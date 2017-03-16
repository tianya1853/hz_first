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


#include <string.h>
#include "hz_type.h"
int hz_grep(char *match,char *string)
{
	int i = 0;
//	char *tmp_str=string;
	int match_len = 0 ;
	int string_len = 0;

	int  offset = -1;


	match_len = strlen(match);
	string_len = strlen(string);


	if (  string_len >= match_len )
	{
		for ( i = 0; i < ( string_len +1 - match_len );i++)
		{
			if ( 0 == strncmp(string+i,match,match_len ) )
			{
				offset = i;
				//DEBUG_PRINTF("i = %d\n",i);
				break;
			}
		}
	}else
	{
		//offset = -1 ;
	}
	return offset ;
}
