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
Description:  module.h
History------------------------------------------------------------
Author:
Date:
Version:
Description:
*******************************************************************/



#ifndef __SEM_H__
#define __SEM_H__

#include <semaphore.h>

typedef struct _hz_sem_o_
{
	d8 name[16];
	sem_t sem;	
}hz_sem_o;


typedef struct _hz_mutex_o_
{

}hz_mutex_o;

typedef struct _hz_flock_o_
{
	d8 filename[128];
	FILE *fp;	
	s32 fd;
	s32 flag; // 1:inited  0:no init
	s32 flag_lock;
}hz_flock_o;


hz_ret_o hz_file_lock(hz_flock_o *obj);
hz_ret_o hz_file_unlock(hz_flock_o *obj);




#endif
