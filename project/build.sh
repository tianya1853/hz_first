#!/bin/bash

PATH_TOP=../..


if [ $1'x' == 'cleanx' ];then
	rm *.log *.tar.gz  client server rm *~
	exit 0
fi
	

PATH_SQLITE=$PATH_TOP/sqlite/sqlite-snapshot-201703241759
PATH_SQLITE_LIBS=$PATH_SQLITE/.libs
CC="gcc"
CFLAG="-Wall -g -lpthread -lrt -lm -I$PATH_TOP/hz_libc -lsqlite3 -L$PATH_SQLITE_LIBS -I$PATH_SQLITE"

TARGET_TEST=test
SRCS_TEST="test_cjson.c  hz_libc/*.c"

TEST_BUILD="$CC $SRCS_TEST $CFLAG -o $TARGET_TEST "

$TEST_BUILD
