/*
 - bighi.c --
 -	Print a sequence of values with bigger steps at high values.
 -
   Copyright (c) 2009 Gordon D. Carrie
   All rights reserved.

   Please send feedback to dev0@trekix.net
  
   $Revision: 1.1 $ $Date: 2009/09/15 21:42:21 $
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    char *cmd = argv[0], *lo_s, *hi_s, *n1_s;
    double lo, hi;
    int n, n1;
    double ni;

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
    ni = n1 - 1;

    /* Uniform steps in log => values differ by a constant factor */
    for (n = 0; n < n1; n++) {
	printf("%f ", lo - 1 + pow(hi + 1 - lo, n / ni));
    }
    printf("\n");

    return 0;
}
