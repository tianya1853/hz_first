


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
