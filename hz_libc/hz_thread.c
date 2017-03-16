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
	return pthread_mutex_init(&(mutex->lock),NULL);
}


s32 hz_mutex_lock(hz_mutex_t *mutex)
{
	return pthread_mutex_lock(&(mutex->lock));
}

s32 hz_mutex_unlock(hz_mutex_t *mutex)
{
	return pthread_mutex_unlock(&(mutex->lock));
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



