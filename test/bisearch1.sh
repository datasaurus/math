#!/bin/sh
#
#- bisearch1.sh --
#-	This test application tests bisection search functions defined in
#-	bisearch_lib.c.
#-
# Copyright (c) 2009 Gordon D. Carrie
# All rights reserved
#
# Please send feedback to dev0@trekix.net
#
# $Revision: $ $Date: $
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

if ! (cd src;make) > /dev/null
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
1
2
3
4
6
-1
-1
EOF
printf "-9.0  -2.3  -1.1  -0.9  0.0  1.1  1.5  4.3  8.0  9.8" \
	   | bisearch  -2.3  -1.0  0.0  1.0  1.5  2.0  4.1  8.0 \
	   | if diff correct1 -
	   then
	       echo test1 produced good output
	   else
	       echo test1 produced incorrect output
	   fi
echo ""

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
printf "9.8  8.0  4.3  1.5  1.1  0.0  -0.9  -1.1  -2.3  -9.0" \
	   | bisearch 8.0  4.1  2.0  1.0  1.5  0.0  -1.0  -2.3 \
	   | if diff correct2 -
	   then
	       echo test2 produced good output
	   else
	       echo test2 produced incorrect output
	   fi

$RM correct1 correct2
