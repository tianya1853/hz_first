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
Description:  module.c
History------------------------------------------------------------
Author:
Date:
Version:
Description:
*******************************************************************/

#include "hz_include.h"


  
s32 hz_mutex_init(hz_mutex_t *mutex,const hz_mutexattr_t *attr)
{
	mutex->flag = 1;
	return pthread_mutex_init(&(mutex->lock),NULL);
}


s32 hz_mutex_lock(hz_mutex_t *mutex)
{
	if ( mutex->flag == 1 )
	{
		return pthread_mutex_lock(&(mutex->lock));
	}else
	{
		//lt_warn("uninit mutex");  can not use lt_warn , had used hz_mutex_lock & hz_mutex_unlock  in lt_warn
		//if (   0 != strncmp(mutex->name,"lt_log", sizeof("lt_log")  )    )   //it is invalid
		{
			// invalid
			//hzprintf("warning:uninit mutex %s\n",mutex->name);
		}
			
		return 0;
	}
}

s32 hz_mutex_unlock(hz_mutex_t *mutex)
{
	if ( mutex->flag == 1 )
	{
		return pthread_mutex_unlock(&(mutex->lock));
	}else
	{
		//lt_warn("uninit mutex"); can not use lt_warn , had used hz_mutex_lock & hz_mutex_unlock  in lt_warn
		//hzprintf("warning:uninit mutex %s\n",mutex->name);
		if (   0 != strncmp(mutex->name,"lt_log", sizeof("lt_log")  )    )
		{//
			hzprintf("warning:uninit mutex %s\n",mutex->name);
		}
		return 0;
	}	
}


/*
  //int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t * attr)
　　int pthread_mutex_lock(pthread_mutex_t *mutex)

　　int pthread_mutex_unlock(pthread_mutex_t *mutex)

　　int pthread_mutex_trylock(pthread_mutex_t *mutex)
pthread_mutex_t lock;

pthread_mutex_int(&lock, NULL);

...

pthread_mutex_lock(&lock);

...

pthread_mutex_unlock(&lock);

...

pthread_mutex_destroy(&lock);
*/



