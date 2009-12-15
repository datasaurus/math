/*
   -	bisearch_app.c --
   -		This file defines an application that does bisection searches.
   -
   .	Copyright (c) 2008 Gordon D. Carrie
   .	All rights reserved.
   .
   .	Please send feedback to dev0@trekix.net
   .
   .	$Revision: 1.2 $ $Date: 2009/12/14 16:31:42 $
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "err_msg.h"
#include "bisearch_lib.h"

int main(int argc, char *argv[])
{
    double *xx, x, *xp;
    char **ap;

    if ( !(xx = calloc(argc - 1, sizeof(double))) ) {
	fprintf(stderr, "Could not allocate array.\n");
	exit(1);
    }
    for (ap = argv + 1, xp = xx; *ap; ap++, xp++) {
	if (sscanf(*ap, "%lf", xp) != 1) {
	    fprintf(stderr, "Expected float value, got %s.\n", *ap);
	    exit(1);
	}
    }
    while (scanf("%lf", &x) == 1) {
	printf("%d\n", BISearch(x, xx, argc - 1));
    }
    free(xx);

    return 0;
}
