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
Description:  hz_sqlite.c
History------------------------------------------------------------
Author:
Date:
Version:
Description:
*******************************************************************/

#include "hz_include.h"

/**
module函数功能描述
@param arg1 arg2描述
@param arg2 arg2描述
@return 返回值描述
*/
#if 0
static hz_ret_t module_function(s8 * arg1,u32 arg2)
{
	hz_ret_t ret = RET_SUCCESS ;
	s32 res = 0;
	s32 i = 0;
	//s32 stmp = 0;
	//u32 utmp = 0;

	//FILE *fp;
	s32 casx=CASX_INIT;


	do
	{
		ret = ret;
		res = res;
		i = i;
	}
	while(0);

	while(casx)
	{
		switch(casx)
		{
		case CASX_INIT:
			{
			}
			casx = CASX_STEP_00 ;
			break;
		case CASX_STEP_00:
			{				
			}
			casx = CASX_STEP_01 ;
			break;
		case CASX_STEP_01:
			{
			}
			casx = CASX_STEP_02 ;
			break;
		case CASX_STEP_02:
			{
			}
			casx = CASX_STEP_03 ;
			break;
		case CASX_STEP_03:
			{
			}
			casx = CASX_STEP_04 ;
			break;
		case CASX_STEP_04:
			{
			}
			casx = CASX_STEP_05 ;
			break;
		case CASX_STEP_05:
			{
			}
			casx = CASX_FREE_MEM ;
			break;
		case CASX_LOOP_00:
			{
			}
			casx = CASX_LOOP_00 ;
			break;
		case CASX_LOOP_01:
			{
			}
			casx = CASX_LOOP_01 ;
			break;
		case CASX_FREE_MEM:
			{			
			}
			casx = CASX_CLOSE_FILE ;
			break;
		case CASX_CLOSE_FILE:
			{
			}
			casx = CASX_EXIT ;
			break;
		case CASX_HELP:
			{
			}
			casx = CASX_EXIT ;
			break;
		default:
			{
				casx = CASX_EXIT ;
				break;
			}
		}
	}
	return 0 - ret;	
}
#endif






/**
module函数功能描述
@param arg1 arg2描述
@param arg2 arg2描述
@return 返回值描述
*/

hz_ret_o hz_db_o_init(hz_db_o *hz_db,d8 *dbname)
{
	hz_ret_o ret;
	ret.v=0;
	if ( hz_db != NULL )
	{
		hz_db->db_callback_default = hz_db_callback_display ;
		hz_db->db_callback = NULL ;
		hz_db->zErrMsg=NULL;
		hz_db->db=NULL;
		hz_mutex_init(&hz_db->db_mutex,NULL);
		sprintf(hz_db->db_mutex.name,"%s",dbname);
		sprintf(hz_db->dbname,"%s",dbname);
	}else
	{
		lt_error("hz_db == NULL");
	}
	return ret;
}

