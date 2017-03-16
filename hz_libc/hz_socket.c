/*******************************************************************
Copyright (C) hz
Version:      v0.0.1
FileInfo------------------------------------------------------------
Filename:     
Author:       hz
Date:         
OS:           Linux-3.3.0
Complier:     arm-linux-gnueabi-gcc (version: 4.6.3)
HardWare:     
Version :     v0.0.1
Description:
History------------------------------------------------------------
Author:
Date:
Version:
Description:
*******************************************************************/



/**
socket thinking  将socket通信想象为其他方式的通信没有socket的东西，构架不依赖任何通信协议的架构
判断socket连接状态，以心跳为准，其他方式均不可靠，且心跳在所有通信方式中通用
设置独立于socket的唯一连接句柄，当心跳断开时，赋值非socket句柄为NULL ,其他使用同一句柄的线程检测句柄是否为空，并结束线程
接收线程当为阻塞模式时必须有接收超时，在接收超时时赋值非socket句柄为NULL

all of parameter passing  should be change to  pointer of socket_creat_arg_t*,and top of parameter must is a globle parameter
package thread thread_socket_tcp_s_creat 
hz_ret_t thread_cread_handle(socket_creat_arg_t *socket_creat_arg);
{

	if ( socket_creat_arg->send_fun  != NULL )
	{
		pthread_create(send_fun);
	}

	if ( socket_creat_arg->recv_fun  != NULL )
	{
		pthread_create(recv_fun);
	}

	if ( socket_creat_arg->heartbeat_fun  != NULL )
	{
		pthread_create(heartbeat_fun);
	}	
}



thread_socket_tcp_s_creat
**/

#include "hz_include.h"
void * socket_tcp_s_creat(void * arg);
void * socket_tcp_c_creat(void * arg);


void socket_creat_arg_t_dump(socket_creat_arg_t *sock_arg)
{
	lt_debug("sock_arg              =%p\n", sock_arg); //%p not need 0x ,
	lt_debug("sock_arg->connectfd   =0x%x\n", sock_arg->connectfd);
	lt_debug("sock_arg->ip_str      =%s\n", sock_arg->ip_str);
	lt_debug("sock_arg->port        =0x%x\n", sock_arg->port);

	lt_debug("sock_arg->thread_free.thread_handle      =0x%x\n", sock_arg->thread_free.thread_handle);
	lt_debug("sock_arg->thread_free.thread_f           =%p\n", sock_arg->thread_free.thread_f);
	lt_debug("sock_arg->thread_free.thread_arg         =%p\n", sock_arg->thread_free.thread_arg);
	lt_debug("sock_arg->thread_free.thread_result      =%p\n", sock_arg->thread_free.thread_result);

	lt_debug("sock_arg->thread_send.thread_handle      =0x%x\n", sock_arg->thread_send.thread_handle);
	lt_debug("sock_arg->thread_send.thread_f           =%p\n", sock_arg->thread_send.thread_f);
	lt_debug("sock_arg->thread_send.thread_arg         =%p\n", sock_arg->thread_send.thread_arg);
	lt_debug("sock_arg->thread_send.thread_result      =%p\n", sock_arg->thread_send.thread_result);

	lt_debug("sock_arg->thread_recv.thread_handle      =0x%x\n", sock_arg->thread_recv.thread_handle);
	lt_debug("sock_arg->thread_recv.thread_f           =%p\n", sock_arg->thread_recv.thread_f);
	lt_debug("sock_arg->thread_recv.thread_arg         =%p\n", sock_arg->thread_recv.thread_arg);
	lt_debug("sock_arg->thread_recv.thread_result      =%p\n", sock_arg->thread_recv.thread_result);

	lt_debug("sock_arg->thread_heartbeat.thread_handl  =0x%x\n", sock_arg->thread_heartbeat.thread_handle);
	lt_debug("sock_arg->thread_heartbeat.thread_f      =%p\n", sock_arg->thread_heartbeat.thread_f);
	lt_debug("sock_arg->thread_heartbeat.thread_arg    =%p\n", sock_arg->thread_heartbeat.thread_arg);
	lt_debug("sock_arg->thread_heartbeat.thread_result =%p\n", sock_arg->thread_heartbeat.thread_result);
}
/*
close-----关闭本进程的socket id，但链接还是开着的，用这个socket id的其它进程还能用这个链接，能读或写这个socket id

shutdown--则破坏了socket 链接，读的时候可能侦探到EOF结束符，写的时候可能会收到一个SIGPIPE信号，这个信号可能直到

注意:
    1>. 如果有多个进程共享一个套接字，close每被调用一次，计数减1，直到计数为0时，也就是所用进程都调用了close，套

接字将被释放。
    2>. 在多进程中如果一个进程中shutdown(sfd, SHUT_RDWR)后其它的进程将无法进行通信. 如果一个进程close(sfd)将不会


warning: is process not thread
*/

