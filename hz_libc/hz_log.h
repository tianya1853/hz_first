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
#ifndef __HZ_LOG_H__
#define __HZ_LOG_H__
#include <stdio.h>
#include <unistd.h>
#include "hz_type.h"
#include "hz_thread.h"
//#define TEST_MODE  1

extern hz_mutex_t mutex_print;

typedef enum 
{
	LT_ERROR,
	LT_WARNING,
	LT_INFO,
	LT_DEBUG,
}hz_log_t;


s32 hzprintf(char *fmt, ...);


extern int lt_runtime(lt_time_t *lt_time,s32 printtime);

#if 0
#define lt_log(lt,fmt...)                                         \
do{                                                               \
    {                                                             \
	lt_runtime(NULL,1);                                       \
        hzprintf("[%s][line_%d]<%s:",__FILE__,__LINE__,#lt);      \
        hzprintf(fmt);                                            \
        hzprintf("\n");                                           \
    }                                                             \
                                                                  \
}while(0)
#else

#define lt_log(lt,fmt...)                                         \
do{                                                               \
    {                                                             \
	hz_mutex_lock(&mutex_print);    			  \
	lt_runtime(NULL,1);                                       \
        hzprintf("[%s][%s][line_%d]<%s:",__FILE__,__FUNCTION__,__LINE__,#lt);      \
        hzprintf(fmt);                                            \
        hzprintf("\n");                                           \
	hz_mutex_unlock(&mutex_print); 				  \
    }                                                             \
                                                                  \
}while(0)

#endif




#define DEBUG_LEVEL 4

//#define dprintf(fmt...) do{hzprintf("[%s][line_%d]",__FILE__,__LINE__);hzprintf(fmt);hzprintf("\n");}while(0)


#if 0

#define lt_debug(fmt...)                                          \
do{                                                               \
    if( DEBUG_LEVEL >=4 ) 		                          \
    {                                                             \
	lt_runtime(NULL,1);                                       \
        hzprintf("[%s][%s][line_%d]<debug:",__FILE__,__FUNCTION__,__LINE__);       \
        hzprintf(fmt);                                            \
        hzprintf("\n");                                           \
    }                                                             \
                                                                  \
}while(0)


#define lt_info(fmt...)                                           \
do{                                                               \
    if( DEBUG_LEVEL >=3 ) 		                          \
    {                                                             \
	lt_runtime(NULL,1);                                       \
        hzprintf("[%s][%s][line_%d]<info:",__FILE__,__FUNCTION__,__LINE__);       \
        hzprintf(fmt);                                            \
        hzprintf("\n");                                           \
    }                                                             \
}while(0)



#define lt_warn(fmt...)                                           \
do{                                                               \
    if( DEBUG_LEVEL >=2 ) 		                          \
    {                                                             \
	lt_runtime(NULL,1);                                       \
        hzprintf("[%s][%s][line_%d]<warn:",__FILE__,__FUNCTION__,__LINE__);       \
        hzprintf(fmt);                                            \
        hzprintf("\n");                                           \
    }                                                             \
}while(0)



#define lt_error(fmt...)                                          \
do{                                                               \
    if( DEBUG_LEVEL >=1 ) 		                          \
    {                                                             \
	lt_runtime(NULL,1);                                       \
        hzprintf("[%s][%s][line_%d]<error:",__FILE__,__FUNCTION__,__LINE__);       \
        hzprintf(fmt);                                            \
        hzprintf("\n");                                           \
    }                                                             \
}while(0)
                             


#else

#define lt_debug(fmt...)    do{ if( DEBUG_LEVEL >=4 ){lt_log("debug",fmt);} }while(0)
#define lt_info(fmt...)    do{ if( DEBUG_LEVEL >=3 ){lt_log("info",fmt);} }while(0)
#define lt_warn(fmt...)    do{ if( DEBUG_LEVEL >=2 ){lt_log("warn",fmt);} }while(0)
#define lt_error(fmt...)    do{ if( DEBUG_LEVEL >=1 ){lt_log("error",fmt);} }while(0)

#endif



                 

extern int lt_sleep(int delay_s);
extern int lt_msleep(int delay_ms);
extern int lt_usleep(int delay_us);
extern s32 hz_log_init(int level,char *path_log,char *file_name_log);

#endif
