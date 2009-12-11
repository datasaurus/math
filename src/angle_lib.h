/*
   -	angle_lib.h --
   -		Declarations of functions that manipulate angles.
   -		See angle_lib (3).
   -	
   .	Copyright (c) 2009 Gordon D. Carrie
   .	All rights reserved.
   .
   .	Please send feedback to dev0@trekix.net
   .
   .	$Revision: 1.2 $ $Date: 2009/12/09 22:18:50 $
 */

#ifndef ANGLE_H_
#define ANGLE_H_

#ifndef M_PI
#define M_PI     3.141592653589793238462	/* pi */
#endif
#ifndef M_PI_2
#define M_PI_2   1.570796326794896619231	/* pi / 2 */
#endif
#ifndef RAD_DEG
#define RAD_DEG   0.01745329251994329576	/* radians / degree */
#endif
#ifndef DEG_RAD
#define DEG_RAD   57.29577951308232087680	/* degrees / radian */
#endif

double Angle_AzWrap(const double, const double);
double Angle_ElevWrap(const double);
double Angle_GCDist(const double, const double, const double, const double);
double Angle_GCAz(const double, const double, const double, const double);
void Angle_GCStep(const double, const double, const double, const double,
	double *, double *);

#endif
