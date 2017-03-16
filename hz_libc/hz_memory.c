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

	if ( buf != NULL && length > 0  )
	{
		for(;i< length;i++)
		{
			hzprintf("%02x ",(u8)*(buf+i) );
			if ( i % 10 == 9 ) hzprintf("\n");
		}
		hzprintf("\n");		
	}else
	{
		ret = RET_ERR_MEMDUMP;
	}



	lt_info("dump done") ;
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

