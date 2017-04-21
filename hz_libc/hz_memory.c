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



/**
hz_memcpy replace memcpy
@param dest arg2描述
@param src arg2描述
@return 返回值描述
*/
hz_ret_t hz_memcpy(d8 *dest,d8 * src,s32 length)
{
	hz_ret_t ret = RET_SUCCESS ;
	//s32 res = 0;
	s32 i = 0;
	if ( dest != NULL && src != NULL && length > 0)
	{
		for(;i < length; i++ )
		{
			*(dest+i) = *(src+i);
		}
		
	}else
	{
		ret = RET_ERR_MEMCPY;
	}
	
	
	return 0 - ret;	
}


hz_ret_t hz_memset(d8 *dest,d8 value,s32 length)
{
	hz_ret_t ret = RET_SUCCESS ;
	//s32 res = 0;
	s32 i = 0;
	if ( dest != NULL && length > 0  )
	{
		for(;i < length; i++ )
		{
			*(dest+i) = value;
		}
		
	}else
	{
		ret = RET_ERR_MEMSET;
	}	
	return 0 - ret;	
}


hz_ret_t hz_memdump(d8 *buf,s32 length)
{
	s32 i=0;
	hz_ret_t ret = RET_SUCCESS ;
	lt_info("dump buf=%p length=%d",buf,length) ;
	hz_log_lock();
	if ( buf != NULL && length > 0  )
	{
		for(;i< length;i++)
		{
			hzprintf("%02x ",(u8)*(buf+i) );
			if ( i % 30 == 29 ) hzprintf("\n");
		}
		hzprintf("\n");		
	}else
	{
		ret = RET_ERR_MEMDUMP;
	}
	hz_log_unlock();

	lt_info("dump done") ;
	return 0 - ret;
}


/**
*/
hz_ret_t hz_mem2str(hz_mem_str_o * mem_str)  //抽时间统一整理成面向对象格式
{
	hz_ret_t ret = RET_SUCCESS ;
	int i=0;
	if ( (mem_str->src_buf == NULL) ||  (mem_str->dest_buf == NULL)  || (mem_str->length > 4096) )
	{
		ret = RET_FAIL;		
	}else
	{
		for( i=0;i<mem_str->length;i++ )
		{
			hzsprintf(mem_str->dest_buf+i*2,"%02x",(u8)mem_str->src_buf[i]);
		}
		mem_str->dest_buf[i*2]=0;
	}
	return 0 - ret;
}

/**
*/
hz_ret_t hz_str2mem(hz_mem_str_o * mem_str)  //抽时间统一整理成面向对象格式
{
	hz_ret_t ret = RET_SUCCESS ;
	d8 tmp_buf[10];
	int i=0;
	if ( ( mem_str->src_buf == NULL ) ||  ( mem_str->dest_buf == NULL )  || ( mem_str->length > 4096 ) )
	{
		ret = RET_FAIL;		
	}else
	{
		for( i=0 ; i < mem_str->length ; i=i+2 )
		{
			hzsnprintf(tmp_buf,3,"%s",&mem_str->src_buf[i]);
			mem_str->dest_buf[i/2]=(u8)strtol(tmp_buf,NULL,16);
		}
	}
	return 0 - ret;
}

/**
rewrite    extern void *malloc(unsigned int num_bytes);
*/
void *hz_malloc(u32 num_bytes)
{
	return malloc( num_bytes);
}
/**
void free(void *ptr);
释放malloc(或calloc、realloc)函数给指针变量分配的内存空间的函数
使用后该指针变量一定要重新指向NULL，防止野指针出现，有效 规避误操作。
与malloc()函数配对使用，释放malloc函数申请的动态内存。（另：对于free(p)这句语句，如果p 是NULL 指针，那么free 对p 无论操作多少次都不会出问题。如果p 不是NULL 指针，那么free 对p连续操作两次就会导致程序运行错误。）
hz_free(ptr);
ptr=NULL;
*/
void hz_free(void *ptr)
{
	free( ptr);
}

void hz_freepp(void **ptr)
{
	free( *ptr);
	*ptr = NULL;
}

