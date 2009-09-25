/*
 - bighi.c --
 -	Print a sequence of values with bigger steps at high values.
 -

   Copyright (c) 2009 Gordon D. Carrie
   All rights reserved

   Please send feedback to dev0@trekix.net
  
   $Revision: 1.6 $ $Date: 2009/09/24 15:09:11 $
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Ratio of final (high end) slope to starting slope */
double M = 4.0;

int main(int argc, char *argv[])
{
    char *cmd = argv[0], *lo_s, *hi_s, *N_s;
    double lo, hi;
    int n, N;

    if (argc != 4) {
	fprintf(stderr, "Usage: %s lo hi n\n", cmd);
	exit(1);
    }
    lo_s = argv[1];
    hi_s = argv[2];
    N_s = argv[3];
    if (sscanf(lo_s, "%lf", &lo) != 1) {
	fprintf(stderr, "%s: expected float value for lo, got %s\n", cmd, lo_s);
	exit(1);
    }
    if (sscanf(hi_s, "%lf", &hi) != 1) {
	fprintf(stderr, "%s: expected float value for hi, got %s\n", cmd, hi_s);
	exit(1);
    }
    if ( !(lo < hi) ) {
	fprintf(stderr, "%s: low value must be less than high value\n", cmd);
	exit(1);
    }
    if (sscanf(N_s, "%d", &N) != 1) {
	fprintf(stderr, "%s: expected integer value for n, got %s\n", cmd, N_s);
	exit(1);
    }
    if (N <= 0) {
	fprintf(stderr, "%s: Number of values must be positive.\n", cmd);
	exit(1);
    }

    /* Values grow exponentially. */
    for (n = 0; n < N; n++) {
	printf("%d %f\n", n,
		lo + (pow(M, n / (N - 1.0)) - 1.0) * (hi - lo) / (M - 1.0));
    }

    return 0;
}
