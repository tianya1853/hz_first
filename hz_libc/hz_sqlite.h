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
Description:  hz_sqlite.h
History------------------------------------------------------------
Author:
Date:
Version:
Description:
*******************************************************************/





#ifndef __HZ_SQLITE_H__
#define __HZ_SQLITE_H__
//#include "sqlite3.h"

typedef struct _hz_db_o_
{	
	d8 dbname[64];
	sqlite3 *db;
	d8 * zErrMsg;
	s32 rc;
	d8 sql[256];
	void *db_callback;
	void *db_callback_default;
	void *db_callback_data;
	hz_mutex_t db_mutex;
}hz_db_o;

hz_ret_o hz_db_o_init(hz_db_o *hz_db,d8 *dbname);
s32      hz_db_callback_display( void *data, s32 argc, d8 **argv, d8 **azColName);
hz_ret_o hz_db_create_table(hz_db_o *hz_db,d8 *sql);
hz_ret_o hz_db_open_table(hz_db_o *hz_db);
void     hz_db_close_table     ( hz_db_o *hz_db);
hz_ret_o hz_db_exec            ( hz_db_o *hz_db,d8 * table,d8 *sql);
void     hz_db_search_all      ( hz_db_o *hz_db,d8 * table );
void     hz_db_search_by_id    ( hz_db_o *hz_db,d8 * table,u32 id);
void     hz_db_search_by_id_max( hz_db_o *hz_db,d8 * table);
void     hz_db_delete_by_id    ( hz_db_o *hz_db,d8 * table,u32 id);
void     hz_db_delete_by_id_max( hz_db_o *hz_db,d8 * table);
void     hz_db_delete_all      ( hz_db_o *hz_db,d8 * table);

#define  hz_db_sql_mprintf     sqlite3_mprintf
#define  hz_db_sql_free        sqlite3_free




#endif



