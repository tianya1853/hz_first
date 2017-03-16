#ifndef __HZ_INCLUDE_H__
#define __HZ_INCLUDE_H__

#include <stdio.h>
#include <string.h>
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



#include "hz_type.h"
#include "hz_log.h"
#include "hz_string.h"
#include "hz_file.h"
#include "hz_socket.h"
#include "hz_memory.h"
#include "hz_thread.h"



#endif /* !__TYPE_H__ */
