/*
   -	angle_lib.c --
   -		This file defines functions that manipulate angles.
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

#include <math.h>
#include "angle_lib.h"

double Angle_AzWrap(const double l, const double r)
{
    double l1 = fmod(l, 2.0 * M_PI);
    l1 = (l1 < r - M_PI) ? l1 + 2.0 * M_PI
	: (l1 >= r + M_PI) ? l1 - 2.0 * M_PI : l1;
    return (l1 == -0.0) ? 0.0 : l1;
}

double Angle_ElevWrap(const double l)
{
    double l1 = fmod(l, 2.0 * M_PI);
    l1 += (l1 < 0.0) ? 2.0 * M_PI : 0.0;
    return (l1 > 1.5 * M_PI) ? l1 - 2.0 * M_PI : (l1 > M_PI_2 ) ? M_PI - l1 : l1;
}

double Angle_GCDist(const double o1, const double a1,
	const double o2, const double a2)
{
    double sin_do_2, sin_da_2, a;

    /*
       Reference -- R.W. Sinnott, "Virtues of the Haversine",
       Sky and Telescope, vol. 68, no. 2, 1984, p. 159
       cited in: http://www.census.gov/cgi-bin/geo/gisfaq?Q5.1
     */

    sin_do_2 = sin(0.5 * (o2 - o1));
    sin_da_2 = sin(0.5 * (a2 - a1));
    a = sqrt(sin_da_2 * sin_da_2 + cos(a1) * cos(a2) * sin_do_2 * sin_do_2);
    return (a > 1.0 ? M_PI : 2.0 * asin(a));
}

double Angle_GCAz(const double o1, const double a1,
	const double o2, const double a2)
{
    double sin_da, sin_sa, y, x;

    sin_da = sin(a1 - a2);
    sin_sa = sin(a2 + a1);
    y = cos(a2) * sin(o2 - o1);
    x = 0.5 * (sin_sa - sin_da - (sin_sa + sin_da) * cos(o2 - o1));
    return atan2(y, x);
}

void Angle_GCStep(const double o1, const double a1, const double d, const double s,
	double *o2, double *a2)
{
    double sin_s, sin_d, cos_d, dlon, a, x, y;

    /*
       Reference -- Smart, W. M., "Textbook on Spherical Astronomy",
       Sixth edition revised by R. M. Green.
       Cambridge University Press, Cambridge, 1977.
     */

    sin_s = sin(s);
    sin_d = sin(d);
    cos_d = cos(d);
    a = 0.5 * (sin(a1 + s) * (1.0 + cos_d) + sin(a1 - s) * (1.0 - cos_d));
    *a2 = (a > 1.0) ? M_PI_2 : (a < -1.0) ? -M_PI_2 : asin(a);
    y = sin_s * sin_d;
    x = 0.5 * (cos(a1 + s) * (1 + cos_d) + cos(a1 - s) * (1 - cos_d));
    dlon = atan2(y, x);
    *o2 = Angle_AzWrap(o1 + dlon, 0.0);
}
