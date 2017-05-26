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
#ifndef __HZ_MEMORY_H__
#define __HZ_MEMORY_H__

/*

*/




hz_ret_t hz_memcpy(d8 *dest,d8 * src,s32 length);

hz_ret_t hz_memset(d8 *dest,d8 value,s32 length);
hz_ret_t hz_memdump(d8 *buf,s32 length);


typedef struct __hz_mem_str_o__
{
	d8 name[16];
	void *new;
	d8 *src_buf;
	d8 *dest_buf;
	u32 length; //limite 4096
}hz_mem_str_o;
hz_ret_t hz_mem2str(hz_mem_str_o * mem2str);
hz_ret_t hz_str2mem(hz_mem_str_o * mem_str);
void *hz_malloc(u32 num_bytes);


#endif /* !__HZ_STRING_H__ */
