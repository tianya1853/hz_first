#!/bin/bash


PATH_SQLITE=../sqlite/sqlite-snapshot-201703241759
PATH_SQLITE_LIBS=$PATH_SQLITE/.libs

CC="gcc"
CFLAG="-Wall -g -lpthread -lrt -Ihz_libc  -lsqlite3 -L$PATH_SQLITE_LIBS -I$PATH_SQLITE"

#SRCS_SERVER="server_dw.c hz_libc/*.c"
SRCS_CLIENT="client_press.c hz_libc/*.c"
TARGET_SERVER="server"
TARGET_CLIENT="client_press"


#SERVER_BUILD="$CC $SRCS_SERVER $CFLAG -o $TARGET_SERVER "
CLIENT_BUILD="$CC $SRCS_CLIENT $CFLAG -o $TARGET_CLIENT "




#$SERVER_BUILD
$CLIENT_BUILD
