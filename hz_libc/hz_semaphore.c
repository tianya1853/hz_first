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

#include "hz_include.h"


hz_ret_o hz_file_lock(hz_flock_o *obj)
{
	hz_ret_o ret;
	//hz_tmp_o tmp;

	ret.v = RET_SUCCESS;
	//tmp.casx=CASX_INIT;
	obj->flag_lock = HZ_FAIL;
	do
	{
		if ( SUCCESS == file_exist(obj->filename) )
		{			
		}else
		{
			ret.v = RET_FAIL;
			break;
			//system("touch obj->filename")
		}
		obj->fp = fopen(obj->filename,"r");  
		if( obj->fp == NULL )  
		{  
			lt_error("open file error!\n");  
			//exit(1);  
			ret.v = RET_FAIL;
			break;
		} 
		obj->fd = fileno(obj->fp);  

		if(0 == flock(obj->fd,LOCK_EX)) //mutex 
		{			
			obj->flag_lock = HZ_SUCCESS;
		}else
		{
			fclose(obj->fp);  
			obj->fp = NULL;
			obj->fd = 0;
			lt_error("failing to lock %s\n ",obj->filename);  
			obj->flag_lock = HZ_FAIL;			
		}
	}while(0);
	
	ret.v=0-ret.v;
	return ret;	
}

hz_ret_o hz_file_unlock(hz_flock_o *obj)
{
	hz_ret_o ret;
	ret.v = RET_SUCCESS;
	
	do
	{
		if( obj->flag_lock == HZ_SUCCESS )
		{
			if ( 0 == flock(obj->fd,LOCK_UN) )
			{
				fclose(obj->fp);  
				obj->fp = NULL;
				obj->fd = 0;
			}else
			{
				ret.v = RET_FAIL;
				lt_error("failing to unlock %s\n ",obj->filename);  
			}
		}else
		{
			ret.v = RET_FAIL;
		}
	}while(0);
	
	ret.v=0-ret.v;
	return ret;	
}





