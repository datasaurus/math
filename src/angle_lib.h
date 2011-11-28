/*
   -	angle_lib.h --
   -		Declarations of functions that manipulate angles.
   -		See angle_lib (3).
   -	
   .	Copyright (c) 2011, Gordon D. Carrie. All rights reserved.
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
   .	$Revision: 1.3 $ $Date: 2009/12/11 21:49:35 $
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
