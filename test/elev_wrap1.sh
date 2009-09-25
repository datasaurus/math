#!/bin/sh
#
#- plat1.sh --
#-	This test application tests conversion functions defined in geog_lib.c.
#-	Specifically, it tests the plat (principal latitude function).
#-
# Copyright (c) 2009 Gordon D. Carrie
# All rights reserved
#
# Please send feedback to dev0@trekix.net
#
# $Revision: 1.2 $ $Date: 2009/07/10 22:02:14 $
#
########################################################################

echo "
plat1.sh --

This test application tests conversion functions defined in geog_lib.c.
Specifically, it tests the plat (principal latitude function).
See geog_lib (3) and geog (1) for more information.

It reads latitudes from a local input file and puts them into
the range -90 <= lat <= 90

Usage suggestions:
./plat1.sh 2>&1 | less
To save temporary files:
env RM=: ./plat1.sh 2>&1 | less

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

# Test input.  Columns: longitude reference_longitude geog_plat_result
cat > input << END
 -370.0  -10.0
 -360.0    0.0
 -350.0   10.0
 -190.0   10.0
 -180.0    0.0
 -170.0  -10.0
 -100.0  -80.0
  -90.0  -90.0
  -80.0  -80.0
  -10.0  -10.0
   -0.0    0.0
    0.0    0.0
   10.0   10.0
   80.0   80.0
   90.0   90.0
  100.0   80.0
  170.0   10.0
  180.0    0.0
  190.0  -10.0
  350.0  -10.0
  360.0    0.0
  370.0   10.0
END

# For each line of input, give first and second column to 'geog plat'.
# Compare result with third column.
awk '{print $1}' input | while read l
do
    printf '%7.1f%7.1f\n' $l $r `geog plat -f '%10.4f' $l`
done | if diff input -
then
    echo test1 produced good output
else
    echo test1 produced incorrect output
fi

$RM input
