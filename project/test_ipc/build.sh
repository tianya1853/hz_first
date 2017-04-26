#!/bin/bash

PATH_TOP=../..


if [ $1'x' == 'cleanx' ];then
	rm *.log  test_ipc *~
	exit 0
fi
	

PATH_SQLITE=$PATH_TOP/sqlite/sqlite-snapshot-201703241759
PATH_SQLITE_LIBS=$PATH_SQLITE/.libs
CC="gcc"
CFLAG="-Wall -g -lpthread -lrt -I$PATH_TOP/hz_libc -lsqlite3 -L$PATH_SQLITE_LIBS -I$PATH_SQLITE"

SRCS_TEST="test_ipc.c $PATH_TOP/hz_libc/*.c"

TARGET_TEST="test_ipc"
TEST_BUILD="$CC $SRCS_TEST $CFLAG -o $TARGET_TEST"

$TEST_BUILD

