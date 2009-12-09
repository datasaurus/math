/*
   -	bisearch.h --
   -		Declarations of functions that search for intervals in arrays.
   -		See bisearch (3).
   -	
   .	Copyright (c) 2009 Gordon D. Carrie
   .	All rights reserved.
   .
   .	Please send feedback to dev0@trekix.net
   .
   .	$Revision: $ $Date: $
 */

#ifndef BISEARCH_H_
#define BISEARCH_H_

int BISearch(double, double, int);
int BISearch_Az(double, double *, int);

#endif
