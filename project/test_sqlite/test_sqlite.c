/*******************************************************************
Copyright (C) hz
Version:      v0.0.1
FileInfo------------------------------------------------------------
Filename:     
Author:       liusonghua
Date:         
OS:           
Complier:     
HardWare:     
Version :     v0.0.1
Description:  sqlite_test.c
History------------------------------------------------------------
Author:
Date:
Version:
Description:
*******************************************************************/


#include "hz_include.h"
#include "sqlite3.h"
static int db_creat_table_test_t1(char* dbname);
static int db_get_table(char* dbname);
static int db_insert_test_t1(char* dbname);
///static int db_delete_test_t1(char* dbname);

//main1
s32 main_1(s32 argc,d8 **argv)
{
//	u32 i=0;
	d8 log_file[100];	
	d8 *db_test_t1="test_t1.db";
	sprintf(log_file,"%s.log",argv[0]);
	hz_log_init(0,".",log_file );

	db_creat_table_test_t1(db_test_t1);
	db_insert_test_t1(db_test_t1);
	//db_delete_test_t1(db_test_t1);
	db_get_table(db_test_t1);
	return 0;
}


static int db_callback_display(void *data, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
	   lt_info("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }   
   return 0;
}
#if 0
static int db_update(char *dbname, hz_time_info_s *time_info_db)
{
	sqlite3 *db;
	int rc;
	char *sql;
	int res = 0;
	char *zErrMsg = 0;


	/* Open database */
	rc = sqlite3_open(dbname, &db);
	if( rc )
	{
		res = -1;
		return res;
	}else
	{
	}

	sql = malloc(1024);
	sprintf(sql," UPDATE LicenseTime set " \
				" check_code = '%s' ," \
				" time_register = '%s' ," \
				" time_expiry = '%s' ," \
				" time_last = '%s' ," \
				" time_init = 'inited' " \
				"WHERE id =1 ; "  \
				 "SELECT * from LicenseTime;"
				,time_info_db->check_code
				,time_info_db->time_register_str
				,time_info_db->time_expiry_str
				,time_info_db->time_last_str);

	DEBUG_PRINTF("%s\n",sql);
	rc = sqlite3_exec(db, sql, db_callback_display , (void*)&time_info_db,  &zErrMsg);
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
	    sqlite3_free(zErrMsg);
		res = -1 ;
	}else{
		DEBUG_PRINTF("select Operation done successfully\n");
	}


	free(sql);
	sqlite3_close(db);
	return res ;
}
#endif

#if 0
static int db_callback(void *data, int argc, char **value, char **name)
{
	int i ;
	int res = 0 ;
	hz_time_info_s * time_info_db = (hz_time_info_s *)data;
	//fprintf(stderr, "%s: ", (const char*)data);
	for(i=0; i<argc; i++)
	{
		DEBUG_PRINTF("%s = %s\n", name[i], value[i] ? value[i] : "NULL");
		if ( 0 == strncmp("check_code" ,name[i],strlen("check_code") ) )
		{
			if (  33 >= strlen(value[i])  ) {
				sprintf(time_info_db->check_code,"%s",value[i] ? value[i] : TIME_FOREVER);
				DEBUG_PRINTF("check_code:%s\n",time_info_db->check_code);
			}else{
				res = -1 ;
				//break;
			}
		}

		if ( 0 == strncmp("time_register" ,name[i],strlen("time_register") ) )
		{
			if (  14 <= strlen(value[i])  )	{
				if ( 0 == strncmp("20" ,value[i],strlen("20") ) )
				{
					timeStrToTimeStruct ( &(time_info_db->time_register) 	,value[i] );
				}else
				{
					timeStrToTimeStruct ( &(time_info_db->time_register) 	,TIME_FOREVER);
				}
				DEBUG_PRINTF("time_register:%s\n",value[i]);
			}else{
				res = -1 ;
				//break;
			}
		}
		if ( 0 == strncmp("time_expiry" ,name[i],strlen("time_expiry") ) )
		{
			if (  14 <= strlen(value[i])  )	{
				if ( 0 == strncmp("20" ,value[i],strlen("20") ) )
				{
					timeStrToTimeStruct ( &(time_info_db->time_expiry) 	,value[i] );
				}else
				{
					timeStrToTimeStruct ( &(time_info_db->time_expiry) 	,TIME_FOREVER);
				}
				DEBUG_PRINTF("time_expiry:%s\n",value[i]);
			}else{
				res = -1 ;
				//break;
			}
		}

		if ( 0 == strncmp("time_last" ,name[i],strlen("time_last") ) )
		{
			if (  14 <= strlen(value[i])  )	{
				if ( 0 == strncmp("20" ,value[i],strlen("20") ) )
				{
					timeStrToTimeStruct ( &(time_info_db->time_last) 	,value[i] );
				}else
				{
					timeStrToTimeStruct ( &(time_info_db->time_last) 	,TIME_FOREVER);
				}
				DEBUG_PRINTF("time_last:%s\n",value[i]);
			}else{
				//DEBUG_PRINTF("time_last: %d%send\n",strlen(value[i]),value[i]);
				res = -1 ;
				//break;
			}
		}

		if ( 0 == strncmp("time_init" ,name[i],strlen("time_init") ) )
		{
			sprintf(time_info_db->time_init,"%s",value[i]);
		}
	}
	//printf("\n");
//	return res;
	res = res ;
	return 0;
}


