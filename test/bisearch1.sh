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
# $Revision: 1.5 $ $Date: 2011/11/28 16:43:52 $
#
########################################################################

echo "
bisearch1.sh --

This test application tests bisection search functions defined in bisearch_lib.c.
See bisearch_lib (3) and bisearch (1) for more information.

It builds and runs the bisearch application for some simple sequences of
float values.

Copyright (c) 2009 Gordon D. Carrie
All rights reserved

################################################################################
"

if ! (cd src;make bisearch) > /dev/null
then
    echo "make failed"
    exit 1
fi
export PATH=$PWD/src:$PATH

array="-2.30 -1.00 0.00 1.00 1.50 2.00 4.10 8.00"
keys="-9.00 -2.30 -1.20 -1.10 -0.90 0.00 1.10 1.20 1.50 4.30 8.00 9.80"
printf "Searching $array\n    for $keys\n"
printf -- "$keys" | bisearch $array

printf "\n------------------------------------\n\n"

array="8.00 4.10 2.00 1.00 1.50 0.00 -1.00 -2.30"
keys="9.80 8.00 4.30 1.50 1.10 0.00 -0.90 -1.10 -2.30 -9.00"
printf "Searching $array\n    for $keys\n"
printf -- "$keys" | bisearch $array