/**
module函数功能描述
@param arg1 arg2描述
@param arg2 arg2描述
@return 返回值描述
*/
s32 hz_db_callback_display(void *data, s32 argc, d8 **argv, d8 **azColName)
{
   s32 i;
   for(i=0; i<argc; i++){
	   lt_info("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }   
   return 0;
}

/**
	Create SQL statement 
	//PRIMARY KEY CAN AUTO ++


//PRIMARY KEY type can not is int ,must be interger , others primary can not auto ++
	sql = 	"CREATE TABLE test_t1("  \
			"id INT PRIMARY KEY     NOT NULL," \
			"time_input     TEXT," \
			"time_output    TEXT," \
			"info           TEXT," \
			"reserve1       TEXT," \
			"reserve2       TEXT," \
			"reserve3       TEXT);";

	d8 * sql = 	"CREATE TABLE test_t1("  \
			"id integer PRIMARY KEY not null," \
			"time_input     TEXT," \
			"time_output    TEXT," \
			"info           TEXT," \
			"reserve1       TEXT," \
			"reserve2       TEXT," \
			"reserve3       TEXT);";


*/
hz_ret_o hz_db_create_table(hz_db_o *hz_db,d8 *sql)
{
	hz_ret_o ret;	
	//FILE *fp;
	hz_tmp_o tmp;
	hz_tmp_o_init(&tmp);
	ret.v=0;
	/**
	lt_info("creat table file if file not exist");
	

	tmp.fp = fopen( hz_db->dbname , "rb" );
	if( tmp.fp != NULL )
	{
		fclose(tmp.fp);
		lt_info("file %s exist ",hz_db->dbname);
		return ret;
	}
	*/
	do
	{
		hz_mutex_lock(&hz_db->db_mutex);
		hz_db->rc = sqlite3_open(hz_db->dbname,&hz_db->db);
		//rc = sqlite3_open_v2(filename,&db,SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
		if (hz_db->rc)
		{
			lt_error("can't open database%s\n",sqlite3_errmsg(hz_db->db));
			//sqlite3_close(hz_db->db);
			ret.v = -1 ;break;
		}
		if ( sql == NULL )
		{
			lt_error("sql == NULL");
			break;
		}

		//sql =  "CREATE TABLE save_data(num integer primary key, id int, data text, time text)";
		lt_info("will creat table sql=%s",sql);
		hz_db->rc = sqlite3_exec(hz_db->db, sql, hz_db_callback_display, 0, &hz_db->zErrMsg);
		if( hz_db->rc != SQLITE_OK )
		{			
			lt_error("table creat failed  errmsg=%s\n",sqlite3_errmsg(hz_db->db));
			sqlite3_free(hz_db->zErrMsg);
			ret.v = -1 ;break;
		}
	}while(0);

	sqlite3_close(hz_db->db);
	hz_mutex_unlock(&hz_db->db_mutex);
	return ret;
}


/**
module函数功能描述
@param arg1 arg2描述
@param arg2 arg2描述
@return 返回值描述
*/
hz_ret_o hz_db_open_table(hz_db_o *hz_db)
{
	hz_ret_o ret;
	ret.v=0;
	////s32 hz_db->rc;;
	hz_mutex_lock(&hz_db->db_mutex);
	do
	{
		hz_db->rc = sqlite3_open(hz_db->dbname,&hz_db->db);		
		if ( hz_db->rc )
		{
			lt_error("can't open database%s\n",sqlite3_errmsg(hz_db->db));
			sqlite3_close(hz_db->db);
			ret.v = -1 ;break;
		}
	}while(0);
	hz_mutex_unlock(&hz_db->db_mutex);
	return ret ;
}

/**
module函数功能描述
@param arg1 arg2描述
@param arg2 arg2描述
@return 返回值描述
*/
void hz_db_close_table(hz_db_o *hz_db)
{
	hz_mutex_lock(&hz_db->db_mutex);
	if ( hz_db->db != NULL )
	{
		sqlite3_close(hz_db->db);
	}else
	{
		lt_error("table close failed  hz_db->db == NULL ");
	}
	hz_mutex_unlock(&hz_db->db_mutex);
}

/**
can used for insert,delete
@param arg1 arg2描述
@param arg2 arg2描述
@return 返回值描述  hz_ret_o.v < 0 failed 


UPDATE table_name
SET column1 = value1, column2 = value2...., columnN = valueN
WHERE [condition];

e.g. UPDATE COMPANY SET ADDRESS = 'Texas' WHERE ID = 6;


replace INTO test_t1 (id,time_input,time_output,info) "  \
	 	"VALUES (0, '20170506', 'null','jasmine');

*/
hz_ret_o hz_db_exec(hz_db_o *hz_db,d8 * table,d8 *sql)
{
	//d8 * sql;
	////d8 * hz_db->zErrMsg = NULL;
	//s32 res =0;
	////s32 hz_db->rc;;
	hz_ret_o ret;

	hz_mutex_lock(&hz_db->db_mutex);
	do
	{
		lt_debug("will exec table sql=%s",sql);
		hz_db->rc = sqlite3_exec( hz_db->db, sql, hz_db->db_callback, hz_db->db_callback_data, &hz_db->zErrMsg);
		if( hz_db->rc != SQLITE_OK )
		{			
			lt_error("table exec failed  errmsg=%s\n",sqlite3_errmsg(hz_db->db));
			sqlite3_free(hz_db->zErrMsg);
			ret.v = -1 ;break;
		}
	}while(0);

	hz_mutex_unlock(&hz_db->db_mutex);
	return ret ;
}



void hz_db_search_all( hz_db_o *hz_db,d8 * table )
{
	d8 * sql;
	//d8 * hz_db->zErrMsg = 0;
	hz_mutex_lock(&hz_db->db_mutex);
	sql = sqlite3_mprintf("select * from %s",table);
	sqlite3_exec(hz_db->db,sql,hz_db_callback_display,0,&hz_db->zErrMsg);// hz_db_callback_display == &hz_db_callback_display
	sqlite3_free(sql);
	hz_mutex_unlock(&hz_db->db_mutex);
}


void hz_db_search_by_id( hz_db_o *hz_db,d8 * table,u32 id)
{
    d8 * sql;
    //d8 * hz_db->zErrMsg = 0;

    //sn = 0;
	hz_mutex_lock(&hz_db->db_mutex);
    sql = sqlite3_mprintf("select * from %s where id=%d",table,id);
    sqlite3_exec(hz_db->db,sql,hz_db_callback_display,0,&hz_db->zErrMsg);
    sqlite3_free(sql);
	hz_mutex_unlock(&hz_db->db_mutex);
}


void hz_db_search_by_id_max( hz_db_o *hz_db,d8 * table)
{
	d8 * sql;
	//d8 * hz_db->zErrMsg = 0;

	//sn = 0;
	hz_mutex_lock(&hz_db->db_mutex);
	sql = sqlite3_mprintf("select * from %s where id=( select max(id) from %s )",table,table);
	if ( hz_db->db_callback == NULL )
	{
		sqlite3_exec(hz_db->db,sql,hz_db_callback_display,hz_db->db_callback_data,&hz_db->zErrMsg);
	}else
	{
		sqlite3_exec(hz_db->db,sql,hz_db->db_callback,hz_db->db_callback_data,&hz_db->zErrMsg);
	}
	
	sqlite3_free(sql);
	hz_mutex_unlock(&hz_db->db_mutex);
}


void hz_db_delete_by_id( hz_db_o *hz_db,d8 * table,u32 id)
{
    //s32 hz_db->rc; ;
    d8 * sql;
    //d8 * hz_db->zErrMsg = 0;
	hz_mutex_lock(&hz_db->db_mutex);
    sql = sqlite3_mprintf("delete from %s where id=%d",table,id);
    hz_db->rc = sqlite3_exec(hz_db->db,sql,0,0,&hz_db->zErrMsg);
    sqlite3_free(sql);
	hz_mutex_unlock(&hz_db->db_mutex);
}




void hz_db_delete_by_id_max( hz_db_o *hz_db,d8 * table)
{
    //s32 hz_db->rc; ;
    d8 * sql;
    //d8 * hz_db->zErrMsg = 0;
	hz_mutex_lock(&hz_db->db_mutex);
    sql = sqlite3_mprintf("delete from %s where id = ( select max(id) from %s )",table,table);
    hz_db->rc = sqlite3_exec(hz_db->db,sql,0,0,&hz_db->zErrMsg);
    sqlite3_free(sql);
	hz_mutex_unlock(&hz_db->db_mutex);
}


void hz_db_delete_all(hz_db_o *hz_db,d8 * table)
{
    d8 * sql;
    //d8 * hz_db->zErrMsg = 0;
	hz_mutex_lock(&hz_db->db_mutex);
	sql = sqlite3_mprintf("delete from %s",table);
	sqlite3_exec(hz_db->db,sql,0,0,&hz_db->zErrMsg);
	sqlite3_free(sql);
	hz_mutex_unlock(&hz_db->db_mutex);
}





