

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