static int db_get_time_info(hz_time_info_s * time_info_db,char* dbname)
{
	int rc;
	char *sql;
	sqlite3 *db;
	char *zErrMsg = 0;
	int res = 0;


	/* Open database */
	rc = sqlite3_open(dbname, &db);

	if( rc )
	{
		printf("%d:ERROR\n",__LINE__);
		res = -1;
		return res;
	}


	memset(time_info_db,0,sizeof(hz_time_info_s));
	sql = "SELECT * from LicenseTime";


	rc = sqlite3_exec(db, sql, db_callback, (void*)time_info_db, &zErrMsg);
	if( rc != SQLITE_OK ){
		printf("%d:ERROR\n",__LINE__);
		sqlite3_free(zErrMsg);
		res = -1 ;
	}

	sqlite3_close(db);
	return res ;
}
#endif
static int db_creat_table_test_t1(char* dbname)
{

	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;
	//const char* data = "Callback function called";

	int res = 0 ;

	FILE *fp;

	lt_info("creat table file if file not exist");
	fp = fopen(dbname , "rb");
	if( fp != NULL )
	{
		fclose(fp);
		return 0;
	}


	/* Open database */
	rc = sqlite3_open(dbname, &db);
	if ( rc != SQLITE_OK )
	{
		lt_error("table open failed\n");
		res = -1;
		return res;
	}


	   /* Create SQL statement */
	//PRIMARY KEY CAN AUTO ++
	sql = 	"CREATE TABLE test_t1("  \
			"id INT PRIMARY KEY     NOT NULL," \
			"time_input     TEXT," \
			"time_output    TEXT," \
			"info           TEXT," \
			"reserve1       TEXT," \
			"reserve2       TEXT," \
			"reserve3       TEXT);";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, db_callback_display, 0, &zErrMsg);
	if( rc != SQLITE_OK )
	{
		lt_error("table creat failed");
		sqlite3_free(zErrMsg);
		res = -1 ;
	}

    sqlite3_close(db);

    return res ;
}


static int db_get_table(char* dbname)
{
   //DEBUG_ENTER();
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   //const char* data = "Callback function called";

   int res = 0 ;
	/* Open database */
	rc = sqlite3_open(dbname, &db);
	if ( rc != SQLITE_OK )
	{
		printf("%d:ERROR\n",__LINE__);
		res = -1;
		return res;
	}

//   if( rc ){
//      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
//      exit(0);
//   }else{
//      fprintf(stderr, "Opened database successfully\n");
//   }
    sql = "SELECT * from test_t1";

    char** pResult;
    int nRow;
    int nCol;
    rc = sqlite3_get_table(db,sql,&pResult,&nRow,&nCol,&zErrMsg);
    if (rc != SQLITE_OK)
    {
//      fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_close(db);
        sqlite3_free(zErrMsg);

    	lt_error("%d:ERROR\n",__LINE__);
    	res = -1 ;
    	return res;
    }

#if 1
    u32 nIndex = nCol;
    u32 i,j;
    lt_info("nRow=%d,nCol=%d\n",nRow,nCol);
    for( i=0;i<nRow;i++)
    {
        for( j=0;j<nCol;j++)
        {
/*
            strOut+=pResult[j];
            strOut+=":";
            strOut+=pResult[nIndex];
            strOut+="\n";
*/
            lt_info("nRow=%d,nCol=%d :%s\n",i,j,pResult[nIndex]);
            ++nIndex;
        }
    }
#endif

    sqlite3_free_table(pResult);
    sqlite3_close(db);
    //DEBUG_EXIT();
    return nRow * nCol;
}