static void *thread_socket_module_entry_point(void *arg)
{
	//hz_ret_t ret = RET_SUCCESS ;
	s32 res = 0;
	//s32 i = 0;
	//s32 stmp = 0;
	//u32 utmp = 0;
	//socket_creat_arg_t curr_arg;
	//memcpy(&curr_arg,arg,sizeof(curr_arg));
	//socket_creat_arg_t *sock_arg=&curr_arg;
	socket_creat_arg_t *sock_arg=(socket_creat_arg_t *)arg;

	lt_debug("thread %s is starting. Argument was %p\n",__FUNCTION__,arg);

	if (	sock_arg->flag == 1 ) //server
	{
		pthread_detach(pthread_self());
	}
	


	if( sock_arg->thread_free.thread_f == NULL )
	{
		if ( sock_arg->thread_heartbeat.thread_f != NULL )
		{
			if ( sock_arg->thread_heartbeat.thread_arg == NULL )
			{
				sock_arg->thread_heartbeat.thread_arg = sock_arg;
			}
			lt_info("creat thread thread_heartbeat=%p",sock_arg->thread_heartbeat.thread_f);
			res = pthread_create(&(sock_arg->thread_heartbeat.thread_handle),NULL, sock_arg->thread_heartbeat.thread_f,sock_arg);
			if( res != 0 )
			{
				lt_error("Thread creation failed!\n");
			}
		}else
		{
			lt_info("thread_heartbeat is NULL");
		}


		if ( sock_arg->thread_recv.thread_f != NULL )
		{
			if ( sock_arg->thread_recv.thread_arg == NULL )
			{
				sock_arg->thread_recv.thread_arg = sock_arg;
			}
			lt_info("creat thread thread_recv=%p",sock_arg->thread_recv.thread_f);
			res = pthread_create(&(sock_arg->thread_recv.thread_handle),NULL, sock_arg->thread_recv.thread_f,sock_arg);
			if( res != 0 )
			{
				lt_error("Thread creation failed!\n");
			}
		}else
		{
			lt_info("thread_recv is NULL");
		}

		if ( sock_arg->thread_send.thread_f != NULL )
		{
			if ( sock_arg->thread_send.thread_arg == NULL )
			{
				sock_arg->thread_send.thread_arg = sock_arg;
			}
			lt_info("creat thread thread_send=%p",sock_arg->thread_send.thread_f);
			res = pthread_create(&(sock_arg->thread_send.thread_handle),NULL, sock_arg->thread_send.thread_f,sock_arg);
			if( res != 0 )
			{
				lt_error("Thread creation failed!\n");
			}
		}else
		{
			lt_info("thread_send is NULL");
		}
	}else
	{
		lt_info("thread_free not NULL,then ignore thread_heartbeat  thread_send  thread_recv");
	}

	
	socket_creat_arg_t_dump(sock_arg);
	
	if( sock_arg->thread_free.thread_f == NULL )
	{

		if ( sock_arg->thread_heartbeat.thread_f != NULL )
		{
			lt_debug("waiting  thread_heartbeat stop");
			res = pthread_join(sock_arg->thread_heartbeat.thread_handle, &(sock_arg->thread_heartbeat.thread_result) );
			if( res != 0 )
			{
				lt_error("Thread join failed!\n");				
			}
			lt_debug("thread_heartbeat had stop");
			close(sock_arg->connectfd);
		}
		if ( sock_arg->thread_recv.thread_f != NULL )
		{
			lt_debug("waiting  thread_recv stop");
			res = pthread_join(sock_arg->thread_recv.thread_handle, &(sock_arg->thread_recv.thread_result) );
			if( res != 0 )
			{
				lt_error("Thread join failed!\n");
			}
			lt_debug("thread_recv had stop");
			close(sock_arg->connectfd);
		}
		if ( sock_arg->thread_send.thread_f != NULL )
		{
			lt_debug("waiting  thread_send stop");
			res = pthread_join(sock_arg->thread_send.thread_handle, &(sock_arg->thread_send.thread_result) );
			if( res != 0 )
			{
				lt_error("Thread join failed!\n");
			}
			lt_debug("thread_send had stop");
			close(sock_arg->connectfd);
		}

	}	
	lt_info("socket fd %d  had stop",sock_arg->connectfd);

	return  NULL;
}







/**
thread_socket_tcp_s_creat  thread_tcp_s_creat creat one tcp server，
must close connectfd when  thread socket_creat_arg->thread_f  over
@param socket_creat_arg  socket_creat_arg_t type   and must be a global argument
*/
hz_ret_t thread_socket_tcp_s_creat(socket_creat_arg_t *socket_creat_arg)
{
	pthread_t thread_server_app;
	hz_ret_t ret = RET_SUCCESS ;
	s32 res = 0;
	lt_info("will creat thread socket server");
	do
	{
		res = pthread_create(&thread_server_app,NULL,socket_tcp_s_creat,socket_creat_arg);
		if( res != 0 )
		{
			lt_error("Thread creation failed!\n");
			ret = RET_FAIL ;	
			break ;	
		}
	}while(0);
	return 0 - ret;	
}

/**
thread_socket_tcp_c_creat  thread_tcp_s_creat 创建一个tcp server，
@param socket_creat_arg  socket_creat_arg_t type   and must be a global argument
*/
hz_ret_t thread_socket_tcp_c_creat(socket_creat_arg_t *socket_creat_arg)
{
	pthread_t thread_client_app;
	hz_ret_t ret =RET_SUCCESS ;
	s32 res = 0;
	lt_info("will creat thread socket client");
	do
	{
		res = pthread_create(&thread_client_app,NULL,socket_tcp_c_creat,socket_creat_arg);
		if( res != 0 )
		{
			lt_error("Thread creation failed!\n");
			ret = RET_FAIL ;	
			break ;	
		}
	}while(0);
	return 0 - ret;	
}

/**
thread_tcp_s_creat 创建一个tcp server，
@param thread_f  函数指针，指向创建的tcp server的线程入口函数
@param port	port
@return 返回值描述
*/
void * socket_tcp_s_creat(void * arg)
{
	//s32  res = 0 ;
	//s32 ret=HZ_SUCCESS;
//#define  PORT 1234
//#define  PORT 9999
	socket_creat_arg_t * thread_arg = (socket_creat_arg_t *)arg;


#define  BACKLOG 2  
	//lt_debug("thread %s is starting. Argument was %s\n",__FUNCTION__, (char *)arg);
	
	s32  listenfd, connectfd;
	struct  sockaddr_in server;
	struct  sockaddr_in client;
	socklen_t  addrlen;	
	s32 opt =SO_REUSEADDR;
	
	pthread_detach(pthread_self());

	addrlen =sizeof(client);  

	bzero(&server,sizeof(server));  
	server.sin_family=AF_INET;  
	server.sin_port=htons( thread_arg->port );  
	server.sin_addr.s_addr= htonl(INADDR_ANY);  



	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)  
	{  
		perror("Creating  socket failed.");  
		exit(1);
	}

