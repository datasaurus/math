/*
 - bigsml.c --
 -	Print a sequence of values with bigger steps at small magnitude values.
 -
   Copyright (c) 2009 Gordon D. Carrie
   All rights reserved

   Please send feedback to dev0@trekix.net
  
   $Revision: 1.5 $ $Date: 2009/09/21 16:04:02 $
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* This parameter sets the ratio of the maximum step size to the minimum */
double M = 3.0;

int main(int argc, char *argv[])
{
    char *cmd = argv[0], *lo_s, *hi_s, *N_s;
    double lo, hi;
    int n, N;
    double x;
    double xl;	/* Abscissa where value = lo */
    double n1;	/* Index where value crosses zero */
    double a;

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

    /* Make two logarithmic curves */
    xl = 2 - exp(-lo / hi * log(M));
    n1 = (N - 1) / (M - xl) * (1 - xl);
    a = hi / log(M);
    for (n = 0; n < n1; n++) {
	x = xl + (M - xl) / (N - 1) * n;
	printf("%d %f\n", n, -a * log(2 - x));
    }
    for ( ; n < N; n++) {
	x = xl + (M - xl) / (N - 1) * n;
	printf("%d %f\n", n, a * log(x));
    }
    return 0;
}
