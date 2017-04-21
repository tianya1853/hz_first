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
Description:  type.c
History------------------------------------------------------------
Author:
Date:
Version:
Description:
*******************************************************************/

#include "hz_type.h"
#include "hz_memory.h"
/**
module函数功能描述
@param arg1 arg2描述  
@param arg2 arg2描述
@return 返回值描述
*/
void hz_tmp_o_init(hz_tmp_o *hz_tmp)
{
	hz_memset((d8 *)hz_tmp,0,sizeof(hz_tmp_o));
	hz_tmp->casx = CASX_INIT ;
}



