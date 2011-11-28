#!/bin/sh
#
#-	step1.sh --
#-		Test "angle gc_step" function.
#-
# Copyright (c) 2011, Gordon D. Carrie. All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 
#     * Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
# TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# Please send feedback to dev0@trekix.net

#
#	Please send feedback to dev0@trekix.net
#
#	$Revision: 1.3 $ $Date: 2009/12/11 21:55:24 $
#
########################################################################

# This script compares output from angle with output from
# geod, stored in file geod.out, which was produced as follows:
#
# radians per degree
# rad_deg=0.01745329251994329576
#
# Earth radius = a
# eval `geod -le | awk '/sphere/ {print $2}'`
# export a
#
#    d_m=`echo "scale=17;$d_deg * $a * $rad_deg" | bc`
#    echo $lat $lon $dir $d_m | geod -f '%.6f' +ellps=sphere \
#	    | (read lat2 lon2 back
#		printf "$f" $lon $lat $dir $d_deg $lon2 $lat2) \
#	    | sed -e 's/-180/ 180/' -e 's/-0/ 0/' >> geod.out
#
# geod is part of proj4.
# cf. http://trac.osgeo.org/proj

# Set RM to : in environment to save temporary files.
RM=${RM:-'rm -f'}

PATH=$PWD/src:$PATH
export PATH

ANGLE_UNIT=DEGREE
export ANGLE_UNIT

if ! (cd src;make) > /dev/null
then
    echo "make failed"
    exit 1
fi

rm -f angle.out
f="(%5.1f %5.1f) dir %3.0f go %3.0f deg => (%10.5f %10.5f)\n"
for lon in -179 -1 0 1 45 89 91 135 179 180 181 225 270 359
do
    for lat in -89 -45 -1 0 1 45 89
    do
	for dir in -270 -225 -135 -90 -45 0 45 90 135 180 225 270 360
	do
	    for d_deg in 0 10 80 100 170 190
	    do
		angle gc_step $lon $lat $dir $d_deg \
		    | (read lon2 lat2
			    printf "$f" $lon $lat $dir $d_deg $lon2 $lat2) \
			| sed -e 's/-180/ 180/' -e 's/-0/ 0/' >> angle.out
	    done
	done
    done
done

if gunzip -c geod.out.gz | diff angle.out - > /dev/null
then
    echo SUCCESS
else
    echo FAIL: angle.out and geod.out differ
fi

$RM angle.out
