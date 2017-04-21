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
#include "hz_include.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "hz_type.h"
//#include "hz_log.h"


hz_mutex_t mutex_print;   //={0,PTHREAD_MUTEX_INITIALIZER};



#if 1
	// string type is d8 ,not d8  or u8
	#ifdef TCI6614_ARM_SIMULATE	
		d8 *hz_log_dir="";
		d8 *hz_log_file="hz_license.log";
	#else
		d8 *hz_log_dir="/mnt/log/log_license";
		d8 *hz_log_file="hz_license.log";
	#endif

#else
	d8 *hz_log_file=NULL;
#endif


s32 hz_log_count=10;        //file count
s32 hz_log_max_size=5*1024*1024; //file size  5m




//sleep 函数有时候行,有时候不行，没搞明白,sleep 在某些情况下可能被中断导致没有延时
int lt_sleep(int delay_s)
{
	sleep(delay_s);	
	return 0 ;
}


int lt_msleep(int delay_ms)
{
	usleep(delay_ms*1000);	
	return 0 ;
}


int lt_usleep(int delay_us) //usleep 是不精确的
{
	usleep(delay_us);	
	return 0 ;
}


/*
static s32 init_log(char * filename)
{
	return 0;
}
*/


/*
* add edit hz_log_max_size & multi log
*/
s32 hz_log_init(int level,char *path_log,char *file_name_log)
{
	level=level;
	path_log=path_log;
	file_name_log=file_name_log;



	hz_log_dir=path_log;
	hz_log_file=file_name_log;
	printf("log file is %s/%s\n",hz_log_dir,hz_log_file);
	return HZ_SUCCESS;
}

static s32 _hz_log_init_()
{
	//s32 res=0;
	s32 ret=0;

	d8 tmp_cmd[256];
	sprintf(tmp_cmd,"mkdir -p %s ",hz_log_dir);
	
	system(tmp_cmd);
	hz_mutex_init(&mutex_print,NULL);
	sprintf(mutex_print.name,"lt_log");
	return ret;

}

static s32 hz_log_backup()
{
	d8 tmp_cmd[256];
	d8 tmp_log_filename[256];
	s32 i = 0;

	sprintf(tmp_log_filename,"%s/%s",hz_log_dir,hz_log_file);

	for( i=0;i<hz_log_count-1;i++)  //0--8  loop 9 times
	{
		sprintf(tmp_cmd,"mv %s_%d.tar.gz %s_%d.tar.gz >> %s  2>&1",tmp_log_filename,hz_log_count-2-i,tmp_log_filename,hz_log_count-1-i,tmp_log_filename);
		//printf("debug cmd :%s\n",tmp_cmd);
		system(tmp_cmd);
	}
	//will gereate one waring    tar: removing leading '/' from member names
	sprintf(tmp_cmd,"tar -czvf %s_0.tar.gz  %s ",tmp_log_filename,tmp_log_filename);
	//printf("debug cmd :%s\n",tmp_cmd);
	system(tmp_cmd);
	
	sprintf(tmp_cmd,"rm %s",tmp_log_filename);
	//printf("debug cmd :rm %s",tmp_log_filename);
	system(tmp_cmd);
	return 0;
}

s32 hzprintf(d8 *fmt, ...)
{
	va_list list;
	s32 cnt=0;
	s32 file_len=0;
	static s32 flag_init=0;
	//s32 flag_backup=0;
	d8 tmp_log_name[256]={0};
	FILE *fp;
	
	va_start(list, fmt);
	
	if ( flag_init == 0 )
	{
		flag_init =1;		
		_hz_log_init_();
		//hz_log_backup();
	}

	//hz_mutex_lock(&mutex_print);//lock
	sprintf(tmp_log_name,"%s/%s",hz_log_dir,hz_log_file);
	
	do
	{
			
		if (hz_log_file == NULL)
		{
			cnt = vfprintf(stdout, fmt, list);
		}else
		{
			
			fp = fopen(tmp_log_name , "a");
			if(  fp == NULL )
			{
				break;
			}
			cnt = vfprintf(fp, fmt, list);
			fclose(fp);

		}		
	}
	while(0);
	va_end( list );


	fp = fopen(tmp_log_name , "rb");
	if(  fp == NULL )
	{
		//hz_mutex_unlock(&mutex_print);
		return(cnt);
	}	
	fseek(fp,0,SEEK_END); //定位到文件末 
	file_len = ftell(fp); //文件长度
	fclose(fp);
	if ( file_len > hz_log_max_size )
	{
		hz_log_backup();
	}
	//hz_mutex_unlock(&mutex_print);//unlock
	return(cnt);
}



//#define hzprintf printf


#if 0
s32 lt_log()
{


}
#else

#endif















int lt_runtime(lt_time_t *lt_time,s32 printtime)
{
	struct timespec time1 = {0, 0};
	time_t timer;//time_t就是long int 类型  
	struct tm *tblock;  

	timer = time(NULL);//这一句也可以改成time(&timer);  
	tblock = localtime(&timer);


	clock_gettime(CLOCK_MONOTONIC, &time1);  
	
	if( printtime )
	{		
		hzprintf("[%d%02d%02d%02d%02d%02d:",tblock->tm_year+1900,tblock->tm_mon+1,tblock->tm_mday,tblock->tm_hour,tblock->tm_min,tblock->tm_sec ); 
		hzprintf("%ds.%09dns]", (s32)time1.tv_sec,(s32) time1.tv_nsec);  
	}
	if( lt_time == NULL )
	{
		return -1;
	}
	lt_time->year=tblock->tm_year+1900;
	lt_time->mon =tblock->tm_mon+1;
	lt_time->day =tblock->tm_mday ;
	lt_time->hour =tblock->tm_hour ;
	lt_time->min =tblock->tm_min ;
	lt_time->sec =tblock->tm_sec ;
	lt_time->time_s = (s32)time1.tv_sec;
	lt_time->time_ns = time1.tv_nsec;
	return 0; 
}






