/*
 - bighi.c --
 -	Print a sequence of values with bigger steps at high values.
 -
   Copyright (c) 2009 Gordon D. Carrie
   All rights reserved.

   Please send feedback to dev0@trekix.net
  
   $Revision: $ $Date: $
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    char *cmd = argv[0], *lo_s, *hi_s, *n1_s;
    double lo, hi, dlog;
    int n, n1;

    if (argc != 4) {
	fprintf(stderr, "Usage: %s lo hi n\n", cmd);
	exit(1);
    }
    lo_s = argv[1];
    hi_s = argv[2];
    n1_s = argv[3];
    if (sscanf(lo_s, "%lf", &lo) != 1) {
	fprintf(stderr, "%s: expected float value for lo, got %s\n", cmd, lo_s);
	exit(1);
    }
    if (sscanf(hi_s, "%lf", &hi) != 1) {
	fprintf(stderr, "%s: expected float value for hi, got %s\n", cmd, hi_s);
	exit(1);
    }
    if (sscanf(n1_s, "%d", &n1) != 1) {
	fprintf(stderr, "%s: expected float value for n, got %s\n", cmd, n1_s);
	exit(1);
    }

    /* Uniform steps in log => values differ by a constant factor */
    dlog = log(hi - lo + 1) / (n1 - 1);
    for (n = 0; n < n1; n++) {
	printf("%f ", lo + exp(dlog * n) - 1);
    }
    printf("\n");

    return 0;
}
