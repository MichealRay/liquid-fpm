/*
 * Copyright (c) 2008, 2009 Joseph Gaeddert
 * Copyright (c) 2008, 2009 Virginia Polytechnic Institute & State University
 *
 * This file is part of liquid-fpm.
 *
 * liquid-fpm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * liquid-fpm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with liquid-fpm.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIQUIDFPM_SQRT_NEWTON_AUTOTEST_H
#define LIQUIDFPM_SQRT_NEWTON_AUTOTEST_H

#include <stdio.h>
#include <math.h>

#include "liquidfpm.internal.h"
#include "autotest.h"

void sqrt_newton_autotest()
{
    if (_autotest_verbose)
        printf("testing sqrt() [Newton]...\n");

    unsigned int n=32;  // precision
    unsigned int num_steps = 32;
    float xmin = 0.0f;
    float xmax = Q(_fixed_to_float)(Q(_max));
    float dx = (xmax - xmin)/((float)(num_steps-1));
    float tol = expf(-sqrtf(Q(_fracbits)));

    // testing variables
    float xf;
    float yf;
    q32_t x;
    q32_t y;
    float ytest;

    unsigned int i;
    xf = xmin;
    for (i=0; i<num_steps; i++) {
        // compute true inverse (floating-point)
        yf = sqrtf(xf);

        // compute fixed-point value
        x = Q(_float_to_fixed)(xf);
        y = Q(_sqrt_newton)(x,n);

        ytest = Q(_fixed_to_float)(y);

        // run the comparison
        CONTEND_DELTA(yf,ytest,tol);

        if (_autotest_verbose) {
            printf("sqrt(%12.8f) = %12.8f (%12.8f)\n", xf,
                                                      q32_fixed_to_float(y),
                                                      yf);
        }

        // increment input parameter
        xf += dx;
    }

}

#endif // LIQUIDFPM_SQRT_NEWTON_AUTOTEST_H

