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
#ifndef __HZ_SOCKET_H__
#define __HZ_SOCKET_H__








/**
@brief socket_creat_arg_t
ip_str:server ip
port :listen port
*/
typedef struct
{
	d8 ip_str[13];//192.168.9.9
	s32 port;
	hz_thread_t thread_free;        //user self define mode. thread function of handle (creat thread_send,thread_recv,thread_heartbeat,if not NULL,then thread_send thread_recv thread_heartbeat  will invalid)
	hz_thread_t thread_send;	//thread function of send handle socket action,argument is self socket_creat_arg_t type
	hz_thread_t thread_recv;;	//thread function of recv handle socket action,argument is self socket_creat_arg_t type
	hz_thread_t thread_heartbeat;;	//thread function of heartbeat handle socket action,argument is self socket_creat_arg_t type
	s32 connectfd;
	s32 hz_connectfd;                   		//independent of socket or other commnication type
	struct  sockaddr_in server;
	struct  sockaddr_in client;
	u32 flag;//1:server  0:client
	u32 disconnect;//0:reconnect  others:not reconnect
	s32 recv_timeout; // 0:default 60s   <0:do not set time out  >0:set  recv_timeout s timeout
	void* userdata[16];
	hz_mutex_t *usermutex[4];
	FILE *logfile_fp;
	
}socket_creat_arg_t;


typedef struct _socket_data_t_
{
	u32 data_len;  // data_len + reserve + (extern) data len
	u32 reserve[4];
}socket_data_head_t;

typedef struct _socket_msg_t_
{
	u32 head;//0x12345678

	u32 msg_len;  // msg_len + msg_type + ack_flag + msg_id + reserve[8] + msg_p +  msg_p length + checkcode	
	//data
	u32 msg_type;		
	u32 ack_flag;	
	u32 msg_id;
	u32 reserve[8];
	void *msg_p;
	u32 checkcode;
	u32 tail;//0x87654321
	///u8  data[MIN_MSG_DATA_LENGTH-4];
}socket_msg_t;

typedef struct _socket_msg_user_t_
{
	u32 msg_type;		
	u32 ack_flag;	
	u32 msg_id;
	void *msg_p;
	u32 buflen;
}socket_msg_user_t;



typedef struct _socket_msg_head_t_
{
	u32 head;//0x12345678
//#define SOCKET_MSG_LEN_MAX ( 8192 - sizeof(u32)*3 ) //去掉头尾，并预留 4 个字节缓冲
	u32 msg_len;  // sizeof(socket_msg_head_t) +  sizeof(socket_msg_tail_t) + sizeof (data struct)
	//data
	u32 msg_type;		
	u32 ack_flag;	
	u32 msg_id;
	u32 reserve[8];
}socket_msg_head_t;

#define SOCKET_MSG_FLAG_HEAD 0x12345678
#define SOCKET_MSG_FLAG_TAIL 0x87654321
#define SOCKET_MSG_LEN_MAX ( 8192 - 4 ) //预留 4 个字节缓冲
#define SOCKET_MSG_DATA_LEN_MAX ( SOCKET_MSG_LEN_MAX - sizeof(socket_msg_head_t) - sizeof(socket_msg_tail_t) ) 
#define SOCKET_MSG_HEAD_LEN ( sizeof(socket_msg_head_t) )
#define SOCKET_MSG_TAIL_LEN ( sizeof(socket_msg_tail_t) )
typedef struct _socket_msg_tail_t_
{
	u32 checkcode;
	u32 tail;//0x87654321
}socket_msg_tail_t;

typedef struct _socket_msg_min_t_
{
	socket_msg_head_t msg_head;
	socket_msg_tail_t msg_tail;
}socket_msg_min_t;


typedef enum
{
	SOCKET_MSG_TYPE_HEART_BEAT,
	SOCKET_MSG_TYPE_REBOOT,
	SOCKET_MSG_TYPE_01, //slave:license write   	master:
	SOCKET_MSG_TYPE_02, //slave:license read	master:get license data
	SOCKET_MSG_TYPE_03, //
	SOCKET_MSG_TYPE_04, //
	SOCKET_MSG_TYPE_05,	
}socket_msg_type_t;


/**************************************
应答标志ack_flag说明:
	作为消息的主动发起方,该字段恒为0x00。如果作为应答消息,该字段作为应答标志。应答消息中如果该字段非0X01,则表明最近收到的命令无法处理或出错。
	主发起方收到对方应答标志非 0X00 的应答后,对应答标志之后的数据不解析，不处理，只有应答标志为0x00,应答标志之后的数据才有意义。

应答标志编码
0X00 表明本消息为发送消息
0x01 表明本消息为ACK消息，且消息正确接收后的应答
0X02 消息号错，收到接收模块不支持的命令
0X04 消息数据错，消息数据超过接收模块支持的范围
0X08 操作失败，接收模块不能按消息要求完成对接收模块的控制
0X10 接收模块忙，接收模块还未完成消息处理，无法返回数据，主要用于消息处理需要很长时间的消息
其它  保留
**************************************/
typedef enum
{
	SOCKET_MSG_ACK_FLAG_SEND=0X00,
	SOCKET_MSG_ACK_FLAG_RECV_SUCCESS=0X01,
	SOCKET_MSG_ACK_FLAG_MSG_TYPE_ERROR=0X02,//unsupport
	SOCKET_MSG_ACK_FLAG_MSG_DATA_ERROR=0X04,
	SOCKET_MSG_ACK_FLAG_MSG_ACTION_FAIL=0X08,
	SOCKET_MSG_ACK_FLAG_BUSY=0X10,
}socket_msg_ack_flag_t;


typedef enum
{
	HZ_SOCK_FLAG_NONE=0X00,
	HZ_SOCK_FLAG_WAITALL=0X01,
	//HZ_SOCK_FLAG_DONTWAIT=0X02,	
}hz_sock_flag_t;


/*
HZ_SOCK_FLAG_WAITALL
*/
s32 socket_read(socket_creat_arg_t *sock_arg,d8 * buf,s32 buflen,hz_sock_flag_t flag);   //fd should be change to  socket_creat_arg_t
s32 socket_write(socket_creat_arg_t *sock_arg,d8 * buf,s32 buflen,hz_sock_flag_t flag);  //fd should be change to  socket_creat_arg_t
hz_ret_t thread_socket_tcp_s_creat(socket_creat_arg_t *socket_creat_arg);
hz_ret_t thread_socket_tcp_c_creat(socket_creat_arg_t *socket_creat_arg);     // block mode


s32 socket_msg_util_send_handle(socket_creat_arg_t *sock_arg,socket_msg_user_t *msg_arg);
//fd should be change to  socket_creat_arg_t
//s32 socket_msg_util_send_handle_(socket_creat_arg_t *sock_arg,socket_msg_type_t msg_type,socket_msg_ack_flag_t ack_flag ,s32 msg_id,d8 * buf,s32 buflen);  

s32 socket_msg_util_recv_handle(socket_creat_arg_t *sock_arg,socket_msg_user_t *msg_arg);



#endif /* !__HZ_FILE_H__ */
