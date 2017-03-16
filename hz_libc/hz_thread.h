/*******************************************************************
Copyright (C) hz
Version:      v0.0.1
FileInfo------------------------------------------------------------
Filename:     
Author:       hz
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





#ifndef __HZ_THREAD_H__
#define __HZ_THREAD_H__

/**
@brief hz_thread_t
*/
typedef struct _hz_thread_t_
{
	pthread_t thread_handle;	
	void *(*thread_f)(void*);
	void *thread_arg;
	void *thread_result;
}hz_thread_t;



typedef struct _hz_mutex_t_ 
{   
	int sum;  
	pthread_mutex_t lock;  
}hz_mutex_t;

typedef struct _hz_mutexattr_t_ 
{  
	pthread_mutexattr_t att;  
}hz_mutexattr_t ;
 
s32 hz_mutex_init(hz_mutex_t *mutex,const hz_mutexattr_t *attr);
s32 hz_mutex_lock(hz_mutex_t *mutex);
s32 hz_mutex_unlock(hz_mutex_t *mutex);


#endif
