#!/bin/bash




if [ $1'x' == 'cleanx' ];then
	rm *.log *.tar.gz  client server test_sqlite
	exit 0
fi
	

PATH_SQLITE=../sqlite/sqlite-snapshot-201703241759
PATH_SQLITE_LIBS=$PATH_SQLITE/.libs
CC="gcc"
CFLAG="-Wall -g -lpthread -lrt -Ihz_libc -lsqlite3 -L$PATH_SQLITE_LIBS -I$PATH_SQLITE"

SRCS_SERVER="server.c hz_libc/*.c"
SRCS_CLIENT="client.c hz_libc/*.c"
SRCS_TEST_SQLITE="test_sqlite.c  hz_libc/*.c"



TARGET_SERVER="server"
TARGET_CLIENT="client"
TARGET_TEST_SQLITE="test_sqlite"

SERVER_BUILD="$CC $SRCS_SERVER $CFLAG -o $TARGET_SERVER "
CLIENT_BUILD="$CC $SRCS_CLIENT $CFLAG -o $TARGET_CLIENT "

TEST_SQLITE_BUILD="$CC $SRCS_TEST_SQLITE $CFLAG -o $TARGET_TEST_SQLITE "


$SERVER_BUILD
$CLIENT_BUILD
$TEST_SQLITE_BUILD
