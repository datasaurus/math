/*
   -	BISearch --
   -		Define functions that search arrays for intervals that
   -		contain given values.  See bisearch (n).
   -
   .	Copyright (c) 2011, Gordon D. Carrie. All rights reserved.
   .	
   .	Redistribution and use in source and binary forms, with or without
   .	modification, are permitted provided that the following conditions
   .	are met:
   .	
   .	    * Redistributions of source code must retain the above copyright
   .	    notice, this list of conditions and the following disclaimer.
   .
   .	    * Redistributions in binary form must reproduce the above copyright
   .	    notice, this list of conditions and the following disclaimer in the
   .	    documentation and/or other materials provided with the distribution.
   .	
   .	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   .	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   .	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   .	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
   .	HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   .	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
   .	TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   .	PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   .	LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   .	NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   .	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
   .
   .	Please send feedback to dev0@trekix.net
   .
   .	$Revision: 1.9 $ $Date: 2012/09/14 16:07:05 $
 */

/*
	Ref: Press, et al., Numerical Recipes in C, 2nd Edition.  p. 117.
 */

#include "bisearch_lib.h"

int BISearch(double val, double *bnds, int n_bnds)
{
    int jl;		/* Index for lower bound */
    int jm;		/* Index for midpoint in bisection search */
    int ju;		/* Index for upper bound */

    /* Interval includes the left boundary (boundary with lesser index). */

    jl = 0;
    ju = n_bnds - 1;
    if (bnds[n_bnds - 1] > bnds[0]) {
	/* bnds is increasing */ 
	if (val < bnds[0] || val >= bnds[n_bnds - 1]) {
	    return -1;
	}
	while (ju - jl > 1) {
	    jm = (jl + ju) / 2;
	    if (val >= bnds[jm]) {
		jl = jm;
	    } else {
		ju = jm;
	    }
	}
    } else {
	/* bnds is decreasing */ 
	if (val > bnds[0] || val <= bnds[n_bnds - 1]) {
	    return -1;
	}
	while (ju - jl > 1) {
	    jm = (jl + ju) / 2;
	    if (val <= bnds[jm]) {
		jl = jm;
	    } else {
		ju = jm;
	    }
	}
    }
    return jl;
}

void BISearchArr(double *vals, int n_vals, double *bnds, int n_bnds,
	int *idcs, unsigned *c)
{
    int n, i;

    for (n = 0; n < n_vals - 1; n++) {
	c[n] = 0;
    }
    for (n = 0; n < n_bnds; n++) {
	i = BISearch(bnds[n], vals, n_vals);
	idcs[n] = i;
	if (i != -1) {
	    c[i]++;
	}
    }
}
