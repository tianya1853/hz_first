#!/bin/bash
CC="gcc"
CFLAG="-Wall -g -lpthread -lrt -Ihz_libc"

SRCS_SERVER="server.c hz_libc/*.c"
SRCS_CLIENT="client.c hz_libc/*.c"
TARGET_SERVER="server"
TARGET_CLIENT="client"


SERVER_BUILD="$CC $SRCS_SERVER $CFLAG -o $TARGET_SERVER "
CLIENT_BUILD="$CC $SRCS_CLIENT $CFLAG -o $TARGET_CLIENT "




$SERVER_BUILD
$CLIENT_BUILD
