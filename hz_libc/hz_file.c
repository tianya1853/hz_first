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

#include <stdio.h>
s32 file_exist(d8 *filename)
{
	FILE *fp;
	fp = fopen(filename , "rb");
	if(  fp == NULL )
	{
		return FAIL;
	}else
	{
		fclose(fp);
		return SUCCESS;
	}		
}






#if 0
static s32 popen_read(d8 *cmd,d8 *buf,s32 buflen_max)
{
	s32 ret = HZ_SUCCESS;

	if((fp=popen(cmd,"r"))==NULL)
	{		
		lt_error("popen_read:errno=%s\n",strerror(errno));
		ret = HZ_FAIL;
	}
	else
	{
		while(fgets(result_buf, sizeof(result_buf), fp) != NULL);

    }
		pclose(fp);
	}
	
	return ret ;
}

#endif


/**
redirection  &>     equivalent   >&
*/
s32 shell_cmd(d8 *cmd,d8*retbuf,s32 buflen_max)
{
	FILE *fp;
	d8 cmd_2[256];
	int file_size;


	snprintf(cmd_2,250,"%s  > /dev/shm/c_callshell.tmp  2>&1",cmd);
	system(cmd_2);
	lt_debug("%s",cmd_2);
	fp = fopen("/dev/shm/c_callshell.tmp" , "rb");
	if(  fp == NULL )
	{
		return FAIL;
	}
 
	fseek( fp , 0 , SEEK_END );
	
	file_size = ftell( fp );
	if ( file_size >= buflen_max )
	{
		file_size = buflen_max-2;
	}
	
	fseek( fp , 0 , SEEK_SET);	
	fread( retbuf ,sizeof(d8), file_size, fp);
	
	retbuf[file_size]= 0;
	lt_debug("%s",retbuf);
	fclose(fp);
	return SUCCESS;
}
