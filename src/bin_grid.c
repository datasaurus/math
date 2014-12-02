/*
   -	bin_grid.c --
   -		Bin rectangular cells into data intervals and print outlines
   -		for each interval.
   -
   .	Usage:
   .		bin_grid -s attributes -t transparent
   .	where:
   .		-s requests SVG output. String attributes will be added to
   .		   the path elements for the polygons.
   .		-t specifies a transparent color. Cells for this color will
   .		   be excluded from output.
   .
   .	The process will then read grid, color, and data specifiers as described
   .	below.
   .
   .	Copyright (c) 2013, Gordon D. Carrie. All rights reserved.
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
   .	$Revision: 1.1 $ $Date: 2014/05/27 18:55:08 $
 */

/*
   Read the following from standard input:

   nx
   x[0] x[1] x[2] ... x[nx-1]
   ny
   y[0] y[1] y[2] ... y[ny-1]
   nbnds
   bnd[0] bnd[1] bnd[2] ... bnd[nbnds-1]
   color[0] color[1] ... color[nbnds-2]
   v[0][0] v[0][1] v[0][2] ... v[0][nx-2]
   v[1][0] v[1][1] v[1][2] ... v[1][nx-2]
   ...
   v[ny-2][0] v[ny-2][1] v[ny-2][2] ... v[ny-2][nx-2]

   x refers to horizontal coordinate in cartesian grid.
   y refers to vertical coordinate in cartesian grid.
   nx		= number of x coordinates.
   x		= x coordinates of cells
   ny		= number of y coordinates
   y		= y coordinates of cells
   nbnds	= number of boundaries defining the data intervals.
   bnd		= boundaries
   color	= color specifier for the interval - actually any string of up
   .		  to LEN characters that describes the interval.
   v		= values in cells. Count = (nx - 1) * (ny - 1).

   Input tokens can be separated by any combination of white space.

   Grid layout:

   y[ny-1] |---------------|---------------|     |---------------|
           |               |               |     |               |
           |  v[ny-2][0]   |  v[ny-2][1]   | ... | v[ny-2][nx-2] |
           |               |               |     |               |
   y[ny-2] |---------------|---------------|     |---------------|

           ...

   y[1]    |---------------|---------------|     |---------------|
           |               |               |     |               |
           |    v[0][0]    |    v[0][1]    | ... | v[ny-2][nx-2] |
           |               |               |     |               |
   y[0]    |---------------|---------------|     |---------------|
   .       x[0]            x[1]              ... x[nx-2]         x[nx-1]

   Standard output will be:

   color[0]
   x y x y x y x y
   x y x y x y x y
   ...
   color[1]
   x y x y x y x y
   x y x y x y x y
   ...
   color[nbnds-2]
   x y x y x y x y
   x y x y x y x y
   ...

   "x y x y x y x y" represents a list of coordinates for corners of a cell.
   If v[j][i] satisfies bnd[n] <= v[j][i] < bnd[n+1], then output
   for color[n] will have a line of form:
   x[i] y[j] x[i+1] y[j] x[i+1] y[j+1] x[i] y[j+1]

 */

#include "unix_defs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "bisearch_lib.h"

/* Length of various names and strings */
#define LEN 255
#define LEN_FMT " %254s"

