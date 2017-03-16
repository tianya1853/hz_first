
#ifndef __HZ_FILE_H__
#define __HZ_FILE_H__

/*
return:SUCCESS/FAIL
*/
s32 file_exist(d8 *filename);

s32 shell_cmd(d8 *cmd,d8*retbuf,s32 buflen_max);



#endif /* !__HZ_FILE_H__ */
