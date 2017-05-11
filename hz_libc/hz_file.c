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





/**
fopen mode
“r” 以只读方式打开文件，该文件必须存在。
“r+” 以可读写方式打开文件，该文件必须存在。
”rb+“ 读写打开一个二进制文件，允许读写数据，文件必须存在。
“w” 打开只写文件，若文件存在则文件长度清为0，即该文件内容会消失。若文件不存在则建立该文件。
“w+” 打开可读写文件，若文件存在则文件长度清为零，即该文件内容会消失。若文件不存在则建立该文件。
“a” 以附加的方式打开只写文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾，即文件原先的内容会被保留。（EOF符保留）
”a+“ 以附加方式打开可读写的文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾后，即文件原先的内容会被保留。 （原来的EOF符不保留）
“wb” 只写打开或新建一个二进制文件；只允许写数据。
“wb+” 读写打开或建立一个二进制文件，允许读和写
“wx” 创建文本文件,只允许写入数据.[C11]
“wbx” 创建一个二进制文件,只允许写入数据.[C11]
”w+x“ 创建一个文本文件,允许读写.[C11]
“wb+x” 创建一个二进制文件,允许读写.[C11]
“w+bx” 和"wb+x"相同[C11]
“rt” 只读打开一个文本文件，只允许读数据
　　“wt” 只写打开或建立一个文本文件，只允许写数据
　　“at” 追加打开一个文本文件，并在文件末尾写数据
　　“rb” 只读打开一个二进制文件，只允许读数据
　　“wb” 只写打开或建立一个二进制文件，只允许写数据
　　“ab” 追加打开一个二进制文件，并在文件末尾写数据
　　“rt+” 读写打开一个文本文件，允许读和写
　　“wt+” 读写打开或建立一个文本文件，允许读写
　　“at+” 读写打开一个文本文件，允许读，或在文件末追加数据
　　“rb+” 读写打开一个二进制文件，允许读和写
　　“ab+” 读写打开一个二进制文件，允许读，或在文件末追加数据

*/






/**
access mode
具体含义如下：
R_OK 只判断是否有读权限
W_OK 只判断是否有写权限
X_OK 判断是否有执行权限
F_OK 只判断是否存在
在宏定义里面分别对应：
00 只存在
02 写权限
04 读权限
06 读和写权限
*/

#if 1
s32 file_exist(d8 *filename)
{
	if ( access(filename, 0) == 0 )
		return HZ_SUCCESS;
	else
		return HZ_FAIL;
	//return (access(filename, 0) == 0);
}
#else

s32 file_exist(d8 *filename)
{
	FILE *fp;
	fp = fopen(filename , "rb");
	if(  fp == NULL )
	{
		return HZ_FAIL;
	}else
	{
		fclose(fp);
		return HZ_SUCCESS;
	}		
}

#endif

s32 file_touch(d8 *filename)
{
	FILE *fp;
	fp = fopen(filename , "ab");
	if(  fp == NULL )
	{
		return HZ_FAIL;
	}else
	{
		fclose(fp);
		return HZ_SUCCESS;
	}		
}

/**
#include<stdio.h>
int main(){
    char filename[80];
    printf("The file to delete:");
    gets(filename);
    if( remove(filename) == 0 )
        printf("Removed %s.", filename);
    else
        perror("remove");
}
*/

s32 file_rm(d8 *filename)
{
	
	if( remove(filename) == 0  )
	{
		return HZ_SUCCESS;
	}else
	{
		lt_error("remove file %s, failed",filename);
		return HZ_FAIL;
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
