#include "hz_include.h"


int main (int argc,char **argv)
{
	//first print "warning:uninit mutex lt_log",is normal
	d8 log_file[100];
	sprintf(log_file,"%s.log",argv[0]);
	hz_log_init(0,".",log_file );


	lt_info("DEBUG");

	hz_tmp_o tmp;
	hz_flock_o process_lock;
	hz_sprintf(process_lock.filename,"dw.lock");
	
	tmp.ret = hz_file_lock(&process_lock);
	if ( tmp.ret.v == RET_SUCCESS )
	{
		lt_info("lock success");
	}else
	{
		lt_error("lock failed");
	}

	lt_sleep(20);
	tmp.ret = hz_file_unlock(&process_lock);
	if ( tmp.ret.v == RET_SUCCESS )
	{
		lt_info("unlock success");
	}else
	{
		lt_error("unlock failed");
	}
	return 0;
}