/**
一般来说，一个端口释放后会等待两分钟之后才能再被使用，SO_REUSEADDR是让端口释放后立即就可以被再次使用。
SO_REUSEADDR用于对TCP套接字处于TIME_WAIT状态下的socket，才可以重复绑定使用。server程序总是应该在调用bind()之前设置SO_REUSEADDR套接字选项。TCP，先调用close()的一方会进入TIME_WAIT状态
*/
	setsockopt(listenfd,SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));  

	if(bind(listenfd, (struct sockaddr *)&server, sizeof(server)) == -1) {  
		perror("Binderror.");
		exit(1);
	}
	if(listen(listenfd,BACKLOG)== -1){  /* calls listen() */  
		perror("listen()error\n");  
		exit(1);  
	}  
	

	s32 casx=CASX_INIT;
	while(casx)
	{
		switch(casx)
		{
		case CASX_INIT:
			{
				lt_info("waiting client accept");
				if( (connectfd = accept(listenfd,(struct sockaddr*)&client,&addrlen))==-1) 
				{
					if(errno==EINTR)
					{
						continue;
					}
					else
					{
						lt_error("cannot accept client connect request");
						casx = CASX_FREE_MEM ;
						break;
					}
				}



				/*
				这里我们要涉及到一个结构：
				struct timeval
				{
					time_t tv_sec;
					time_t tv_usec;
				};
				这里第一个域的单位为秒，第二个域的单位为微秒。



SO_RCVTIMEO和SO_SNDTIMEO ，它们分别用来设置socket接收数据超时时间和发送数据超时时间。
因此，这两个选项仅对与数据收发相关的系统调用有效，这些系统调用包括：send, sendmsg, recv, recvmsg, accept, connect 。
这两个选项设置后，若超时， 返回-1，并设置errno为EAGAIN或EWOULDBLOCK.
其中connect超时的话，也是返回-1, 但errno设置为EINPROGRESS
				*/
				struct timeval tv_out;
				tv_out.tv_sec  = 60; //6s will timeout    //recv timeout
				tv_out.tv_usec = 0; 
				//填充这个结构后，我们就可以以如下的方式调用这个函数：				
				setsockopt(connectfd, SOL_SOCKET, SO_RCVTIMEO, &tv_out, sizeof(tv_out));//(具体参数可以man一下，或查看MSDN)

				lt_info("Yougot a connection from cient's ip is %s, prot is %d\n",inet_ntoa(client.sin_addr),htons(client.sin_port));  
				//casx = CASX_STEP_00 ;
				//break;
			}
			casx = CASX_STEP_00 ;
			break;
		case CASX_STEP_00://creat thread
			{
				s32 res;
				pthread_t thread_server_app;

				//void *thread_result;
				//state_tcp_client_online = SUCCESS ;


				lt_debug("will creat thread thread_server_app and connectfd=%d",connectfd);
/**
must be reentrant(可重入) function/thread  
*/
				thread_arg->connectfd = connectfd;
				thread_arg->hz_connectfd = connectfd;
				thread_arg->flag = 1; //server 
				res = pthread_create(&thread_server_app,NULL,thread_socket_module_entry_point ,thread_arg);
				if( res != 0 )
				{
					lt_error("Thread creation failed!\n");
					casx = CASX_FREE_MEM ;
					break;
					//exit(EXIT_FAILURE);
				}
//must add pthrea_join or pthread_detach

/*
				lt_debug("waiting pthread thread_server_app finish");

				res = pthread_join(thread_server_app, &thread_result);
				if (res != 0)
				{
					lt_error("Thread join failed!/n");
					exit(EXIT_FAILURE);
				}
				lt_info("thread server_app had finished...\n");
				close(connectfd);

				//close(listenfd);
				lt_info("waiting accept new tcp socket...\n");
*/
				//state_tcp_client_online = FAIL ;
				//sleep(1);
				casx = CASX_INIT ;
				break;
			}
			casx = CASX_FREE_MEM ;
			break;
		case CASX_FREE_MEM:
			{
			}
			casx = CASX_CLOSE_FILE ;
			break;
		case CASX_CLOSE_FILE:
			{
				close(connectfd);
				close(listenfd);
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
	return NULL;
}


/**
thread_tcp_c_creat 创建一个tcp server，
@param thread_f  函数指针，指向创建的tcp server的线程入口函数
@param port	port
@return 返回值描述
*/

void * socket_tcp_c_creat(void * arg)
{
	//s32  res = 0 ;

	lt_debug("thread %s is starting. Argument was %p\n",__FUNCTION__,arg);
	socket_creat_arg_t * thread_arg = (socket_creat_arg_t *)arg;
	s32  connectfd;
	struct  sockaddr_in server;
	//struct  sockaddr_in client;
	//socklen_t  addrlen;

	//lt_info("try connect server");
	//addrlen =sizeof(client);  

	s32 casx=CASX_INIT;
	pthread_detach(pthread_self());

	
	while(casx)
	{
		switch(casx)
		{
		case CASX_INIT:
			{
				if((connectfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)  
				{  
					perror("Creating  socket failed.");  
					exit(1);
				}

				//s32 opt =SO_REUSEADDR;
				//setsockopt(connectfd,SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));  

				bzero(&server,sizeof(server));  
				server.sin_family=AF_INET;  
				server.sin_port=htons(thread_arg->port);  
				server.sin_addr.s_addr = inet_addr(thread_arg->ip_str);



				
 
				 /* 客户程序发起连接请求 */ 
				while(1)
				{
					lt_info("try connect server");
					int err_log = connect(connectfd, (struct sockaddr*)&server, sizeof(server));      // 主动连接服务器  
					if(err_log != 0)  
					{  
						lt_error("Connect Error:%s\n",strerror(errno) );
						//close(sockfd);  
						//exit(-1);  
						lt_sleep(2);
					}else
					{
						break;
					}					
				}
				/*

				这里我们要涉及到一个结构：
				struct timeval
				{
						time_t tv_sec;
						time_t tv_usec;
				};
				这里第一个域的单位为秒，第二个域的单位为微秒。
				*/
				struct timeval tv_out;
				tv_out.tv_sec  = 60; //60s will timeout  //recv timeout
				tv_out.tv_usec = 0;
				//填充这个结构后，我们就可以以如下的方式调用这个函数：				
				setsockopt(connectfd, SOL_SOCKET, SO_RCVTIMEO, &tv_out, sizeof(tv_out));//(具体参数可以man一下，或查看MSDN)

				lt_info("Yougot a connection from server's ip is %s, prot is %d\n",inet_ntoa(server.sin_addr),htons(server.sin_port));  
				//casx = CASX_STEP_00 ;
				//break;
			}
			casx = CASX_STEP_00 ;
			break;
		case CASX_STEP_00://creat thread
			{
				s32 res;
				pthread_t thread_client_app;
				void *thread_result;

				lt_debug("will creat thread thread_client_app and connectfd=%d",connectfd);
				thread_arg->connectfd = connectfd;
				thread_arg->hz_connectfd = connectfd;
				thread_arg->flag = 0; //server 
				res = pthread_create(&thread_client_app,NULL,thread_socket_module_entry_point,thread_arg);
				if( res != 0 )
				{
					lt_error("Thread creation failed!\n");
					casx = CASX_FREE_MEM ;
					break;
					//exit(EXIT_FAILURE);
				}

				lt_debug("waiting pthread thread_client_app finish");

				res = pthread_join(thread_client_app, &thread_result);
				if (res != 0)
				{
					lt_error("Thread join failed!\n");
					exit(EXIT_FAILURE);
				}
				lt_info("thread_client_app had finished...\n");
				if ( thread_arg->disconnect)
				{
					casx = CASX_FREE_MEM ;
					break;

				}else
				{
					close(connectfd);
					//close(listenfd);
					lt_info("waiting connect new tcp socket...\n");
					//state_tcp_client_online = FAIL ;
					sleep(1);
					casx = CASX_INIT ;
					break;
				}

			}
			casx = CASX_FREE_MEM ;
			break;

		case CASX_FREE_MEM:
			{
			}
			casx = CASX_CLOSE_FILE ;
			break;
		case CASX_CLOSE_FILE:
			{
				close(connectfd);
				//close(listenfd);
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
	return NULL;
}


s32 socket_write(socket_creat_arg_t *sock_arg,d8 * buf,s32 buflen,hz_sock_flag_t flag)
{
	s32 nleft = buflen;
	s32 nwritten = 0;
	s32 res = SUCCESS;
	s32 chance = 0 ;
	const s8 *ptr;


	ptr = (const s8 *) buf;
	while( nleft > 0 && chance <= 1 )
	{
		//nwritten = send(fd,ptr,nleft,0);
		//lt_debug("run send");
		nwritten = send(sock_arg->connectfd,ptr,nleft,MSG_NOSIGNAL);//need add commentary
		if ( nwritten <= 0 )
		{
			if( errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK )
			{
				//Give Ethernet a chance
				nwritten = 0;
				lt_error("send FAIL \n");
				lt_sleep(1);
				chance ++ ;
			}else
			{
				res = FAIL ;
				break;
			}
		}
		nleft -= nwritten;
		ptr   += nwritten;
	}
	return res ;
}
/**
socket_read()   //recv设置了接收超时 如果没有数据接收到则recv会阻塞等待数据   recv并不是立即返回当没有数据的时候
@return ret <0  :error   ret==0:recv time out    ret>0:normal


read 原则：

        数据在不超过指定的长度的时候有多少读多少，没有数据则会一直等待。所以一般情况下：我们读取数据都需要采用循环读的方式读取数据，因为一次read 完毕不能保证读到我们需要长度的数据，read 完一次需要判断读到的数据长度再决定是否还需要再次读取。

 

recv 原则：
        recv 中有一个MSG_WAITALL 的参数:
                recv(sockfd, buff, buff_size, MSG_WAITALL),
        正常情况下recv 是会等待直到读取到buff_size 长度的数据，但是这里的WAITALL 也只是尽量读全，在有中断的情况下recv 还是可能会被打断，造成没有读完指定的buff_size的长度。所以即使是采用recv + WAITALL 参数还是要考虑是否需要循环读取的问题，在实验中对于多数情况下recv (使用了MSG_WAITALL)还是可以读完buff_size，
        所以相应的性能会比直接read 进行循环读要好一些。

2、read 与 recv函数调用
        read(sockfd, buff, buff_size);       
        write(sockfd, buff, buff_size);
        recv(sockfd, buff, buff_size,MSG_WAITALL); //阻塞模式接收        
        send(scokfd, buff, buff_size,MSG_WAITALL); //阻塞模式发送
        recv(sockfd, buff, buff_size,MSG_DONTWAIT); //非阻塞模式接收        
        send(scokfd, buff, buff_size,MSG_DONTWAIT); //非阻塞模式发送
        recv(sockfd, buff, buff_size,0);        
        send(scokfd, buff, buff_size,0);
3、socket编程经验
        1）尽量使用recv(,,MSG_WAITALL),read必须配合while使用，否则数据量大(240*384)时数据读不完
        2）编程时写入的数据必须尽快读出，否则后面的数据将无法继续写入
        3）最佳搭配如下：
                nbytes = recv(sockfd, buff, buff_size,MSG_WAITALL);
                nbytes = send(scokfd, buff, buff_size,MSG_WAITALL);



*/
#if 1

s32 socket_read(socket_creat_arg_t *sock_arg,d8 * buf,s32 buflen,hz_sock_flag_t flag)
{
	s32 nleft = 0 ;
	s32 nread = 0;
	//s32 res = SUCCESS;
	//s32 chance = 0 ;
	//const s8 *ptr;
	s8 *ptr;

	ptr = (s8 *) buf;
	nleft = buflen ;
	while( nleft > 0 )//&& chance <= 1 )
	{
		//nwritten = send(fd,ptr,nleft,0);
		//lt_debug("run recv fd=%d",sock_arg->connectfd);
		//数据在不超过指定的长度的时候有多少读多少，没有数据则会一直等待
		nread = recv(sock_arg->connectfd,ptr,nleft,0);  //MSG_WAITALL  will block    
		// recv(fd,ptr,nleft,0);  is equal to read(fd,ptr,nleft);
		// recv arg3  flag set 0   is  identity  with read
		//nread = read(fd,ptr,nleft);
		if ( nread < 0 )
		{
			if( errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK ) //|| errno == EAGAIN || errno == EWOULDBLOCK )
			{
				lt_error("recv nread=%d \n",nread);
				lt_error("recv errno=%d \n",errno);
				lt_error("recv error %s\n",strerror(errno));
				//Give Ethernet a chance
				nread = 0;  // and call read() again
				lt_error("recv again,may be time out");
				//lt_sleep(1);
				//chance ++ ;

			}else
			{
				lt_error("recv nread=%d \n",nread);
				lt_error("recv errno=%d \n",errno);
				lt_error("recv error %s\n",strerror(errno));
				return FAIL ;
			}
		}else if (nread == 0 )
		{
			lt_error("recv nread=%d \n",nread);
			lt_error("recv errno=%d \n",errno);
			lt_error("recv error %s\n",strerror(errno));
			lt_error("may be connect error");
			return FAIL ;
		}
		nleft -= nread;
		ptr   += nread;
		if ( flag == HZ_SOCK_FLAG_WAITALL )
		{

		}else
		{
			break;  //若没有break 则会一直等到接收buflen 字节才会退出，若有则recv等到有数据接收到才会返回，
		}
		
		//res = buflen - nleft  ;
	}

	//return res ;
	return buflen - nleft;
}
#else
s32 socket_read(s32 fd,d8 * buf,s32 buflen,s32 flag)
{
	s32 nleft = 0 ;
	s32 nread = 0;
	//s32 res = SUCCESS;
	//s32 chance = 0 ;
	//const s8 *ptr;
	s8 *ptr;

	ptr = (s8 *) buf;
	nleft = buflen ;
	while( nleft > 0 )//&& chance <= 1 )
	{
		//nwritten = send(fd,ptr,nleft,0);
		//lt_debug("run recv");
		nread = recv(fd,ptr,nleft,0);  //MSG_WAITALL  will block    
		// recv(fd,ptr,nleft,0);  is equal to read(fd,ptr,nleft);
		// recv arg3  flag set 0   is  identity  with read
		//nread = read(fd,ptr,nleft);
		if ( nread <= 0 )
		{
			if( errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK ) //|| errno == EAGAIN || errno == EWOULDBLOCK )
			{
				//Give Ethernet a chance
				nread = 0;  // and call read() again
				lt_error("recv again,may be time out");
				//lt_sleep(1);
				//chance ++ ;
				lt_error("recv nread=%d \n",nread);
				lt_error("recv errno=%d \n",errno);
				lt_error("recv error %s\n",strerror(errno));
				//return FAIL;
				
			}else
			{
				//res = FAIL ;
				//break;
				
				lt_error("recv nread=%d \n",nread);
				lt_error("recv errno=%d \n",errno);
				lt_error("recv error %s\n",strerror(errno));
				nread = 0;
				return FAIL ;
			}
		}
		nleft -= nread;
		ptr   += nread;
		break;  //若没有break 则会一直等到接收buflen 字节才会退出
		//res = buflen - nleft  ;
	}

	//return res ;
	return buflen - nleft;
}
#endif

















s32 socket_msg_util_send_handle_(socket_creat_arg_t *sock_arg,socket_msg_type_t msg_type,socket_msg_ack_flag_t ack_flag ,s32 msg_id,d8 * buf,s32 buflen)
{
//add mutex
	socket_msg_head_t* msg_head=NULL;
	socket_msg_tail_t* msg_tail=NULL;
	d8 *socket_buf=NULL;
	//s32 tmp = 0;
	s32 malloc_len=0;
	s32 ret=SUCCESS,res=0;
	s32 i = 0;
	
	do
	{
		if (  buflen > SOCKET_MSG_DATA_LEN_MAX  )   
		{
			lt_debug("buflen=%d  max=%d",buflen, SOCKET_MSG_DATA_LEN_MAX );
			ret = FAIL;
			lt_error("buflen too large");
			break;
		}

		if ( buf == NULL || buflen== 0 ) 
		{
			buf = NULL ; 
			buflen = 0 ;
		}
		malloc_len = SOCKET_MSG_TAIL_LEN + SOCKET_MSG_HEAD_LEN + buflen + 8 ;//8 bytes reserves
		socket_buf = malloc( malloc_len ) ;
		if ( socket_buf == NULL )
		{
			ret = FAIL;
			lt_error("error malloc failed");
			break;
		}

		memset(socket_buf,0,malloc_len);
		msg_head = (socket_msg_head_t*)  socket_buf;
		msg_tail = (socket_msg_tail_t*)(  (d8 *)socket_buf + SOCKET_MSG_HEAD_LEN + buflen ) ;
		msg_head->head = SOCKET_MSG_FLAG_HEAD ; 
		msg_head->msg_len  = SOCKET_MSG_TAIL_LEN + SOCKET_MSG_HEAD_LEN + buflen ;
		msg_head->msg_type = msg_type ; 
		msg_head->ack_flag = ack_flag ; 
		msg_head->msg_id = msg_id ; 

		for(i=0;i < buflen;i++)
		{
			socket_buf[ SOCKET_MSG_HEAD_LEN  + i ] = buf[i] ;
		}

		msg_tail->tail = SOCKET_MSG_FLAG_TAIL ; 
		msg_tail->checkcode = 0 ; 	

		//lt_debug("enter %s  socket_write",__FUNCTION__);
		res = socket_write(sock_arg,socket_buf,msg_head->msg_len,0);
		if ( res != SUCCESS )
		{
			//网络异常
			lt_error("socket send FAIL \n");
			ret = FAIL ;
			break;
		}	
	}while(0);


	free(socket_buf);



	//lt_debug("exit %s  socket_write",__FUNCTION__);
	return ret ;
}


s32 socket_msg_util_send_handle(socket_creat_arg_t *sock_arg,socket_msg_user_t *msg_arg)
{
//add mutex
	socket_msg_head_t* msg_head=NULL;
	socket_msg_tail_t* msg_tail=NULL;
	d8 *socket_buf=NULL;
	//s32 tmp = 0;
	s32 malloc_len=0;
	s32 ret=SUCCESS,res=0;
	s32 i = 0;


	if ( msg_arg ==NULL )
	{
		return FAIL;
	}

	socket_msg_type_t   	msg_type	=msg_arg->msg_type;
	socket_msg_ack_flag_t 	ack_flag	=msg_arg->ack_flag;
	s32 			msg_id		=msg_arg->msg_id;
	d8 * 			buf		=msg_arg->msg_p;
	s32 			buflen		=msg_arg->buflen;
	do
	{
		if (  buflen > SOCKET_MSG_DATA_LEN_MAX  )   
		{
			lt_debug("buflen=%d  max=%d",buflen, SOCKET_MSG_DATA_LEN_MAX );
			ret = FAIL;
			lt_error("buflen too large");
			break;
		}

		if ( buf == NULL || buflen== 0 ) 
		{
			buf = NULL ; 
			buflen = 0 ;
		}
		malloc_len = SOCKET_MSG_TAIL_LEN + SOCKET_MSG_HEAD_LEN + buflen + 8 ;//8 bytes reserves
		socket_buf = malloc( malloc_len ) ;
		if ( socket_buf == NULL )
		{
			ret = FAIL;
			lt_error("error malloc failed");
			break;
		}

		memset(socket_buf,0,malloc_len);
		msg_head = (socket_msg_head_t*)  socket_buf;
		msg_tail = (socket_msg_tail_t*)(  (d8 *)socket_buf + SOCKET_MSG_HEAD_LEN + buflen ) ;
		msg_head->head = SOCKET_MSG_FLAG_HEAD ; 
		msg_head->msg_len  = SOCKET_MSG_TAIL_LEN + SOCKET_MSG_HEAD_LEN + buflen ;
		msg_head->msg_type = msg_type ; 
		msg_head->ack_flag = ack_flag ; 
		msg_head->msg_id = msg_id ; 

		for(i=0;i < buflen;i++)
		{
			socket_buf[ SOCKET_MSG_HEAD_LEN  + i ] = buf[i] ;
		}

		msg_tail->tail = SOCKET_MSG_FLAG_TAIL ; 
		msg_tail->checkcode = 0 ; 	

		//lt_debug("enter %s  socket_write",__FUNCTION__);
		res = socket_write(sock_arg,socket_buf,msg_head->msg_len,0);
		if ( res != SUCCESS )
		{
			//网络异常
			lt_error("socket send FAIL \n");
			ret = FAIL ;
			break;
		}	
	}while(0);


	free(socket_buf);



	//lt_debug("exit %s  socket_write",__FUNCTION__);
	return ret ;
}

static d8 socket_msg_util_recv_buf[SOCKET_MSG_LEN_MAX];
s32 socket_msg_util_recv_handle(socket_creat_arg_t *sock_arg,socket_msg_user_t *msg_arg)
{

	socket_msg_head_t  recv_msg_head;
	socket_msg_tail_t *recv_msg_tail;
	s32 tmp_len;
	d8 *malloc_buf=NULL;
	s32 ret=0;
	
	memset(&recv_msg_head,0,sizeof(recv_msg_head));
	malloc_buf = socket_msg_util_recv_buf;//add globle array

	if ( msg_arg ==NULL )
	{
		return FAIL;
	}
	
	s32 casx=CASX_INIT;
	while(casx)
	{
		switch(casx)
		{
		case CASX_INIT:
			{
				s32 recv_length;
				//lt_debug("%s CASX_INIT",__FUNCTION__);
				recv_length = socket_read(sock_arg,(d8*)&recv_msg_head,sizeof(recv_msg_head),HZ_SOCK_FLAG_WAITALL);				
				if ( recv_length == sizeof(recv_msg_head) )
				{
					if ( recv_msg_head.head != SOCKET_MSG_FLAG_HEAD )
					{
						lt_error("head flag != %x",SOCKET_MSG_FLAG_HEAD);
						casx = CASX_FREE_MEM ;
						ret = FAIL;break;
					}
					if (  recv_msg_head.msg_len > SOCKET_MSG_LEN_MAX ||
					      recv_msg_head.msg_len < ( SOCKET_MSG_HEAD_LEN + SOCKET_MSG_TAIL_LEN  )	)				
					{
						lt_error("msg_len error msg_len=%x",recv_msg_head.msg_len);
						casx = CASX_FREE_MEM ;
						ret = FAIL;break;
					}

				}else
				{
					lt_error("recv_length = %x",recv_length);
					//lt_sleep(1);
					casx = CASX_FREE_MEM ;
					ret = FAIL;break;
				}
				tmp_len = recv_msg_head.msg_len - SOCKET_MSG_HEAD_LEN ;
				//if (malloc_buf != NULL)
				//{
				//	free(malloc_buf);
				//	malloc_buf=NULL;
				//}
				//malloc_buf = malloc( tmp_len + 8 ) ;//8 BYTES reserve
				if ( malloc_buf == NULL )
				{
					//ret = FAIL;
					lt_error("error malloc failed");
					casx = CASX_FREE_MEM ;
					ret = FAIL;break;
				}
				
				recv_length = socket_read(sock_arg,malloc_buf,tmp_len ,HZ_SOCK_FLAG_WAITALL);
				if ( recv_length == tmp_len ) 
				{
					recv_msg_tail =(socket_msg_tail_t *)( malloc_buf +  tmp_len - SOCKET_MSG_TAIL_LEN );
					if ( recv_msg_tail->tail  != SOCKET_MSG_FLAG_TAIL )					
					{
						lt_error("tail flag != %x",SOCKET_MSG_FLAG_TAIL);
						casx = CASX_FREE_MEM ;
						ret = FAIL;break;
					}
					//CHECKCODE
				}else
				{
					lt_error("recv_length = %x",recv_length);
					//lt_sleep(1);
					casx = CASX_FREE_MEM ;
					ret = FAIL;break;
				}
				casx = CASX_FREE_MEM ;
				msg_arg->msg_type=recv_msg_head.msg_type;
				msg_arg->ack_flag=recv_msg_head.ack_flag;
				msg_arg->msg_id=recv_msg_head.msg_id;
				msg_arg->msg_p=malloc_buf;
				msg_arg->buflen=tmp_len - SOCKET_MSG_TAIL_LEN;
				ret = SUCCESS;break;
			}
			casx = CASX_INIT ;
			break;
		case CASX_FREE_MEM:
			{
				//lt_debug("%s CASX_FREE_MEM",__FUNCTION__);
				//free(malloc_buf);
			}
			casx = CASX_CLOSE_FILE ;
			break;
		case CASX_CLOSE_FILE:
			{
				//lt_debug("%s CASX_CLOSE_FILE",__FUNCTION__);
				//close(recv_hd);  
				//close(recv_hd);  
				//lt_debug("%s thread will done\n",__FUNCTION__);
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
				lt_error("%s default",__FUNCTION__);
				break;
			}
		}
	}
	return ret;

}


#if 0
/*

*/
s32 socket_msg_write(s32 fd,socket_msg_t *socket_msg,s32 flag)
{
	s8 *buffer=NULL;
	s32 ret = SUCCESS ;
	s32 res = 0;
	s32 tmp = 0;
	socket_msg_t *socket_msg_p;
	s8 * buffer_tmp=NULL;
	do
	{
		if ( socket_msg == NULL )
		{
			ret = FAIL;
			break;
		}
		if ( socket_msg -> head  != 0x12345678 || socket_msg -> tail  == 0x87654321)
		{
			ret = FAIL;
			break;
		}
		if ( socket_msg -> msg_len >= SOCKET_MSG_LEN_MAX )
		{
			ret = FAIL;
			break;
		}
		buffer = malloc( socket_msg -> msg_len + sizeof(socket_msg->head)*3 ); 
		if ( buffer ==NULL )
		{
			ret = FAIL;
			break;
		}
		buffer_tmp = buffer;
		hz_memset(buffer, 0, socket_msg -> msg_len + sizeof(socket_msg->head)*3 )
		hz_memcpy(buffer,socket_msg,sizeof( *socket_msg)  );

		buffer_tmp = buffer + hz_struct_offset(socket_msg_t, msg_p ) +4 ;
		tmp = socket_msg -> msg_len - hz_struct_offset(socket_msg_t, msg_p );
		hz_memcpy( buffer_tmp  , socket_msg->msg_p , tmp);

		buffer_tmp = buffer_tmp + tmp ;
		hz_memcpy( buffer_tmp , socket_msg->checkcode  ,  sizeof (socket_msg->checkcode);
		buffer_tmp = buffer_tmp +  sizeof (socket_msg->checkcode) ;
		hz_memcpy( buffer_tmp  , socket_msg->tail  , sizeof (socket_msg->tail) ;
		socket_write(buffer,socket_msg-> msg_len + sizeof(socket_msg->head)*2,flag);
	}while(0);
	//socket_write

	free(buffer);
	return ret;
}
s32 socket_msg_read(s32 fd,socket_msg_t *socket_msg,s32 flag)
{
	s8 *buffer=NULL;
	s32 ret = SUCCESS ;
	s32 res = 0;
	s32 tmp = 0;
	socket_msg_t *socket_msg_p;
	s8 * buffer_tmp=NULL;
	s32 tmp_len=0;
	socket_msg_t tmp_socket_msg;
	do
	{
		if ( socket_msg == NULL )
		{
			ret = FAIL;
			break;
		}

		if ( socket_msg -> head  != 0x12345678 || socket_msg -> tail  == 0x87654321)
		{
			ret = FAIL;
			break;
		}
		if ( socket_msg -> msg_len >= SOCKET_MSG_LEN_MAX )
		{
			ret = FAIL;
			break;
		}
		tmp_len = hz_struct_offset(socket_msg_t,msg_len ) + sizeof(socket_msg->msg_len) ;
		tmp = socket_read(fd,(s8 *)&tmp_socket_msg,tmp_len  ,flag);
		if ( tmp != tmp_len )
		{
			ret = FAIL;
			break;
		}
		
		if ( tmp_socket_msg.head != 0x12345678 )
		{
			ret = FAIL;
			break;
		}
		
		if ( tmp_socket_msg.msg_len <=0 || tmp_socket_msg.msg_len >= SOCKET_MSG_LEN_MAX  )
		{
			ret = FAIL;
			break;
		}

		buffer = malloc( socket_msg -> msg_len + sizeof(socket_msg->head)*3 ); 
		if ( buffer ==NULL )
		{
			ret = FAIL;
			break;
		}
		hz_memset(buffer, 0, socket_msg -> msg_len + sizeof(socket_msg->head)*3 )
		hz_memcpy(buffer,socket_msg,sizeof( *socket_msg)  );

		buffer_tmp = buffer + hz_struct_offset(socket_msg_t, msg_p ) +4 ;
		tmp = socket_msg -> msg_len - hz_struct_offset(socket_msg_t, msg_p );
		hz_memcpy( buffer_tmp  , socket_msg->msg_p , tmp);

		buffer_tmp = buffer_tmp + tmp ;
		hz_memcpy( buffer_tmp , socket_msg->checkcode  ,  sizeof (socket_msg->checkcode);
		buffer_tmp = buffer_tmp +  sizeof (socket_msg->checkcode) ;
		hz_memcpy( buffer_tmp  , socket_msg->tail  , sizeof (socket_msg->tail) ;
		socket_write(buffer,socket_msg-> msg_len + sizeof(socket_msg->head)*2,flag);
	}while(0);
	//socket_write
	return ret;
}




void *thread_recv_handle_entry_point(void *arg)
{
	s32 connectfd=*(s32 *)arg;

	min_msg_t recv_cmd;


//#define MAX_BUFFER_LENGTH sizeof(min_msg_t)
	//s8 buffer[MAX_BUFFER_LENGTH];

	lt_debug("thread %s is starting. Argument was %d\n",__FUNCTION__, connectfd);

	memset(&recv_cmd,0,sizeof(recv_cmd));
	s32 casx=CASX_INIT;
	while(casx)
	{
		switch(casx)
		{
		case CASX_INIT:
			{
				s32 recv_length;
				//lt_debug("%s CASX_INIT",__FUNCTION__);
				recv_length = socket_read(connectfd,(s8 *)&recv_cmd,sizeof(recv_cmd),0);
				if ( recv_length == sizeof(recv_cmd) )
				{
					if ( recv_cmd.head != MSG_HEAD_FLAG )
					{
						continue ;
					}
					if ( recv_cmd.data_length  != 4 )
					{
						//continue ;
					}
					if ( recv_cmd.ack_flag == ACK_FLAG_SEND && recv_cmd.pkt_type == MSG_T_HEART_BEAT)
					{
						casx = CASX_STEP_00 ; //ack heart beat
						break;
					}else if ( recv_cmd.ack_flag == ACK_FLAG_SEND && recv_cmd.pkt_type == MSG_T_REBOOT)
					{
						casx = CASX_STEP_01 ; //ack reboot
						break;
					}else if ( recv_cmd.ack_flag == ACK_FLAG_SEND && recv_cmd.pkt_type == MSG_T_QUERY_SYNC_INFO)
					{
						casx = CASX_STEP_02 ; //ack query sync info
						break;
					}else if ( recv_cmd.ack_flag == ACK_FLAG_SEND && recv_cmd.pkt_type == MSG_T_SEARCH_SYNC_INFO_AGAIN)
					{
						casx = CASX_STEP_03 ; //ack search sync info again
						break;
					}else if ( recv_cmd.ack_flag == ACK_FLAG_RECV_SUCCESS && recv_cmd.pkt_type == MSG_T_HEART_BEAT)
					{
						casx = CASX_STEP_04 ; //recv ack heart beat
						break;
					}else if ( recv_cmd.ack_flag == ACK_FLAG_SEND )
					{
						casx = CASX_STEP_05 ; //ack unsupport cmd
						break;
					}
				}else
				{
					casx = CASX_FREE_MEM ;
					break;
				}
			}
			casx = CASX_STEP_00 ;
			break;
		case CASX_STEP_00://
			{
				//lt_debug("%s CASX_STEP_00",__FUNCTION__);
				if ( msg_ack_heart_beat_handle(connectfd) != SUCCESS )
				{
					casx = CASX_FREE_MEM ;
					break;
				}
			}
			casx = CASX_INIT ;
			break;
		case CASX_STEP_01:
			{
				lt_debug("%s CASX_STEP_01",__FUNCTION__);
				if ( msg_ack_reboot_handle(connectfd) != SUCCESS )
				{
					casx = CASX_FREE_MEM ;
					break;
				}
			}
			casx = CASX_INIT ;
			break;
		case CASX_STEP_02:
			{
				lt_debug("%s CASX_STEP_02",__FUNCTION__);
				if ( msg_ack_query_sync_info_handle(connectfd) != SUCCESS )
				{
					casx = CASX_FREE_MEM ;
					break;
				}
			}
			casx = CASX_INIT ;
			break;
		case CASX_STEP_03:
			{
				lt_debug("%s CASX_STEP_03",__FUNCTION__);
				if ( msg_ack_search_sync_info_again_handle(connectfd) != SUCCESS )
				{
					casx = CASX_FREE_MEM ;
					break;
				}
			}
			casx = CASX_INIT ;
			break;
		case CASX_STEP_04:
			{
				//lt_debug("%s CASX_STEP_04",__FUNCTION__);
				msg_ack_flag_heart_beat = MSG_ACK_FLAG ;
				//lt_debug();
			}
			casx = CASX_INIT ;
			break;
		case CASX_STEP_05:
			{
				lt_debug("%s CASX_STEP_05",__FUNCTION__);
				if ( msg_ack_unsupport_handle(connectfd,recv_cmd.pkt_type) != SUCCESS )
				{
					casx = CASX_FREE_MEM ;
					break;
				}
			}
			casx = CASX_INIT ;
			break;
		case CASX_FREE_MEM:
			{
				lt_debug("%s CASX_FREE_MEM",__FUNCTION__);
			}
			casx = CASX_CLOSE_FILE ;
			break;
		case CASX_CLOSE_FILE:
			{
				lt_debug("%s CASX_CLOSE_FILE",__FUNCTION__);
				//close(recv_hd);  
				//close(recv_hd);  
				lt_debug("%s thread will done\n",__FUNCTION__);
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
}

void *thread_heart_beat_enry_point(void *arg)
{
	s32  res = 0 ;
	s32 tmp_res = 0;

	u32 chance = 0 ;
	s32 connectfd=*(s32 *)arg;

	lt_debug("thread %s is starting. Argument was %d\n",__FUNCTION__, connectfd);
	//send(connectfd,"Welcometo my server.\n",22,0);
	min_msg_t msg_heart_beat;
	memset(  &msg_heart_beat,0,sizeof(msg_heart_beat)  );
	msg_heart_beat.head=MSG_HEAD_FLAG;
	msg_heart_beat.pkt_type=MSG_T_HEART_BEAT;
	msg_heart_beat.data_length=4;
	msg_heart_beat.ack_flag=0;



	while(1)
	{
		tmp_res = socket_write(connectfd,(s8 *)&msg_heart_beat,sizeof(msg_heart_beat),0);
		if ( tmp_res == FAIL )
		{
			//网络异常
			//chance ++ ;
			lt_error("socket send FAIL \n");
			break;
		}
		lt_sleep(1);
		//lt_debug("socket send heart beat");
		if ( msg_ack_flag_heart_beat == MSG_ACK_FLAG )
		{
			//lt_debug("recv heart beat success\n");
			chance = 0;
			msg_ack_flag_heart_beat = MSG_ACK_FLAG_CLEAR ;
		}else
		{
			chance ++ ;
			lt_error("heart beat ack timeout");
		}

		if ( chance >= 3 )
		{
			chance = 0 ;
			//客户端掉线，可能网络断开
			break;
		}
	}

}
void *thread_socket_s_module_entry_point(void *arg)
{
	s32  res = 0 ;
	//lt_debug("thread %s is starting. Argument was %s\n", (char *)arg);
	s32 connectfd=*(s32 *)arg;
	lt_debug("thread %s is starting. Argument  was connectfd=%p\n",__FUNCTION__, connectfd);
	//send(connectfd,"Welcometo my server.\n",22,0);

	pthread_t thread_heart_beat;
	pthread_t thread_recv_msg;
	void *thread_result;

	//在arm上如果只注释掉pthread_create 而不注释 pthread_join 则会报 Segmentation fault
	res = pthread_create(&thread_heart_beat,NULL, thread_heart_beat_enry_point ,&connectfd);
	if( res != 0 )
	{
		lt_error("Thread creation failed!\n");
	}


	res = pthread_create(&thread_recv_msg,NULL, thread_recv_handle_entry_point ,&connectfd);
	if( res != 0 )
	{
		lt_error("Thread creation failed!\n");
	}

	lt_debug("waiting thead heart beat stop");
	//lt_sleep(1);
	res = pthread_join(thread_heart_beat, &thread_result);
	if (res != 0)
	{
		lt_error("Thread join failed!/n");
	}
	lt_debug("thead heart beat had stop");
	lt_debug("waiting thead recv msg stop");
	//lt_sleep(1);
	res = pthread_join(thread_recv_msg, &thread_result);
	if (res != 0)
	{
		lt_error("Thread join failed!/n");
	}
	lt_debug("thead recv msg had stop");
}
#endif