static int db_insert_test_t1(char* dbname)
{
    //DEBUG_ENTER();
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
  // const char* data = "Callback function called";

   int res = 0 ;
	/* Open database */
	rc = sqlite3_open(dbname, &db);
	if ( rc != SQLITE_OK )
	{
		printf("%d:ERROR\n",__LINE__);
		res = -1;
		return res;
	}

	/* Create SQL statement */
	//PRIMARY KEY CAN AUTO ++,when id was set null
	sql = "INSERT INTO test_t1 (id,time_input,time_output,info) "  \
		 "VALUES (null, '20170327', 'null','jasmine'); ";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, db_callback_display, 0, &zErrMsg);
	if( rc != SQLITE_OK )
	{
		lt_error("zErrMsg=%s\n",zErrMsg);
		sqlite3_free(zErrMsg);
		res = -1 ;
	}

    sqlite3_close(db);
     //DEBUG_EXIT();
    return res ;
}


#if 0
static int db_delete_test_t1(char* dbname)
{
    //DEBUG_ENTER();
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
  // const char* data = "Callback function called";

   int res = 0 ;
	/* Open database */
	rc = sqlite3_open(dbname, &db);
	if ( rc != SQLITE_OK )
	{
		printf("%d:ERROR\n",__LINE__);
		res = -1;
		return res;
	}

	/* Create SQL statement */
	//PRIMARY KEY CAN AUTO ++,when id was set null
	sql = "DELETE FROM test_t1 WHERE ID = ( SELECT MAX(ID) FROM test_t1 )";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, db_callback_display, 0, &zErrMsg);
	if( rc != SQLITE_OK )
	{
		lt_error("%d:ERROR\n",__LINE__);
		sqlite3_free(zErrMsg);
		res = -1 ;
	}

    sqlite3_close(db);
     //DEBUG_EXIT();
    return res ;
}

#endif













#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

sqlite3 * db = NULL;

static int sn = 0;

void create_table(char * filename)
{
    char * sql;
    char * zErrMsg = 0;
    int rc;

    rc = sqlite3_open(filename,&db);
    //rc = sqlite3_open_v2(filename,&db,SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    if (rc)
    {
        fprintf(stderr,"can't open database%s\n",sqlite3_errmsg(db));
        sqlite3_close(db);
    }
    sql =  "CREATE TABLE save_data(num integer primary key, id int, data text, time text)";
    sqlite3_exec(db,sql,0,0,&zErrMsg);
}

void close_table(void)
{
    sqlite3_close(db);
}


void insert_record(char * table,int id,char * data,char * time)
{
    char * sql;
    char * zErrMsg = NULL;

    sql = sqlite3_mprintf("insert into %s values(null,%d,'%s','%s')",table,id,data,time);
    sqlite3_exec(db,sql,0,0,&zErrMsg);
    sqlite3_free(sql);
}

int sqlite_callback(void * userData,int numCol,char ** colData,char **colName)
{
    int i,offset = 0;
    char * buf,* tmp;

    buf = (char *)malloc(40 * sizeof(char));
    tmp = buf;
    memset(buf,0,40);

    //printf("%d %d\n",sizeof(buf),strlen(buf));
    for (i = 1;i < numCol;i++)
    {
        buf = buf + offset;
        sprintf(buf,"%s ",colData[i]);
        offset = strlen(colData[i]) + 1; //it's need one place for put a blank so the lenght add 1
    //    printf("i %d offset %d\n",i, offset);
    }
    printf("%.4d. %s \n",++sn,tmp);

    free(tmp);
    tmp = NULL;
    buf = NULL;

    return 0;
}


void search_all(char * table)
{
    char * sql;
    char * zErrMsg = 0;

    sn = 0;

    sql = sqlite3_mprintf("select * from %s",table);
    sqlite3_exec(db,sql,&sqlite_callback,0,&zErrMsg);
    sqlite3_free(sql);

}

void search_by_id(char * table,char * id)
{
    char * sql;
    char * zErrMsg = 0;

    sn = 0;

    sql = sqlite3_mprintf("select * from %s where id=%s",table,id);
    sqlite3_exec(db,sql,&sqlite_callback,0,&zErrMsg);
    sqlite3_free(sql);
}

