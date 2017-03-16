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







#endif /* !__HZ_STRING_H__ */
