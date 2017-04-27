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
module函数功能描述
@param arg1 arg2描述  
@param arg2 arg2描述
@return 返回值描述
*/
hz_ret_t module_function(s8 * arg1,u32 arg2)
{
	hz_ret_t ret = RET_SUCCESS ;
	s32 res = 0;
	s32 i = 0;
	//s32 stmp = 0;
	//u32 utmp = 0;

	//FILE *fp;
	s32 casx=CASX_INIT;


	do
	{
		ret = ret;
		res = res;
		i = i;
	}while(0);

	while( casx )
	{
		switch(casx)
		{
		case CASX_INIT:
			{
			}
			casx = CASX_STEP_00 ;
			break;
		case CASX_STEP_00:
			{				
			}
			casx = CASX_STEP_01 ;
			break;
		case CASX_STEP_01:
			{
			}
			casx = CASX_STEP_02 ;
			break;
		case CASX_STEP_02:
			{
			}
			casx = CASX_STEP_03 ;
			break;
		case CASX_STEP_03:
			{
			}
			casx = CASX_STEP_04 ;
			break;
		case CASX_STEP_04:
			{
			}
			casx = CASX_STEP_05 ;
			break;
		case CASX_STEP_05:
			{
			}
			casx = CASX_FREE_MEM ;
			break;
		case CASX_LOOP_00:
			{
			}
			casx = CASX_LOOP_00 ;
			break;
		case CASX_LOOP_01:
			{
			}
			casx = CASX_LOOP_01 ;
			break;
		case CASX_FREE_MEM:
			{			
			}
			casx = CASX_CLOSE_FILE ;
			break;
		case CASX_CLOSE_FILE:
			{
			}
			casx = CASX_EXIT ;
			break;
		case CASX_HELP:
			{
			}
			casx = CASX_EXIT ;
			break;
		default:
			{
				casx = CASX_EXIT ;
				break;
			}
		}
	}
	return 0 - ret;	
}











/**
module函数功能描述
@param arg1 arg2描述  
@param arg2 arg2描述
@return 返回值描述
*/
hz_ret_o module_obj(hz_object *obj)
{
	hz_tmp_o tmp;
	tmp.casx=CASX_INIT;
	tmp.ret.v = RET_SUCCESS;
	do
	{
	}while(0);

	while( tmp.casx )
	{
		switch(tmp.casx)
		{
		case CASX_INIT:
			{
			}
			tmp.casx = CASX_STEP_00 ;
			break;
		case CASX_STEP_00:
			{				
			}
			tmp.casx = CASX_STEP_01 ;
			break;
		case CASX_STEP_01:
			{
			}
			tmp.casx = CASX_STEP_02 ;
			break;
		case CASX_STEP_02:
			{
			}
			tmp.casx = CASX_STEP_03 ;
			break;
		case CASX_STEP_03:
			{
			}
			tmp.casx = CASX_STEP_04 ;
			break;
		case CASX_STEP_04:
			{
			}
			tmp.casx = CASX_STEP_05 ;
			break;
		case CASX_STEP_05:
			{
			}
			tmp.casx = CASX_FREE_MEM ;
			break;
		case CASX_LOOP_00:
			{
			}
			tmp.casx = CASX_LOOP_00 ;
			break;
		case CASX_LOOP_01:
			{
			}
			tmp.casx = CASX_LOOP_01 ;
			break;
		case CASX_FREE_MEM:
			{			
			}
			tmp.casx = CASX_CLOSE_FILE ;
			break;
		case CASX_CLOSE_FILE:
			{
			}
			tmp.casx = CASX_EXIT ;
			break;
		case CASX_HELP:
			{
			}
			tmp.casx = CASX_EXIT ;
			break;
		default:
			{
				tmp.casx = CASX_EXIT ;
				break;
			}
		}
	}
	tmp.ret.v=0-tmp.ret.v;
	return ret;	
}


