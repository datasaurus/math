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
   .	$Revision: 1.2 $ $Date: 2009/12/11 23:07:48 $
 */

#ifndef BISEARCH_H_
#define BISEARCH_H_

int BISearch(double, double *, int);
void BISearchArr(double *, int, double *, int, int *, unsigned *);

#endif
