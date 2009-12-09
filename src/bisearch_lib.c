/*
   -	BISearch --
   -		Define functions that search arrays for intervals that contain
   -		given points.
   -
   .	Copyright (c) 2009 Gordon D. Carrie
   .	All rights reserved.
   .
   .	Please send feedback to dev0@trekix.net
   .
   .	$Revision: $ $Date: $
 */

/*
	Ref: Press, et al., Numerical Recipes in C, 2nd Edition.  p. 117.
 */

#include "bisearch.h"

int BISearch(float x, float *xx, int n)
{
    int jl;		/* Index for lower bound */
    int jm;		/* Index for midpoint in bisection search */
    int ju;		/* Index for upper bound */

    /* Bisect to find the interval that contains the value.  */
    jl = 0;
    ju = n - 1;
    if (xx[n - 1] > xx[0]) {
	/* xx is increasing */ 
	if (x < xx[0] || x > xx[n - 1]) {
	    return -1;
	}
	while (ju - jl > 1) {
	    jm = (jl + ju) / 2;
	    if (x > xx[jm]) {
		jl = jm;
	    } else {
		ju = jm;
	    }
	}
    } else {
	/* xx is decreasing */ 
	if (x > xx[0] || x < xx[n - 1]) {
	    return -1;
	}
	while (ju - jl > 1) {
	    jm = (jl + ju) / 2;
	    if (x > xx[jm]) {
		ju = jm;
	    } else {
		jl = jm;
	    }
	}
    }
    return jl;
}

int
BISearch_Az(double x, double *xx, int n)
{
    int jl;		/* Index for lower bound */
    int jm;		/* Index for midpoint in bisection search */
    int ju;		/* Index for upper bound */

    /* Bisect to find the interval that contains the value.  */
    jl = 0;
    ju = n - 1;
    if (LonCmp(xx[1], xx[0]) == East) {
	/* xx is increasing */ 
	if (LonCmp(x, xx[0]) == West || LonCmp(x, xx[n - 1]) == East) {
	    return -1;
	}
	while (ju - jl > 1) {
	    jm = (jl + ju) / 2;
	    if (LonCmp(x, xx[jm]) == East) {
		jl = jm;
	    } else {
		ju = jm;
	    }
	}
    } else {
	/* xx is decreasing */ 
	if (LonCmp(x, xx[0]) == East || LonCmp(x, xx[n - 1]) == West) {
	    return -1;
	}
	while (ju - jl > 1) {
	    jm = (jl + ju) / 2;
	    if (LonCmp(x, xx[jm]) == East) {
		ju = jm;
	    } else {
		jl = jm;
	    }
	}
    }
    return jl;
}
