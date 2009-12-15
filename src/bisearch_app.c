/*
   -	bisearch_app.c --
   -		This file defines an application that does bisection searches.
   -		It is meant to exercise the BISearch and BISearchArr functions,
   - 		not be fast or elegant.
   -
   .	Copyright (c) 2008 Gordon D. Carrie
   .	All rights reserved.
   .
   .	Please send feedback to dev0@trekix.net
   .
   .	$Revision: 1.3 $ $Date: 2009/12/15 20:53:04 $
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "err_msg.h"
#include "bisearch_lib.h"

int main(int argc, char *argv[])
{
    char **ap;
    double *xx, *vv, *p;
    int nx, m, nv;
    int *ii, *c;
    int n;

    nv = argc - 1;
    if ( !(vv = calloc((size_t)nv, sizeof(double))) ) {
	fprintf(stderr, "Could not allocate intervals array.\n");
	exit(1);
    }
    if ( !(c = calloc((size_t)nv, sizeof(unsigned))) ) {
	fprintf(stderr, "Could not allocate count array.\n");
	exit(1);
    }

    /* Get interval boundaries from command line */
    for (ap = argv + 1, p = vv; *ap; ap++, p++) {
	if (sscanf(*ap, "%lf", p) != 1) {
	    fprintf(stderr, "Expected float value, got %s.\n", *ap);
	    exit(1);
	}
    }

    /* Get value array from stdin */
    m = 1;
    if ( !(xx = calloc((size_t)m, sizeof(double))) ) {
	fprintf(stderr, "Could not allocate values array.\n");
	exit(1);
    }
    for (p = xx; scanf("%lf", p) == 1; p++) {
	if (p + 1 == xx + m) {
	    int m1;
	    double *t;

	    m1 = 2 * m;
	    if (m1 > INT_MAX / sizeof(double)) {
		fprintf(stderr, "Values array wants more than %d values."
			"  Get real.\n", INT_MAX);
		exit(1);
	    }
	    if ( !(t = realloc(xx, m1 * sizeof(double))) ) {
		fprintf(stderr, "Could not reallocate values array.\n");
		exit(1);
	    }
	    xx = t;
	    p = xx + m - 1;
	    m = m1;
	}
    }
    nx = p - xx;
    if ( !(ii = calloc((size_t)nx, sizeof(int))) ) {
	fprintf(stderr, "Could not allocate index array.\n");
	exit(1);
    }

    /* Bin and print */
    BISearchArr(xx, nx, vv, nv, ii, c);
    for (n = 0; n < nx; n++) {
	printf("%d\n", ii[n]);
    }

    free(vv);
    free(ii);
    free(c);
    free(xx);

    return 0;
}
