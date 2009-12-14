/*
   -	BISearch --
   -		Define functions that search arrays for intervals that
   -		contain given values.
   -
   .	Copyright (c) 2009 Gordon D. Carrie
   .	All rights reserved.
   .
   .	Please send feedback to dev0@trekix.net
   .
   .	$Revision: 1.4 $ $Date: 2009/12/14 20:53:24 $
 */

/*
	Ref: Press, et al., Numerical Recipes in C, 2nd Edition.  p. 117.
 */

#include "bisearch_lib.h"

int BISearch(double x, double *xx, int n)
{
    int jl;		/* Index for lower bound */
    int jm;		/* Index for midpoint in bisection search */
    int ju;		/* Index for upper bound */

    /* Interval includes the left boundary (boundary with lesser index). */

    jl = 0;
    ju = n - 1;
    if (xx[n - 1] > xx[0]) {
	/* xx is increasing */ 
	if (x < xx[0] || x >= xx[n - 1]) {
	    return -1;
	}
	while (ju - jl > 1) {
	    jm = (jl + ju) / 2;
	    if (x >= xx[jm]) {
		jl = jm;
	    } else {
		ju = jm;
	    }
	}
    } else {
	/* xx is decreasing */ 
	if (x > xx[0] || x <= xx[n - 1]) {
	    return -1;
	}
	while (ju - jl > 1) {
	    jm = (jl + ju) / 2;
	    if (x <= xx[jm]) {
		jl = jm;
	    } else {
		ju = jm;
	    }
	}
    }
    return jl;
}

/*
   Put doubles from xx, an array of nx elements, into bins vv, an array of nv
   elements.  ii receives indeces, should point to storage for nx integers.
   c receives number of xx values given to each vv bin, should have storage
   for nv integers.
 */
void BISearchArr(double *xx, int nx, double *vv, int nv, int *ii, unsigned *c)
{
    int n, i;

    for (n = 0; n < nv; n++) {
	c[n] = 0;
    }
    for (n = 0; n < nx; n++) {
	i = BISearch(xx[n], vv, nv);
	ii[n] = i;
	if (i != -1) {
	    c[i]++;
	}
    }
}
