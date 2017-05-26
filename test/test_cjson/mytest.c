#include "hz_include.h"


#define JSON_CONFIG  "config.json"
int main (int argc ,char **argv )
{
	d8 log_file[100];
	sprintf(log_file,"%s.log",argv[0]);
	//first print "warning:uninit mutex lt_log",is normal
	hz_log_init(0,".",log_file );





	hz_cjson_o hz_cjson;
	cJSON  *cjson_obj ,*cjson_Item;//not need free


	hz_sprintf(hz_cjson.filename,"%s",JSON_CONFIG );
	hz_cjson_dofile(&hz_cjson);
	if (hz_cjson.cjson_root == NULL)
	{
		printf("error:hz_cjson_dofile failed\n");
		return 0;
	}
	
	cjson_obj=cJSON_GetObjectItem(hz_cjson.cjson_root,"format");


	cjson_Item=cJSON_GetObjectItem(cjson_obj,"frame rate") ;
	printf("frame rate %d\n",cjson_Item->valueint);
	lt_info("frame rate %d\n",cjson_Item->valueint);


	cjson_Item=cJSON_GetObjectItem(cjson_obj,"type") ;	
	printf("type %s \n",cjson_Item->valuestring);
	lt_info("type %s \n",cjson_Item->valuestring);

	d8 *out = cJSON_Print(hz_cjson.cjson_root );   //将json形式打印成正常字符串形式  
	printf("\n%s\n",out)	;
	lt_info("\n%s\n",out)	;
	free(out);
	cJSON_Delete( hz_cjson.cjson_root );





	
	lt_info("test log file use hz_libc.json config file");
	return 0;
}











