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
Description:  TYPE.h
History------------------------------------------------------------
Author:
Date:
Version:
Description:
*******************************************************************/


#ifndef __TYPE_H__
#define __TYPE_H__
#include <stdio.h>
//#pragma pack (16)

#ifndef NULL
#define NULL ((void *)0)
#endif

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef unsigned long long u64;

typedef signed char  s8;  //must use signed,cannot ignor signed. arm-gcc will default char to unsigned char
typedef signed short s16;
typedef signed int   s32;
typedef signed long long s64;


typedef char  d8;
typedef int   d32;
typedef struct{
	u32 year;
	u32 mon;
	u32 day;
	u32 hour;
	u32 min;
	u32 sec;

	s32 time_s;
	s32 time_ns;
}lt_time_t;

#if 0
#ifndef _TM_DEFINED
struct tm {
int tm_sec; /* 秒 – 取值区间为[0,59] */
int tm_min; /* 分 - 取值区间为[0,59] */
int tm_hour; /* 时 - 取值区间为[0,23] */
int tm_mday; /* 一个月中的日期 - 取值区间为[1,31] */
int tm_mon; /* 月份（从一月开始，0代表一月） - 取值区间为[0,11] */
int tm_year; /* 年份，其值等于实际年份减去1900 */
int tm_wday; /* 星期 – 取值区间为[0,6]，其中0代表星期天，1代表星期一，以此类推 */
int tm_yday; /* 从每年的1月1日开始的天数 – 取值区间为[0,365]，其中0代表1月1日，1代表1月2日，以此类推 */
int tm_isdst; /* 夏令时标识符，实行夏令时的时候，tm_isdst为正。不实行夏令时的进候，tm_isdst为0；不了解情况时，tm_isdst()为负。*/
};
#endif
#endif


/*
struct timespec
{
time_t tv_sec; /// 秒
long tv_nsec; //// 纳秒
};
*/


//typedef bool
#define HZ_SUCCESS  0
#define HZ_FAIL    -1
#define SUCCESS  0
#define FAIL    -1

/**
@brief define return error type.

example
	hz_ret_t function()
	{
		hz_ret_t ret = RET_FAIL ;
		return 0 - ret;
	}
*/
typedef enum 
{
	RET_SUCCESS=HZ_SUCCESS,
	RET_ERR_ARG,
	RET_ERR_FILE_OPEN,
	RET_ERR_FILE_SIZE,
	RET_ERR_FILE_READ,
	RET_ERR_FILE_WRITE,
	RET_ERR_MALLOC,
	RET_ERR_MEMCPY,
	RET_ERR_MEMSET,
	RET_ERR_MEMDUMP,
	RET_FAIL
}hz_ret_t;


typedef struct _hz_ret_o_
{
	hz_ret_t   v;//value
	//d8         ret_str[128];
	//hz_mutex_t ret_mutex;
}hz_ret_o;//object

typedef struct _hz_tmp_o_
{
	//s32 res;
	s32 v1;
	s32 v2;
	s32 v3;
	s32 i;
	s32 j;
	s32 casx;
	FILE *fp;
	hz_ret_o ret;//used for return of function	
}hz_tmp_o;//object  抛弃res，减少res与ret的混淆


typedef struct
{
	d8 name[16];
	d8 version[16];
	s32 v;//value
	void *vp;
	void *action;
}hz_object;

void hz_tmp_o_init(hz_tmp_o *hz_tmp);
enum
{
	CASX_EXIT=0,
	CASX_INIT,
	CASX_STEP_00,
	CASX_STEP_01,
	CASX_STEP_02,
	CASX_STEP_03,
	CASX_STEP_04,
	CASX_STEP_05,
	CASX_STEP_06,
	CASX_STEP_07,
	CASX_STEP_08,
	CASX_STEP_09,
	CASX_STEP_10,
	CASX_STEP_11,
	CASX_STEP_12,
	CASX_STEP_13,
	CASX_STEP_14,
	CASX_STEP_15,
	CASX_STEP_16,
	CASX_STEP_17,
	CASX_STEP_18,
	CASX_STEP_19,
	CASX_STEP_20,
	CASX_LOOP_00,
	CASX_LOOP_01,
	CASX_FREE_MEM,
	CASX_CLOSE_FILE,
	CASX_HELP
};




#define BIT(x) (1<<(x))


#define hz_struct_offset(type, member) (unsigned int)(&(((type *)0)->member))

















/*

	int casx=CASX_INIT;
	while(casx)
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
*/








/*
	hz_tmp_o tmp;
	tmp.casx = CASX_INIT ;	
	while( tmp.casx  )
	{
		switch(  tmp.casx  )
		{
		case CASX_INIT:
			{
			}
			tmp.casx  = CASX_STEP_00 ;
			break;
		case CASX_STEP_00:
			{
			}
			tmp.casx  = CASX_STEP_01 ;
			break;
		case CASX_STEP_01:
			{
			}
			tmp.casx  = CASX_STEP_02 ;
			break;
		case CASX_STEP_02:
			{
			}
			tmp.casx  = CASX_STEP_03 ;
			break;
		case CASX_STEP_03:
			{
			}
			tmp.casx  = CASX_STEP_04 ;
			break;
		case CASX_STEP_04:
			{
			}
			tmp.casx  = CASX_STEP_05 ;
			break;
		case CASX_STEP_05:
			{
			}
			tmp.casx  = CASX_FREE_MEM ;
			break;
		case CASX_LOOP_00:
			{
			}
			tmp.casx  = CASX_LOOP_00 ;
			break;
		case CASX_LOOP_01:
			{
			}
			tmp.casx  = CASX_LOOP_01 ;
			break;
		case CASX_FREE_MEM:
			{
			}
			tmp.casx  = CASX_CLOSE_FILE ;
			break;
		case CASX_CLOSE_FILE:
			{
			}
			tmp.casx  = CASX_EXIT ;
			break;
		case CASX_HELP:
			{
			}
			tmp.casx  = CASX_EXIT ;
			break;
		default:
			{
				tmp.casx  = CASX_EXIT ;
				break;
			}
		}
	}
*/











#endif /* !__TYPE_H__ */



