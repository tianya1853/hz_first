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
#ifndef __HZ_FILE_H__
#define __HZ_FILE_H__

/*
return:HZ_SUCCESS/HZ_FAIL
*/
s32 file_exist(d8 *filename);
s32 file_touch(d8 *filename);
s32 file_remove(d8 *filename);
s32 shell_cmd(d8 *cmd,d8*retbuf,s32 buflen_max);



#endif /* !__HZ_FILE_H__ */
