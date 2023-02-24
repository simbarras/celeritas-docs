#!/bin/sh -ex
# Copyright 2023 UT-Battelle, LLC, and other Celeritas developers.
# See the top-level COPYRIGHT file for details.
# SPDX-License-Identifier: (Apache-2.0 OR MIT)

ADMINDIR=$(cd $(dirname $0) && pwd)

if ! hash cloc ; then
  echo "This script requires https://github.com/AlDanial/cloc"
  exit 1
fi

cd /Users/seth/.local/src/celeritas-temp
COMMIT=backports/v0.2
VERSION=$(git describe --tags --match='v*' ${COMMIT})

OUTDIR=${ADMINDIR}/run-cloc/${VERSION}
mkdir $OUTDIR || true

function run_cloc() {
  cloc --git ${COMMIT} --force-lang=CUDA,hip --csv --quiet $@
}

run_cloc --exclude-dir=app,generated,scripts,test > $OUTDIR/library.csv
run_cloc --match-d='generated' > $OUTDIR/generated.csv
run_cloc --fullpath --match-d='/app/' > $OUTDIR/app.csv
run_cloc --fullpath --match-d='/test/' > $OUTDIR/test.csv
run_cloc --fullpath --match-d='/example/' > $OUTDIR/example.csv

