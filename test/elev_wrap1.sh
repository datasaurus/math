#!/bin/sh
#
#- angle_wrapelev.sh --
#-	This test application tests conversion functions defined in angle_lib.c.
#-	Specifically, it tests the Angle_WrapElev.
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
# $Revision: 1.6 $ $Date: 2009/12/11 19:49:42 $
#
########################################################################

echo "
angle_wrapelev.sh --

This test application tests conversion functions defined in angle_lib.c.
Specifically, it tests the Angle_WrapElev.
See angle_lib (3) and angle (1) for more information.

It reads elevations from a local input file and puts them into the range [-90, 90).

Usage suggestions:
./angle_wrapelev.sh 2>&1 | less
To save temporary files:
env RM=: ./angle_wrapelev.sh 2>&1 | less

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

# Test input.  Columns: longitude reference_longitude angle_evel_wrap_result
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

# For each line of input, give first and second column to 'angle evel_wrap'.
# Compare result with third column.
awk '{print $1}' input | while read l
do
    printf '%7.1f%7.1f\n' $l `angle elev_wrap $l`
done | if diff input -
then
    echo test1 produced good output
else
    echo test1 produced incorrect output
fi

$RM input
