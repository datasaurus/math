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

EXECS = angle bighi biglrg biglo bigsml bisearch bin_grid arr32

CC = cc -std=c99
CFLAGS = -g -Wall -Wmissing-prototypes

all : ${EXECS}

arr32 : arr32.c
	${CC} ${CFLAGS} -o arr32 arr32.c

BIN_GRID_OBJ = bin_grid.o bisearch_lib.o
bin_grid : ${BIN_GRID_OBJ}
	${CC} ${CFLAGS} -o bin_grid ${BIN_GRID_OBJ} -lm

bin_grid.o : bin_grid.c
	${CC} ${CFLAGS} -c bin_grid.c

bighi : bighi.c
	${CC} ${CFLAGS} -o bighi bighi.c -lm

biglo : biglo.c
	${CC} ${CFLAGS} -o biglo biglo.c -lm

biglrg : biglrg.c
	${CC} ${CFLAGS} -o biglrg biglrg.c -lm

bigsml : bigsml.c
	${CC} ${CFLAGS} -o bigsml bigsml.c -lm

bisearch : bisearch_app.o bisearch_lib.o
	${CC} ${CFLAGS} -o bisearch bisearch_app.o bisearch_lib.o

bisearch_app.o : bisearch_app.c bisearch_lib.h
	${CC} ${CFLAGS} -c bisearch_app.c

bisearch_lib.o : bisearch_lib.c bisearch_lib.h
	${CC} ${CFLAGS} -c bisearch_lib.c

ANGLE_OBJ = angle_app.o angle_lib.o
angle : ${ANGLE_OBJ}
	${CC} ${CFLAGS} -o angle ${ANGLE_OBJ} -lm

angle_app.o : angle_app.c angle_lib.h
	${CC} ${CFLAGS} -c angle_app.c

angle_lib.o : angle_lib.c angle_lib.h
	${CC} ${CFLAGS} -c angle_lib.c

clean :
	rm -fr ${EXECS} bisearch *core* *.o *.dSYM
