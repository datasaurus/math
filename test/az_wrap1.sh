#!/bin/sh
#
#- lonr1.sh --
#-	This test application tests conversion functions defined in geog_lib.c.
#-	Specifically, it tests the lonr (longitude reference function).
#-
# Copyright (c) 2009 Gordon D. Carrie
# All rights reserved
#
# Please send feedback to dev0@trekix.net
#
# $Revision: 1.5 $ $Date: 2009/11/10 20:01:55 $
#
########################################################################

echo "
lonr1.sh --

This test application tests conversion functions defined in geog_lib.c.
Specifically, it tests the lonr (longitude reference function).
See geog_lib (3) and geog (1) for more information.

It reads longitudes from a local input file and puts them into various
longitude domains.

Usage suggestions:
./lonr1.sh 2>&1 | less
To save temporary files:
env RM=: ./lonr1.sh 2>&1 | less

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

# Test input.  Columns: longitude reference_longitude geog_lonr_result
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

# For each line of input, give first and second column to 'geog lonr'.
# Compare result with third column.
echo Starting test1
awk '{print $1, $2}' input | while read l r
do
    printf '%7.1f%7.1f%7.1f\n' $l $r `geog lonr $l $r`
done | if diff input -
then
    echo test1 produced good output
else
    echo test1 produced incorrect output
fi

# Check for failure with bad angle unit.
echo Starting test2
export ANGLE_UNIT="DEGREES"
r=`geog lonr 0 0 2>&1`
if [ $? == 0 ]
then
    echo test2 FAIL: geog succeeded when it should have reported bad unit
elif [ "$r" != "geog: Unknown angle unit DEGREES." ]
then
    echo test2 FAIL: geog gave incorrect error message
else
    echo test2 succeeded
fi

$RM input
