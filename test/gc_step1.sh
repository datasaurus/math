#!/bin/sh
#
#-	step1.sh --
#-		Test "angle gc_step" function.
#-
#	Copyright (c) 2009 Gordon D. Carrie
#	All rights reserved
#
#	Please send feedback to dev0@trekix.net
#
#	$Revision: 1.2 $ $Date: 2009/11/25 20:53:33 $
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
