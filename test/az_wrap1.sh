#!/bin/sh
#
#- angle_wrapaz1.sh --
#-	This test application tests conversion functions defined in angle_lib.c.
#-	Specifically, it tests the Angle_WrapAz function.
#-
# Copyright (c) 2009 Gordon D. Carrie
# All rights reserved
#
# Please send feedback to dev0@trekix.net
#
# $Revision: 1.6 $ $Date: 2009/11/25 20:53:33 $
#
########################################################################

echo "
angle_wrapaz1.sh --

This test application tests conversion functions defined in angle_lib.c.
Specifically, it tests the Angle_WrapAz function.
See angle_lib (3) and angle (1) for more information.

It reads azimuths from a local input file and puts them into various
azimuth domains.

Usage suggestions:
./angle_wrapaz1.sh 2>&1 | less
To save temporary files:
env RM=: ./angle_wrapaz1.sh 2>&1 | less

Copyright (c) 2009 Gordon D. Carrie
All rights reserved

################################################################################
"

# Set RM to : in environment to save temporary files.
RM=${RM:-'rm -f'}

if ! (cd src;make) > /dev/null
then
    echo "make failed"
    exit 1
fi
export PATH=$PWD/src:$PATH

export ANGLE_UNIT="DEGREE"

# Test input.  Columns: azimuth reference_azimuth angle_wrapaz_result
cat > input << END
 -730.0    0.0  -10.0
 -720.0    0.0    0.0
 -370.0    0.0  -10.0
 -360.0    0.0    0.0
 -350.0    0.0   10.0
 -190.0    0.0  170.0
 -180.0    0.0 -180.0
 -170.0    0.0 -170.0
  -10.0    0.0  -10.0
   -0.0    0.0    0.0
    0.0    0.0    0.0
   10.0    0.0   10.0
  170.0    0.0  170.0
  180.0    0.0 -180.0
  190.0    0.0 -170.0
  350.0    0.0  -10.0
  360.0    0.0    0.0
  370.0    0.0   10.0
  720.0    0.0    0.0
  730.0    0.0   10.0
 -730.0   10.0  -10.0
 -720.0   10.0    0.0
 -370.0   10.0  -10.0
 -360.0   10.0    0.0
 -350.0   10.0   10.0
 -190.0   10.0  170.0
 -180.0   10.0  180.0
 -170.0   10.0 -170.0
  -10.0   10.0  -10.0
   -0.0   10.0    0.0
    0.0   10.0    0.0
   10.0   10.0   10.0
  170.0   10.0  170.0
  180.0   10.0  180.0
  190.0   10.0 -170.0
  350.0   10.0  -10.0
  360.0   10.0    0.0
  370.0   10.0   10.0
  720.0   10.0    0.0
  730.0   10.0   10.0
 -730.0  180.0  350.0
 -720.0  180.0    0.0
 -370.0  180.0  350.0
 -360.0  180.0    0.0
 -350.0  180.0   10.0
 -190.0  180.0  170.0
 -180.0  180.0  180.0
 -170.0  180.0  190.0
  -10.0  180.0  350.0
   -0.0  180.0    0.0
    0.0  180.0    0.0
  180.0  180.0  180.0
  170.0  180.0  170.0
  180.0  180.0  180.0
  190.0  180.0  190.0
  350.0  180.0  350.0
  360.0  180.0    0.0
  370.0  180.0   10.0
  720.0  180.0    0.0
  730.0  180.0   10.0
END

# For each line of input, give first and second column to 'angle az_wrap'.
# Compare result with third column.
echo Starting test1
awk '{print $1, $2}' input | while read l r
do
    printf '%7.1f%7.1f%7.1f\n' $l $r `angle az_wrap $l $r`
done | if diff input -
then
    echo test1 produced good output
else
    echo test1 produced incorrect output
fi

# Check for failure with bad angle unit.
echo Starting test2
export ANGLE_UNIT="DEGREES"
r=`angle az_wrap 0 0 2>&1`
if [ $? == 0 ]
then
    echo test2 FAIL: angle succeeded when it should have reported bad unit
elif [ "$r" != "angle: Unknown angle unit DEGREES." ]
then
    echo test2 FAIL: angle gave incorrect error message
else
    echo test2 succeeded
fi

$RM input
