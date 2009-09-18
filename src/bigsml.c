/*
 - bigsml.c --
 -	Print a sequence of values with bigger steps at small magnitude values.
 -
   Copyright (c) 2009 Gordon D. Carrie
   All rights reserved.

   Please send feedback to dev0@trekix.net
  
   $Revision: 1.1 $ $Date: 2009/09/18 17:13:19 $
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* This parameter set the relative sizes of the big and small steps */
double X = 20.0;

int main(int argc, char *argv[])
{
    char *cmd = argv[0], *lo_s, *hi_s, *N_s;
    double lo, hi;
    int n, N;
    double n0;	/* Index where value crosses zero */
    double a, v;

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
    n0 = (N - 1) / 2.0;
    a = ((fabs(lo) > fabs(hi)) ? fabs(lo) : fabs(hi)) / log(X);

    /* Make two logarithmic curves */
    for (n = 0; n < (int)n0; n++) {
	v = -a * log(X - n * (X - 1) / n0);
	if (lo <= v && v <= hi) {
	    printf("%d %f\n", n, v);
	}
    }
    for ( ; n < N; n++) {
	v = a * log(2 - X + n * (X - 1) / n0);
	if (lo <= v && v <= hi) {
	    printf("%d %f\n", n, v);
	}
    }
    return 0;
}
