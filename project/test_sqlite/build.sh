#!/bin/bash

PATH_TOP=../..


if [ $1'x' == 'cleanx' ];then
	rm *.log *.tar.gz  client server rm *~
	exit 0
fi
	

PATH_SQLITE=$PATH_TOP/sqlite/sqlite-snapshot-201703241759
PATH_SQLITE_LIBS=$PATH_SQLITE/.libs
CC="gcc"
CFLAG="-Wall -g -lpthread -lrt -I$PATH_TOP/hz_libc -lsqlite3 -L$PATH_SQLITE_LIBS -I$PATH_SQLITE"

#SRCS_SERVER="server.c $PATH_TOP/hz_libc/*.c"
#SRCS_CLIENT="client.c $PATH_TOP/hz_libc/*.c"
SRCS_TEST_SQLITE="test_sqlite.c  $PATH_TOP/hz_libc/*.c"



#TARGET_SERVER="server"
#TARGET_CLIENT="client"
TARGET_TEST_SQLITE="test_sqlite"

#SERVER_BUILD="$CC $SRCS_SERVER $CFLAG -o $TARGET_SERVER "
#CLIENT_BUILD="$CC $SRCS_CLIENT $CFLAG -o $TARGET_CLIENT "

TEST_SQLITE_BUILD="$CC $SRCS_TEST_SQLITE $CFLAG -o $TARGET_TEST_SQLITE "


#$SERVER_BUILD
#$CLIENT_BUILD
$TEST_SQLITE_BUILD
