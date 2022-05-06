#!/usr/bin/env python3
# Copyright 2022 UT-Battelle, LLC, and other Celeritas developers.
# See the top-level COPYRIGHT file for details.
# SPDX-License-Identifier: (Apache-2.0 OR MIT)
"""
"""

import json
import re
import logging
import os
from os.path import splitext, split as pathsplit
import subprocess

from collections import defaultdict, deque, namedtuple
from pathlib import Path

HEADER_EXTS = {'.cuh', '.h', '.hh'}

SOURCE_DIR = Path('/rnsdhpc/code/celeritas')
NEW_SHA = '5d8a0c73bd5e6b574a6830d2c643acb56a9c72cd'

log = logging.getLogger('rewriter')
log.setLevel(logging.INFO)

def call_git(subcmd, *args):
    out = subprocess.run(
        ['git', '-C', str(SOURCE_DIR), subcmd, '-z'] + list(args),
        check=True, capture_output=True)
    return (s.decode() for s in out.stdout.split(b'\0'))


def filter_headers(files):
    for filename in files:
        if splitext(filename)[1] in HEADER_EXTS:
            yield filename


def filter_renames(names):
    names = iter(names)
    try:
        while True:
            delta = next(names)
            if delta.startswith('R'):
                yield (next(names), next(names))
            else:
                skipped = next(names)
                print(f"WARNING: not a rename: {delta}, {skipped}")
    except StopIteration:
        pass


def get_listing(sha, *args):
    return call_git('ls-tree', '-r', '--name-only', sha, *args)


def dirname(filename):
    i = filename.rfind('/') + 1
    return filename[:i]


def joinpath(dirname, filename):
    if not dirname:
        return filename
    if not dirname.endswith('/'):
        dirname = dirname + '/'
    return dirname + filename


class HeaderListing:
    def __init__(self, filenames):
        """Construct from filenames relative to the repository root.

        Save a set of paths to all filenames, and a mapping of directory listings.
        """
        filtered_filenames = set()
        dirs = defaultdict(set)
        for fn in filenames:
            ext = splitext(fn)[1]
            if ext not in HEADER_EXTS:
                continue
            filtered_filenames.add(fn)
            (head, tail) = pathsplit(fn)
            dirs[head].add(tail)

        self.filenames = frozenset(filtered_filenames)
        self.dirs = {k: frozenset(v) for (k, v) in dirs.items()}
        self._relative = {}

    def listdir(self, dirname):
        try:
            result = self.dirs[dirname]
        except KeyError:
            result = frozenset()
            self.dirs[dirname] = result
        return result

#    def relative_to(self, dirname):
#        """Get a list of all directories relative to the given directory.
#
#        Filter out directories outside of the dir."""
#        try:
#            # cached
#            return self._relative[dirname]
#        except KeyError:
#            pass
#
#        result = {}
#        for (k, v) in self.dirs.items():
#            if not k.startswith(dirname):
#                continue
#            result[k[len(dirname):]] = v
#
#        self._relative[dirname] = result
#        return result

    def exists(self, filename):
        return filename in self.filenames


class ChangeMap(dict):
    def __init__(self, changes):
        self.update({old: new.split('/')
             for (old, new) in changes.items()})

    def __getitem__(self, key):
        try:
            return dict.__getitem__(self, key)
        except KeyError:
            self[key] = result = key.split('/')
            return result


class IncludeProcessor:
    def __init__(self, headers, search_paths, filename):
        """
        Search paths and filename must be relative to the "headers" root.
        """
        self.headers = headers
        self.search_paths = search_paths
        self.dirname = dirname(filename)

    def __call__(self, filename):
        """Convert the given filename to an absolute path.
        """
        # Try relative
        test_dir = self.dirname
        test_path = filename
        while test_path.startswith('../'):
            test_dir = dirname(self.dirname)
            test_path = test_path

        test_path = joinpath(test_dir, test_path)
        if self.headers.exists(test_path):
            return (test_dir, filename)

        # Try remaining paths
        for test_dir in self.search_paths:
            test_path = joinpath(test_dir, filename)
            if self.headers.exists(test_path):
                return (test_dir, filename)

        # Assume it's a system/build include and don't modify
        return (None, None)


class SourceFileConverter:
    def __init__(self, headers, changes, orig_filename):
        self.process_include = IncludeProcessor(oldh, orig_filename)
        self.changes = changes
        # Break old and new filename into components
        self.new = changes[orig_filename]
        self.is_detail = (len(self.new) > 2 and self.new[-2] == 'detail')

    def __call__(self, filename):
        """Convert a within-file include to an updated path."""
        old_path = self.process_include(filename)
        if not old_path:
            # System include
            return filename

        # Remap from old to new path
        new_path = self.changes[old_path]

        # Find index of first not-common component to make relative
        min_len = len(self.new) - 1
        if self.new[:min_len] == new_path[:min_len]:
            new_path = new_path[min_len:]
        elif self.is_detail and self.new[:min_len - 1] == new_path[:min_len - 1]:
            new_path = ['..'] + new_path[min_len - 1:]

        return '/'.join(new_path)


class ReWriter:
    """Handle safe writing of new files.

    This takes care of error conditions as well as being graceful about not
    touching files that don't get changed.
    """
    def __init__(self, filename, preserve=False):
        (base, ext) = os.path.splitext(filename)

        self.filename     = filename
        self.tempfilename = base + ".temp" + ext
        self.origfilename = base + ".orig" + ext

        # New and original files
        self.infile  = open(filename, "r")
        self.outfile = open(self.tempfilename, "w")

        # Whether we've changed the file
        self.dirty    = False
        # Whether to preserve the original
        self.preserve = preserve

    def close(self, did_error=False):
        self.infile.close()
        self.outfile.close()

        if did_error:
            log.error("ERROR while processing %s" % self.filename)
            if not self.preserve:
                # Failure and we want to delete the temp file
                os.unlink(self.tempfilename)
        elif self.dirty:
            log.info("CHANGED file %s" % self.filename)
            # Swap original and temp
            os.rename(self.filename, self.origfilename)
            os.rename(self.tempfilename, self.filename)

            # Delete the old file
            if not self.preserve:
                os.unlink(self.origfilename)
        else:
            log.info("No changes to %s" % self.filename)
            # No changes, no errors; delete the temp file
            os.unlink(self.tempfilename)

    def __enter__(self):
        "Called when entering context using 'with'"
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        "Called when leaving context"
        self.close(did_error=(exc_type is not None))
        return False

    @property
    def files(self):
        """Get the list of in/out files.

        This is for setting:
        >>> (infile, outfile) = rewriter.files
        """
        return (self.infile, self.outfile)



#-----------------------------------------------------------------------------#

headers = HeaderListing(get_listing(NEW_SHA + '^'))
filename_changes = dict(filter_renames(call_git(
    'diff', '--name-status', NEW_SHA + '^', NEW_SHA)))
change_map = ChangeMap(filename_changes)
