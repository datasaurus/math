/*
 - bigsml.c --
 -	Print a sequence of values with bigger steps at small magnitude values.
 -
   Copyright (c) 2009 Gordon D. Carrie
   All rights reserved.

   Please send feedback to dev0@trekix.net
  
   $Revision: $ $Date: $
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* This parameter set the relative sizes of the big and small steps */
double X = 6.0;

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
    if (sscanf(N_s, "%d", &N) != 1) {
	fprintf(stderr, "%s: expected float value for n, got %s\n", cmd, N_s);
	exit(1);
    }

    if (lo < 0.0 && hi >= 0.0) {
	double n0;	/* Index where value crosses zero */
	double a;

	n0 = (N - 1) / 2.0;
	if (n0 < 0.0 || n0 > N - 1) {
	    fprintf(stderr, "Values cross zero at negative n.\n");
	    exit(1);
	}
	a = hi / log(X);

	/* Define two curves that grow logarithmically away from n0. */
	for (n = 0; n < (int)n0; n++) {
	    printf("%d %f\n", n, -a * log(X - n * (X - 1) / n0));
	}
	for ( ; n < N; n++) {
	    printf("%d %f\n", n, a * log(2 - X + n * (X - 1) / n0));
	}
    } else if (lo >= 0.0 && hi > 0.0) {
	for (n = 0; n < N; n++) {
	}
    } else if (lo <= 0.0 && hi < 0.0) {
	for (n = 0; n < N; n++) {
	}
    }
    return 0;
}
