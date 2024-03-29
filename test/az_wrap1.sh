#!/bin/sh
#
#- angle_wrapaz1.sh --
#-	This test application tests conversion functions defined in angle_lib.c.
#-	Specifically, it tests the Angle_WrapAz function.
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
# Please send feedback to dev0@trekix.net
#
# $Revision: 1.9 $ $Date: 2011/11/28 16:43:52 $
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
export ANGLE_UNIT="DEGREE"
awk '{print $1, $2}' input | while read l r
do
    printf '%7.1f%7.1f%7.1f\n' $l $r `angle az_wrap $l $r`
done | if diff input -
then
    echo test1 produced good output
else
    echo test1 produced incorrect output
fi
$RM input

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

# Check for round off error at edges
export ANGLE_UNIT="RADIAN"
a=`angle az_wrap -2.94159265358979323846 0.2`
if [ "`printf '%.5g' $a`" != "-2.9416" ]
then
    echo "angle az_wrap -2.94159265358979323846 0.2 returned $a => FAILED."
else
    echo "angle az_wrap -2.94159265358979323846 0.2 succeeded."
fi
export ANGLE_UNIT="DEGREE"
a=`angle az_wrap -170.0 10.0`
if [ "`printf '%.1f' $a`" != "-170.0" ]
then
    echo angle az_wrap -170.0 10.0 FAILED.
else
    echo angle az_wrap -170.0 10.0 succeeded.
fi
