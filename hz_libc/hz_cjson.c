#include <stdio.h>
#include "hz_cjson.h"
#include <stdlib.h>


/**
module 函数功能描述
@param arg1 arg2描述  
@param arg2 arg2描述
@return 返回值描述
*/

/* Parse text to JSON, then render back to text, and print! */
void hz_cjson_doit(hz_cjson_o *hz_cjson,char *cjson_text)
{
	//char *cjson_out;
	cJSON *cjson_root;
	
	cjson_root=cJSON_Parse(cjson_text);
	if (!cjson_root) {hz_cjson->cjson_root = NULL; printf("Error before: [%s]\n",cJSON_GetErrorPtr());}
	else
	{
		hz_cjson->cjson_root=cjson_root;
		//cjson_out=cJSON_Print(cjson_root);		
		//cJSON_Delete(root);
		//printf("%s\n",cjson_out);		
		//free(cjson_out);
	}
}

/* Read a file, parse, render back, etc. */
void hz_cjson_dofile(hz_cjson_o *hz_cjson)
{
	FILE *f=NULL;long len;char *data;
	
	f=fopen(hz_cjson->filename,"rb");
	if(  f != NULL )
	{
		fseek(f,0,SEEK_END);len=ftell(f);fseek(f,0,SEEK_SET);
		data=(char*)malloc(len+1);fread(data,1,len,f);fclose(f);		
		hz_cjson_doit(hz_cjson,data);
		free(data);
	}else
	{
		//lt_error("file %s cannot open",hz_cjson->filename);  //can not use lt_log ,when before init log
		printf("error:file %s cannot open\n",hz_cjson->filename);
		hz_cjson->cjson_root = NULL ;		
	}
}
