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
   .	$Revision: 1.3 $ $Date: 2009/12/14 16:31:42 $
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
