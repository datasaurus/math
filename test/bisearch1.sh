#!/bin/sh
#
#- bisearch1.sh --
#-	This test application tests bisection search functions defined in
#-	bisearch_lib.c.
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
# $Revision: 1.4 $ $Date: 2009/12/16 17:10:46 $
#
########################################################################

echo "
bisearch1.sh --

This test application tests bisection search functions defined in bisearch_lib.c.
See bisearch_lib (3) and bisearch (1) for more information.

It builds and runs the bisearch application.

Usage suggestions:
./bisearch1.sh 2>&1 | less
To save temporary files:
env RM=: ./bisearch1.sh 2>&1 | less

Copyright (c) 2009 Gordon D. Carrie
All rights reserved

################################################################################
"

# Set RM to : in environment to save temporary files.
RM=${RM:-'rm -f'}

if ! (cd src;make bisearch) > /dev/null
then
    echo "make failed"
    exit 1
fi
export PATH=$PWD/src:$PATH

echo "Starting test1 - search ascending array"
cat > correct1 << EOF
-1
0
0
0
1
2
3
3
4
6
-1
-1
EOF
cat > count1 << EOF
3
1
1
2
1
0
1
EOF
printf -- "-9.0  -2.3  -1.2 -1.1  -0.9  0.0  1.1  1.2  1.5  4.3  8.0  9.8" \
	   | bisearch  -2.3  -1.0  0.0  1.0  1.5  2.0  4.1  8.0 3> count1.try \
	   | if diff correct1 -
	   then
	       echo test1 produced correct bin output
	   else
	       echo test1 produced incorrect bin output
	   fi
if diff count1 count1.try
then
   echo test1 produced correct counts
else
   echo test1 produced incorrect counts
fi
echo ""
$RM correct1 count1 count1.try

echo "Starting test2 - search descending array"
cat > correct2 << EOF
-1
0
0
2
2
5
5
6
-1
-1
EOF
cat > count2 << EOF
2
0
2
0
0
2
1
EOF
printf -- "9.8  8.0  4.3  1.5  1.1  0.0  -0.9  -1.1  -2.3  -9.0" \
	   | bisearch 8.0  4.1  2.0  1.0  1.5  0.0  -1.0  -2.3 3> count2.try \
	   | if diff correct2 -
	   then
	       echo test2 produced correct bin output
	   else
	       echo test2 produced incorrect output
	   fi
if diff count2 count2.try
then
   echo test2 produced correct counts
else
   echo test2 produced incorrect counts
fi
$RM correct2 count2 count2.try
