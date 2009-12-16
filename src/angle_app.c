/*
   -	angle_app.c --
   -		This file defines an application that does angle calculations.
   -
   .	Copyright (c) 2008 Gordon D. Carrie
   .	All rights reserved.
   .
   .	Please send feedback to dev0@trekix.net
   .
   .	$Revision: 1.2 $ $Date: 2009/12/11 23:06:04 $
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "err_msg.h"
#include "angle_lib.h"

/* Application name and subcommand name */
char *cmd, *cmd1;

/* Number of subcommands */
#define NCMD 5

/* Callback functions.  There should be one for each subcommand. */
typedef int (callback)(int , char **);
callback az_wrap_cb;
callback elev_wrap_cb;
callback gc_dist_cb;
callback gc_dirn_cb;
callback gc_step_cb;

/* If true, use degrees instead of radians */
int use_deg = 0;

int main(int argc, char *argv[])
{
    char *ang_u;	/* Angle unit */
    int i;		/* Index for subcommand in argv[1] */
    int rslt;		/* Return code */

    /* Arrays of subcommand names and associated callbacks */
    char *cmd1v[NCMD]
	= {"az_wrap", "elev_wrap", "gc_dist", "gc_dirn", "gc_step"};
    callback *cb1v[NCMD]
	= {az_wrap_cb, elev_wrap_cb, gc_dist_cb, gc_dirn_cb, gc_step_cb};

    cmd = argv[0];
    if (argc < 2) {
	fprintf(stderr, "Usage: %s subcommand [subcommand_options ...]\n", cmd);
	exit(1);
    }
    cmd1 = argv[1];

    /* Check for angle unit */
    if ((ang_u = getenv("ANGLE_UNIT")) != NULL) {
	if (strcmp(ang_u, "DEGREE") == 0) {
	    use_deg = 1;
	} else if (strcmp(ang_u, "RADIAN") == 0) {
	    use_deg = 0;
	} else {
	    fprintf(stderr, "%s: Unknown angle unit %s.\n", cmd, ang_u);
	    exit(1);
	}
    }

    /* Search cmd1v for cmd1.  When match is found, evaluate the associated
     * callback from cb1v. */
    for (i = 0; i < NCMD; i++) {
	if (strcmp(cmd1v[i], cmd1) == 0) {
	    rslt = (cb1v[i])(argc, argv);
	    if ( !rslt ) {
		fprintf(stderr, "%s %s failed.\n", cmd, cmd1);
		fprintf(stderr, "%s\n", Err_Get());
		break;
	    } else {
		break;
	    }
	}
    }
    if (i == NCMD) {
	fprintf(stderr, "%s: No option or subcommand named %s\n", cmd, cmd1);
	fprintf(stderr, "Subcommand must be one of: ");
	for (i = 0; i < NCMD; i++) {
	    fprintf(stderr, "%s ", cmd1v[i]);
	}
	fprintf(stderr, "\n");
	rslt = 0;
    }
    return !rslt;
}

int az_wrap_cb(int argc, char *argv[])
{
    char *l_s, *r_s;		/* Strings from command line */
    double l, r;		/* Values from command line */
    double c;

    if (argc != 4) {
	Err_Append("Usage: ");
	Err_Append(cmd);
	Err_Append(" ");
	Err_Append(cmd1);
	Err_Append(" lon reflon\n");
	return 0;
    }
    l_s = argv[2];
    if (sscanf(l_s, "%lf", &l) != 1) {
	Err_Append("Expected float value for longitude, got ");
	Err_Append(l_s);
	Err_Append(".\n");
	return 0;
    }
    r_s = argv[3];
    if (sscanf(r_s, "%lf", &r) != 1) {
	Err_Append("Expected float value for reference longitude, got ");
	Err_Append(r_s);
	Err_Append(".\n");
	return 0;
    }
    c = (use_deg ? RAD_DEG : 1.0);
    printf("%lf\n", Angle_AzWrap(l * c, r * c) / c);
    return 1;
}

int elev_wrap_cb(int argc, char *argv[])
{
    char *l_s;			/* String from command line */
    double l;			/* Latitude value from command line */
    double c;

    if (argc != 3) {
	Err_Append("Usage: ");
	Err_Append(cmd);
	Err_Append(" ");
	Err_Append(cmd1);
	Err_Append(" angle\n");
	return 0;
    }
    l_s = argv[2];
    if (sscanf(l_s, "%lf", &l) != 1) {
	Err_Append("Expected float value for angle, got ");
	Err_Append(l_s);
	Err_Append(".\n");
	return 0;
    }
    c = (use_deg ? RAD_DEG : 1.0);
    printf("%f\n", Angle_ElevWrap(l * c) / c);
    return 1;
}