void delete_by_id(char * table,char * id)
{
    int rc ;
    char * sql;
    char * zErrMsg = 0;
    sql = sqlite3_mprintf("delete from %s where id=%s",table,id);
    rc = sqlite3_exec(db,sql,0,0,&zErrMsg);
    if (rc)
    {}
    sqlite3_free(sql);
}

void delete_all(char * table)
{
    char * sql;
    char * zErrMsg = 0;

    sql = sqlite3_mprintf("delete from %s",table);
    sqlite3_exec(db,sql,0,0,&zErrMsg);
    sqlite3_free(sql);
}

int main_2(int agrc,char * argv[])
{
    char * filename = "data.db";
    int i ;

    create_table(filename);

    for (i = 0 ;i < 10;i++)
    {
        insert_record("save_data",2000,"5678","2012-03-12 09:43:56");
        insert_record("save_data",2001,"5678","2012-03-12 09:43:56");
        insert_record("save_data",2002,"5678","2012-03-12 09:43:56");
        insert_record("save_data",2003,"5678","2012-03-12 09:43:56");
        insert_record("save_data",2004,"5678","2012-03-12 09:43:56");
        insert_record("save_data",2005,"5678","2012-03-12 09:43:56");
        insert_record("save_data",2006,"5678","2012-03-12 09:43:56");
        insert_record("save_data",2007,"5678","2012-03-12 09:43:56");
    }

    search_all("save_data");

    close_table();

    return 0;
}



//main_3
int main(int agrc,char * argv[])
{
	//d8 * dbname = "data3.db";
	//sqlite3 *db3=NULL;
	hz_db_o hz_db;
	//s32 res = 0;

	hz_tmp_o tmp;

	d8 log_file[100];
	sprintf(log_file,"%s.log",argv[0]);
	hz_log_init(0,".",log_file );
	lt_warn("warning test");


	hz_db_o_init(&hz_db,"data3.db");

do
{
	d8 * sql = 	"CREATE TABLE test_t1("  \
			"id integer PRIMARY KEY not null," \
			"time_input     TEXT," \
			"time_output    TEXT," \
			"info           TEXT," \
			"reserve1       TEXT," \
			"reserve2       TEXT," \
			"reserve3       TEXT);";
	tmp.ret = hz_db_create_table(&hz_db,sql);
	tmp.ret = hz_db_open_table(&hz_db);
	if ( hz_db.db == NULL )
	{
		return 0;
	}
	if ( tmp.ret.v != 0 )
	{
		lt_error("tmp.ret != 0");
		return 0;
	}

	sql = 	"INSERT INTO test_t1 (id,time_input,time_output,info) "  \
	 	"VALUES (null, '20170327', 'null','jasmine'); ";
	tmp.ret = hz_db_exec(&hz_db,"test_t1",sql);
	if ( tmp.ret.v < 0 )
	{
		break;
	}
	sql = 	"INSERT INTO test_t1 (id,time_input,time_output,info) "  \
	 	"VALUES (null, '20170327', 'null','jasmine2'); ";
	tmp.ret = hz_db_exec(&hz_db,"test_t1",sql);
	if ( tmp.ret.v < 0 )
	{
		break;
	}
	sql = 	"INSERT INTO test_t1 (id,time_input,time_output,info) "  \
	 	"VALUES (null, '20170327', 'null','jasmine2'); ";
	tmp.ret = hz_db_exec(&hz_db,"test_t1",sql);
	if ( tmp.ret.v < 0 )
	{
		break;
	}
	lt_info("********************* search all");
	hz_db_search_all(&hz_db,"test_t1");
	lt_info("********************* search id 1");
	hz_db_search_by_id(&hz_db,"test_t1",1);
	lt_info("********************* search id 2");
	hz_db_search_by_id(&hz_db,"test_t1",2);
	lt_info("********************* search id max");
	hz_db_search_by_id_max(&hz_db,"test_t1");
	lt_info("********************* delete id 2");
	hz_db_delete_by_id(&hz_db,"test_t1",2);

	lt_info("********************* search all");
	hz_db_search_all(&hz_db,"test_t1");
	lt_info("********************* delete id max");
	hz_db_delete_by_id_max(&hz_db,"test_t1");
	lt_info("********************* search all");
	hz_db_search_all(&hz_db,"test_t1");
	lt_info("********************* delete all");
	hz_db_delete_all(&hz_db,"test_t1");
	lt_info("********************* search all");
	hz_db_search_all(&hz_db,"test_t1");

}while(0);
	hz_db_close_table(&hz_db);
	return 0;
}




