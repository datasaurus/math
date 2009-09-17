/*
 - bighi.c --
 -	Print a sequence of values with bigger steps at large magnitude values.
 -
   Copyright (c) 2009 Gordon D. Carrie
   All rights reserved.

   Please send feedback to dev0@trekix.net
  
   $Revision: 1.1 $ $Date: 2009/09/17 19:37:40 $
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

	n0 = (N - 1) / (log(1 + hi) / log(1 - lo) + 1);
	if (n0 < 0.0) {
	    fprintf(stderr, "Values cross zero at negative n.\n");
	    exit(1);
	}

	/* Define two curves that grow exponentially away from n0.
	   Both have the same curvature.*/
	for (n = 0; n < (int)n0; n++) {
	    printf("%d %f\n", n, 1 - pow(1 - lo, 1 - n / n0));
	}
	for (n = (int)n0; n < N; n++) {
	    printf("%d %f\n", n, pow(1 - lo, n / n0 - 1) - 1);
	}
    } else if (lo >= 0.0 && hi > 0.0) {
	/* Single exponential curve */
	for (n = 0; n < N; n++) {
	    printf("%d %f\n", n, lo - 1 + pow(hi + 1 - lo, (double)n / (N - 1)));
	}
    } else if (lo <= 0.0 && hi < 0.0) {
	/* Single logarithmic curve */
	for (n = 0; n < N; n++) {
	    printf("%d %f\n", n, lo + log(n + 1) / log(N) * (hi - lo));
	}
    }
    return 0;
}
