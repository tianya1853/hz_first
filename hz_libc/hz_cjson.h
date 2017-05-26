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
Description:  TYPE.h
History------------------------------------------------------------
Author:
Date:
Version:
Description:
*******************************************************************/
#ifndef __HZ_CJSON_H__
#define __HZ_CJSON_H__
#include "hz_type.h"
#include "cJSON.h"
/**
## 自动模式下的内存管理
在自动模式下，cJSON使用默认的malloc和free函数管理内存。
在cJSON中，每个节点都是malloc而来，每个节点的string和valuestring也是malloc而来。
使用cJSON库中，使用cJSON_Delete函数可以递归释放JSON树中malloc的节点内存和字符内存。
当使用cJSON_Print函数后，需要手动释放cJSON_Print函数分配的内存，避免内存泄露。
*/


typedef struct hz_cjson_o_
{
	//hz_object obj;
	d8 filename[128];
	cJSON *cjson_root; //need free ; need set to 0 when free it
	d8 * cjson_out;
	//d8 * cjson_text;//not need free;
	//d8 *retbuf;
	//FILE *fp;
	//s32 file_size;
}hz_cjson_o;
void hz_cjson_dofile(hz_cjson_o *hz_cjson);

#endif
