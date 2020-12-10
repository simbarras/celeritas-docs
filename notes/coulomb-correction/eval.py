#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Copyright 2020 UT-Battelle, LLC and other Celeritas Developers.
# See the top-level COPYRIGHT file for details.
# SPDX-License-Identifier: (Apache-2.0 OR MIT)
"""
Evaluate the Columb correction factor with an infinite series of Zeta
functions.

Geant4 uses the representation of this function presented in the particle
physics review, which only contains a few decimals of precision.

See https://arxiv.org/abs/1204.3675v3
"""

from scipy.special import zetac
import numpy as np

alpha_fine_structure = 7.297352569e-3 # From NIST CODATA
fz_components = np.array([zetac(2 * n + 1) for n in range(1, 33)])
g4_fz_components = np.array([0.20206, 0.0369, 0.0083, 0.002])


print("Evaluated Coulomb Correction factors")

for atomic_num in [1, 13, 32, 53, 74, 92, 117]:
    print(f"======= Z={atomic_num} =======")
    alphaz = alpha_fine_structure * atomic_num
    azsq = alphaz * alphaz
    pow_series = np.power(-azsq, np.arange(len(fz_components)))
    initial_term = 1/(1 + azsq)
    def calc_f(components):
        i = len(components)
        return azsq * (initial_term + np.dot(components, pow_series[:i]))

    actual = calc_f(fz_components)
    for i in range(len(fz_components)):
        val = calc_f(fz_components[:i])
        err = val / actual - 1
        print(f"  {i:3d}: {val:.16f} ({err:.3g} error)")
        if not abs(err) > 0:
            break


    # Compare to Geant4/PDG value
    val = calc_f(g4_fz_components)
    err = val / actual - 1
    print(f"   G4: {val:.16f} ({err:.3g} error)")

print("First 16 components of the zeta array: ",
      "{",
      ", ".join("{:.16e}".format(v) for v in fz_components[:16].tolist()),
      "}")
