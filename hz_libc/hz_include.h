/*******************************************************************
Copyright (C) hz
Version:      v0.0.1
FileInfo------------------------------------------------------------
Filename:     
Author:       liusonghua
Date:         
OS:           Linux-3.3.0
Complier:     arm-linux-gnueabi-gcc (version: 4.6.3)
HardWare:     
Version :     v0.0.1
Description:  TYPE.h
History------------------------------------------------------------
Author:
Date:
Version:
Description:
*******************************************************************/


#ifndef __HZ_INCLUDE_H__
#define __HZ_INCLUDE_H__

#include <stdio.h>
#include <string.h>

/**
	malloc free use
*/
#include <stdlib.h>
//#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/*
没有此头文件则调用  inet_ntoa  会报Segmentation fault
*/
#include <arpa/inet.h>
#include <pthread.h>
#include <errno.h>


/**
stdlib.h
system()
*/
#include <stdlib.h>

/**
sqlite3
*/
#ifndef HZ_LIBC_NO_SQLITE
	#include "sqlite3.h"
#endif

/**
flock
*/
#include <sys/file.h>



#include "hz_type.h"
#include "hz_log.h"
#include "hz_string.h"
#include "hz_file.h"
#include "hz_socket.h"
#include "hz_memory.h"
#include "hz_thread.h"

#ifndef HZ_LIBC_NO_SQLITE
	#include "hz_sqlite.h"
#endif

#include "hz_semaphore.h"
#include "cJSON.h"
#include "hz_cjson.h"



#endif /* !__TYPE_H__ */
