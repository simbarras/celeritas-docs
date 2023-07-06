#!/usr/bin/env python3
# Copyright 2023 UT-Battelle, LLC, and other Celeritas developers.
# See the top-level COPYRIGHT file for details.
# SPDX-License-Identifier: (Apache-2.0 OR MIT)
"""
"""

from itertools import chain
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

from ghapi.all import GhApi, paged, gh2date

with open('/Users/seth/.config/ghapi-token') as f:
    token = f.read().strip()

celer = GhApi(owner='celeritas-project', repo='celeritas', token=token)

def get_stars(repo):
    star_props = chain.from_iterable(paged(
        repo.activity.list_stargazers_for_repo,
        headers=dict(accept='application/vnd.github.star+json')
    ))
    stardate = sorted([gh2date(p['starred_at']) for p in star_props])
    stars = pd.Series(np.arange(len(stardate), dtype=int),
                  index=pd.DatetimeIndex(stardate))
    return stars


celer_stars = get_stars(celer)
# adept_stars = get_stars(GhApi(owner='apt-sim', repo='AdePT', token=token))
#stars = pd.DataFrame({'celeritas': celer_stars, 'adept': adept_stars})
stars = celer_stars

(fig, ax) = plt.subplots(figsize=(3,3))
stars.plot(ylabel='# stars', ax=ax);
ax.grid(which='major', c=(0.85,)*3)
plt.tight_layout()
fig.savefig('github-stars.pdf', transparent=True)
