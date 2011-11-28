/*
   -	bisearch_app.c --
   -		This file defines an application that does bisection searches.
   -		It is meant to exercise the BISearch and BISearchArr functions,
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
   .	$Revision: 1.7 $ $Date: 2009/12/16 16:18:18 $
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
    int *ii;
    unsigned *c;
    int n;
    FILE *f3;

    nv = argc - 1;
    if ( !(vv = calloc((size_t)nv, sizeof(double))) ) {
	fprintf(stderr, "Could not allocate intervals array.\n");
	exit(1);
    }
    if ( !(c = calloc((size_t)(nv - 1), sizeof(unsigned))) ) {
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
    if ( (f3 = fdopen(3, "w")) ) {
	for (n = 0; n < nv - 1; n++) {
	    fprintf(f3, "%u\n", c[n]);
	}
    }

    free(vv);
    free(ii);
    free(c);
    free(xx);

    return 0;
}
