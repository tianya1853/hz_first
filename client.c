#include "hz_include.h"




void *client_send_handle(void*arg)
{
	s32 res=0;
	d8 *string="hello";
	//dont add   pthread_detach( pthread_self() )
	socket_creat_arg_t *sock_arg=(socket_creat_arg_t *)arg;
	while(1)
	{
		lt_sleep(30);		
		res=socket_write(sock_arg,string,strlen(string),0);		
		if ( res != SUCCESS )
		{
			//网络异常
			lt_error("socket send FAIL \n");
			break;
		}
		lt_info("fd %d send string %s",sock_arg->connectfd,string);		
	}
	return NULL;
}

void *client_recv_handle(void*arg)
{
	s32 res=0;
	d8 string[20];
	socket_creat_arg_t *sock_arg=(socket_creat_arg_t *)arg;
	//dont add   pthread_detach( pthread_self() )
	while(1)
	{		
		///lt_sleep(1);	
		memset(string,0,sizeof(string))	;
		res=socket_read(sock_arg,string,sizeof(string)-1,0);		
		if ( res <= 0 )
		{
			//网络异常
			lt_error("socket recv FAIL \n");
			break;
		}
		lt_info("fd %d recv string %s",sock_arg->connectfd,string);		
	}
	return NULL;
}




void *client_send_msg_handle(void*arg)
{
	s32 res=0;
	d8 *string="msg hello";
	socket_msg_user_t msg_arg;
	//dont add   pthread_detach( pthread_self() )
	socket_creat_arg_t *sock_arg=(socket_creat_arg_t *)arg;
	while(1)
	{
		lt_sleep(4);		
		//res=socket_write(sock_arg,string,strlen(string),0);		
		//res = socket_msg_util_send_handle(sock_arg,SOCKET_MSG_TYPE_01,SOCKET_MSG_ACK_FLAG_SEND,0,string,strlen(string));
		msg_arg.msg_type = SOCKET_MSG_TYPE_01 ;		
		msg_arg.ack_flag = SOCKET_MSG_ACK_FLAG_SEND;	
		msg_arg.msg_id = 0;
		msg_arg.msg_p = string;
		msg_arg.buflen = strlen(string);
		res = socket_msg_util_send_handle(sock_arg,&msg_arg);
		if ( res != SUCCESS )
		{
			//网络异常
			lt_error("socket send FAIL \n");
			break;
		}
		lt_info("fd %d send string %s",sock_arg->connectfd,string);		
	}
	return NULL;
}



void *client_recv_msg_handle(void*arg)
{
	s32 res=0;
	//d8 string[20];
	socket_creat_arg_t *sock_arg=(socket_creat_arg_t *)arg;
	//dont add   pthread_detach( pthread_self() )
	while(1)
	{	
		socket_msg_user_t msg_arg;
		res = socket_msg_util_recv_handle(sock_arg,&msg_arg);				
		if ( res == FAIL )
		{
			lt_error("socket recv FAIL \n");
			break;
		}else
		{
			lt_info("fd %d recv msg_arg->buflen=%d string %s",sock_arg->connectfd,msg_arg.buflen,msg_arg.msg_p);
		}
		//break;				
	}
	return NULL;
}

int main (int argc,char **argv)
{
	u32 i=0;
	d8 log_file[100];

	sprintf(log_file,"%s.log",argv[0]);
	hz_log_init(0,".",log_file );




	#define SOCKET_COUNT  1//1000
	socket_creat_arg_t client[SOCKET_COUNT];



	for ( i=0;i<SOCKET_COUNT;i++)
	{
		memset(&client[i],0,sizeof(client[i]));
		sprintf(client[i].ip_str,"127.0.0.1");
		client[i].port=1234;
		//client[i].thread_recv.thread_f=client_recv_handle;
		//client[i].thread_send.thread_f=client_send_handle;

		client[i].thread_recv.thread_f=client_recv_msg_handle;
		client[i].thread_send.thread_f=client_send_msg_handle;
		thread_socket_tcp_c_creat(&client[i]);
		lt_msleep(10);
	}
	
	lt_info("hello done");
	while(1)
	{
		lt_sleep(1);
	}
	return 0;
}