int main(int argc, char *argv[])
{
    char *argv0 = argv[0];		/* Name of this command */
    char *attr = "";			/* Attributes for SVG path elements */
    char *transparent = "";		/* Transparent color */
    size_t num_x;			/* Number of cell corners in x
					   direction */
    size_t num_cell_x;			/* Number of cells in x direction,
					   always num_cell_x
					 */
    size_t num_y;			/* Number of cell corners in y
					   direction */
    size_t num_cell_y;			/* Number of cells in y direction,
					   always num_cell_y */
    size_t num_bnds;			/* Number of data boundaries */
    size_t num_colors;			/* Number of data intervals, always
					   num_bnds - 1 */
    char **x, **y;			/* Grid coordinates. Not used in any
					   computation, so store as strings to
					   preserve input format */
    double *bnd;			/* Data boundaries, dimensioned
					   [num_bnds] */
    char **colors;			/* Strings storing color names,
					   dimensioned [num_colors][LEN] */
    double **v;				/* Data values, dimensioned
					   [num_y][num_x] */
    int *lists;				/* Linked lists of cell indeces within
					   data intervals. Returned by
					   BiSearch_DDataToList. See bisearch
					   (3). */
    int c, j, i, n, d;

    while ((c = getopt(argc, argv, ":s:t:")) != -1) {
	switch(c) {
	    case 's':
		attr = optarg;
		break;
	    case 't':
		transparent = optarg;
		break;
	    case ':':
		fprintf(stderr, "%s: -%c requires an argument\n",
			argv0, optopt);
		exit(EXIT_FAILURE);
		break;
	    case '?':
		fprintf(stderr, "%s: unknown option %c\n", argv0, c);
		exit(EXIT_FAILURE);
		break;
	}
    }

    /* Allocate and read x coordinates as array of strings */ 
    if ( scanf(" %zi", &num_x) != 1 ) {
	fprintf(stderr, "%s: could not read number of x coordinates.\n", argv0);
	exit(EXIT_FAILURE);
    }
    num_cell_x = num_x - 1;
    if ( !(x = calloc(num_x, sizeof(char *)))
	    || !(x[0] = calloc(num_x * LEN, 1)) ) {
	fprintf(stderr, "%s: could not allocate memory for "
		"%lu x coordinates.\n", argv0, (unsigned long)num_x);
	exit(EXIT_FAILURE);
    }
    for (i = 1; i < num_x; i++) {
	x[i] = x[i - 1] + LEN;
    }
    for (i = 0; i < num_x; i++) {
	if ( scanf(LEN_FMT, x[i]) != 1 ) {
	    fprintf(stderr, "%s: could not read x coordinate at index %d\n",
		    argv0, i);
	    exit(EXIT_FAILURE);
	}
    }

    /* Allocate and read y coordinates as array of strings */ 
    if ( scanf(" %zi", &num_y) != 1 ) {
	fprintf(stderr, "%s: could not read number of y coordinates.\n", argv0);
	exit(EXIT_FAILURE);
    }
    num_cell_y = num_y - 1;
    if ( !(y = calloc(num_y, sizeof(char *)))
	    || !(y[0] = calloc(num_y * LEN, 1)) ) {
	fprintf(stderr, "%s: could not allocate memory for "
		"%lu y coordinates.\n", argv0, (unsigned long)num_y);
	exit(EXIT_FAILURE);
    }
    for (j = 1; j < num_y; j++) {
	y[j] = y[j - 1] + LEN;
    }
    for (j = 0; j < num_y; j++) {
	if ( scanf(LEN_FMT, y[j]) != 1 ) {
	    fprintf(stderr, "%s: could not read y coordinate at index %d\n",
		    argv0, j);
	    exit(EXIT_FAILURE);
	}
    }

    /* Allocate and read boundaries and interval names */ 
    if ( scanf(" %zi", &num_bnds) != 1 ) {
	fprintf(stderr, "%s: could not read number of boundaries.\n", argv0);
	exit(EXIT_FAILURE);
    }
    if ( !(bnd = calloc(num_bnds, sizeof(double))) ) {
	fprintf(stderr, "%s: could not allocate memory for "
		"%lu boundaries.\n", argv0, (unsigned long)num_bnds);
	exit(EXIT_FAILURE);
    }
    for (n = 0; n < num_bnds; n++) {
	if ( scanf(" %lf", bnd + n) != 1 ) {
	    fprintf(stderr, "%s: could not read boundary at index %d\n",
		    argv0, n);
	    exit(EXIT_FAILURE);
	}
    }
    num_colors = num_bnds - 1;
    if ( !(colors = calloc(num_colors, sizeof(char *)))
	    || !(colors[0] = calloc(num_colors * LEN, 1)) ) {
	fprintf(stderr, "%s: could not allocate memory for "
		"%lu data intervals.\n", argv0, (unsigned long)num_colors);
	exit(EXIT_FAILURE);
    }
    for (n = 1; n < num_colors; n++) {
	colors[n] = colors[n - 1] + LEN;
    }
    for (n = 0; n < num_colors; n++) {
	if ( scanf(LEN_FMT, colors[n]) != 1 ) {
	    fprintf(stderr, "%s: could not read interval name at index %d\n",
		    argv0, n);
	    exit(EXIT_FAILURE);
	}
    }
    lists = calloc((size_t)(num_colors + num_cell_y * num_cell_x), sizeof(int));
    if ( !lists ) {
	fprintf(stderr, "%s: failed to allocate storage for lists of cells.\n",
		argv0);
	exit(EXIT_FAILURE);
    }

    /* Read cell data */
    if ( !(v = calloc(num_cell_y, sizeof(double *)))
	    || !(v[0] = calloc(num_cell_y * num_cell_x, sizeof(double))) ) {
	fprintf(stderr, "%s: could not allocate memory for "
		"%lu by %lu data array.\n", argv0,
		(unsigned long)num_cell_x, (unsigned long)num_cell_y);
	exit(EXIT_FAILURE);
    }
    for (j = 1; j < num_cell_y; j++) {
	v[j] = v[j - 1] + num_cell_x;
    }
    for (j = 0; j < num_cell_y; j++) {
	for (i = 0; i < num_cell_x; i++) {
	    if ( scanf(" %lf", &v[j][i]) != 1 ) {
		fprintf(stderr, "%s: could not read data for cell [%d][%d]\n",
			argv0, j, i);
		exit(EXIT_FAILURE);
	    }
	}
    }

    /* Bin the cell data into data intervals. Print corner coordinates */
    BiSearch_DDataToList(v[0], num_cell_y * num_cell_x, bnd, num_bnds, lists);
    for (n = 0; n < num_colors; n++) {
	if ( BiSearch_1stIndex(lists, n) != -1
		&& strcmp(colors[n], transparent) != 0 ) {
	    printf("%s %s\n", colors[n], attr);
	    for (d = BiSearch_1stIndex(lists, n);
		    d != -1;
		    d = BiSearch_NextIndex(lists, d)) {
		j = d / num_cell_x;
		i = d % num_cell_x;
		printf("%s %s %s %s %s %s %s %s\n",
			x[i], y[j], x[i+1], y[j], x[i+1], y[j+1], x[i], y[j+1]);
	    }
	}
    }

    return 0;
}