int gc_dist_cb(int argc, char *argv[])
{
    char *az1_s, *elev1_s, *az2_s,  *elev2_s;
    double az1, elev1, az2, elev2, c;

    if (argc != 6) {
	Err_Append("Usage: ");
	Err_Append(cmd);
	Err_Append(" ");
	Err_Append(cmd1);
	Err_Append(" elev1 az1 elev2 az2\n");
	return 0;
    }
    az1_s = argv[2];
    elev1_s = argv[3];
    az2_s = argv[4];
    elev2_s = argv[5];

    /* Get coordinates from command line arguments */
    if (sscanf(az1_s, "%lf", &az1) != 1) {
	Err_Append("Expected float value for az1, got ");
	Err_Append(az1_s);
	Err_Append(".\n");
	return 0;
    }
    if (sscanf(elev1_s, "%lf", &elev1) != 1) {
	Err_Append("Expected float value for elev1, got ");
	Err_Append(elev1_s);
	Err_Append(".\n");
	return 0;
    }
    if (sscanf(az2_s, "%lf", &az2) != 1) {
	Err_Append("Expected float value for az2, got ");
	Err_Append(az2_s);
	Err_Append(".\n");
	return 0;
    }
    if (sscanf(elev2_s, "%lf", &elev2) != 1) {
	Err_Append("Expected float value for elev2, got ");
	Err_Append(elev2_s);
	Err_Append(".\n");
	return 0;
    }
    c = (use_deg ? RAD_DEG : 1.0);
    printf("%f\n", Angle_GCDist(az1 * c, elev1 * c, az2 * c, elev2 * c) / c);
    return 1;
}

int gc_dirn_cb(int argc, char *argv[])
{
    char *az1_s, *elev1_s, *az2_s,  *elev2_s;
    double az1, elev1, az2, elev2, c;

    if (argc != 6) {
	Err_Append("Usage: ");
	Err_Append(cmd);
	Err_Append(" ");
	Err_Append(cmd1);
	Err_Append(" elev1 az1 elev2 az2\n");
	return 0;
    }
    az1_s = argv[2];
    elev1_s = argv[3];
    az2_s = argv[4];
    elev2_s = argv[5];

    /* Get coordinates from command line arguments */
    if (sscanf(az1_s, "%lf", &az1) != 1) {
	Err_Append("Expected float value for az1, got ");
	Err_Append(az1_s);
	Err_Append(".\n");
	return 0;
    }
    if (sscanf(elev1_s, "%lf", &elev1) != 1) {
	Err_Append("Expected float value for elev1, got ");
	Err_Append(elev1_s);
	Err_Append(".\n");
	return 0;
    }
    if (sscanf(az2_s, "%lf", &az2) != 1) {
	Err_Append("Expected float value for az2, got ");
	Err_Append(az2_s);
	Err_Append(".\n");
	return 0;
    }
    if (sscanf(elev2_s, "%lf", &elev2) != 1) {
	Err_Append("Expected float value for elev2, got ");
	Err_Append(elev2_s);
	Err_Append(".\n");
	return 0;
    }
    c = (use_deg ? RAD_DEG : 1.0);
    printf("%f\n", Angle_GCAz(az1 * c, elev1 * c, az2 * c,  elev2 * c) / c);
    return 1;
}

int gc_step_cb(int argc, char *argv[])
{
    double az1, elev1, dirn, dist, az2, elev2, c;

    if (argc == 2) {
	while (scanf("%lf %lf %lf %lf", &az1, &elev1, &dirn, &dist) == 4) {
	    c = use_deg ? RAD_DEG : 1.0;
	    Angle_GCStep(az1 * c, elev1 * c, dirn * c, dist * c, &az2, &elev2);
	    c = use_deg ? DEG_RAD : 1.0;
	    printf("%f %f\n", az2 * c, elev2 * c);
	}
    } else if (argc == 6) {
	char *elev1_s, *az1_s, *dirn_s, *dist_s;

	az1_s = argv[2];
	if (sscanf(az1_s, "%lf", &az1) != 1) {
	    Err_Append("Expected float value for az1, got ");
	    Err_Append(az1_s);
	    Err_Append(".\n");
	    return 0;
	}
	elev1_s = argv[3];
	if (sscanf(elev1_s, "%lf", &elev1) != 1) {
	    Err_Append("Expected float value for elev1, got ");
	    Err_Append(elev1_s);
	    Err_Append(".\n");
	    return 0;
	}
	dirn_s = argv[4];
	if (sscanf(dirn_s, "%lf", &dirn) != 1) {
	    Err_Append("Expected float value for azimuth, got ");
	    Err_Append(dirn_s);
	    Err_Append(".\n");
	    return 0;
	}
	dist_s = argv[5];
	if (sscanf(dist_s, "%lf", &dist) != 1) {
	    Err_Append("Expected float value for range, got ");
	    Err_Append(dist_s);
	    Err_Append(".\n");
	    return 0;
	}
	c = use_deg ? RAD_DEG : 1.0;
	Angle_GCStep(az1 * c, elev1 * c, dirn * c, dist * c, &az2, &elev2);
	c = use_deg ? DEG_RAD : 1.0;
	printf("%f %f\n", az2 * c, elev2 * c);
    } else {
	Err_Append("Usage: ");
	Err_Append(cmd);
	Err_Append(" ");
	Err_Append(cmd1);
	Err_Append(" [lon lat direction distance]\n");
	return 0;
    }
    return 1;
}
