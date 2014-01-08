/*
   -	bisearch_app.c --
   -		This file defines an application that does bisection searches.
   -		It is meant to exercise the BiSearch and BiSearchArr functions,
   - 		not be fast or elegant.
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
   .	$Revision: 1.12 $ $Date: 2012/11/08 21:12:33 $
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "bisearch_lib.h"

int main(int argc, char *argv[])
{
    char **ap;			/* Point into argv */
    double *bnds, *bnd;		/* Boundaries of data intervals */
    int nb;			/* Number of boundaries
				   = number of data interals + 1 */
    int n;			/* Index from bnds */
    double *xx, *x;		/* Data values */
    int nx;			/* Number of data values */
    int nx_max;			/* Max nx for allocation at xx */
    int *lists;			/* Interval list */

    nb = argc - 1;
    if ( !(bnds = calloc((size_t)nb, sizeof(double))) ) {
	fprintf(stderr, "Could not allocate intervals array.\n");
	exit(1);
    }

    /* Get interval boundaries from command line */
    for (ap = argv + 1, bnd = bnds; *ap; ap++, bnd++) {
	if (sscanf(*ap, "%lf", bnd) != 1) {
	    fprintf(stderr, "Expected float value, got %s.\n", *ap);
	    exit(1);
	}
    }

    /* Get value array from stdin */
    nx_max = 1;
    if ( !(xx = calloc((size_t)nx_max, sizeof(double))) ) {
	fprintf(stderr, "Could not allocate values array.\n");
	exit(1);
    }
    for (x = xx; scanf("%lf", x) == 1; x++) {
	if (x + 1 == xx + nx_max) {
	    int m1;
	    double *t;

	    m1 = 2 * nx_max;
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
	    x = xx + nx_max - 1;
	    nx_max = m1;
	}
    }
    nx = x - xx;
    if ( !(lists = calloc((size_t)(nb + nx), sizeof(int))) ) {
	fprintf(stderr, "Could not allocate index array.\n");
	exit(1);
    }

    /* Bin and print */
    BiSearch_DDataToList(xx, nx, bnds, nb, lists);
    for (n = 0; n < nb - 1; n++) {
	int i;				/* Interval index */

	printf("%.2f to %.2f: ", bnds[n], bnds[n + 1]);
	for (i = BiSearch_1stIndex(lists, n); i != -1; ) {
	    printf("%.2f ", xx[i]);
	    i = BiSearch_NextIndex(lists, i);
	}
	printf("\n");
    }

    free(bnds);
    free(lists);
    free(xx);

    return 0;
}
