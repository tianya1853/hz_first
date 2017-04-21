#!/bin/bash

#/*******************************************************************
#Copyright (C) hz
#Version:      v0.0.1
#FileInfo------------------------------------------------------------
#Filename:     
#Author:       hz
#Date:         20161221
#Version:      v0.0.1
#Description:  
#ChangeLog------------------------------------------------------------
#Author:
#Date:
#Version:
#Description:
#*******************************************************************/

#naming rule
# 大类_小类_对象_动词短语
# class_object_action

#usage
#在查看命令帮助时，会出现[],<>,|等符号，它们的含义如下：
#[]       表示是可选的;
#<>       表示可变选项，一般是多选一，而且必须是要选其一。
#x|y|z    多选一，如果加上[]，可不选。
#-abc     多选，如果加上[]，可不选。

#script architecture:
#comment format:  
	#1.
	#/****************************start xxx ****************************
	#*****************************end   xxx ***************************/
	#2.
	#//***************************import library ***********************
	#//***************************define globle argument ***********************
	#//***************************define function ***********************
	
	
#import library
#define globle argument
#	FILE_LOG
#	FILE_LOCK
#define function
#	main
#
#
#
#//***************************import library ***********************
#source function.sh



#/***************************define globle argument ***********************/

#common define 

VERSION_SELF="20161221_v0.0.1"
DIRE_SELF="."
#NAME_SELF="module.sh"
NAME_SELF=`echo $0 | awk -F'/' '{print $NF}' `
DIRE_LOG_SELF="."
#NAME_PLATFORM='X86'
platform_check()
{
	#which ls
	local tmp=`ls /bin/ls -l | grep busybox | wc -l`
	if test $tmp -eq 0 ;then
		NAME_PLATFORM=X86
	else
		NAME_PLATFORM=ARM
	fi
	return $SUCCESS
}
#warning 对于只运行一次的变量声明后不受其他变量改变而改变，过程语言
self_init()
{
	platform_check
	if [ $NAME_PLATFORM == "ARM" ];then
		DIRE_LOG_SELF=/mnt/log/$NAME_SELF
		DIRE_SELF=/OAM/bin/app/manage
	else
		:
	fi
	#echo_info "platform=$NAME_PLATFORM"
	#echo_info "log=$NAME_PLATFORM"
	mkdir -p $DIRE_LOG_SELF	
	#echo $DIRE_LOG_SELF	
	#echo "$FILE_LOG_SELF"
}


self_init


FILE_SELF="$DIRE_SELF/$NAME_SELF"
FILE_LOCK_SELF="$DIRE_SELF/$NAME_SELF.lock"
FILE_LOG_SELF="$DIRE_LOG_SELF/$NAME_SELF.log"
COUNT_LOG_SELF=10
SIZE_LOG_SELF=102400  #100K
#SIZE_LOG_SELF=4096  #100K


SUCCESS=0
FAILED=1

value_exit=$SUCCESS


#communication define 
FILE_INPUT=$FILE_SELF.in
FILE_OUTPUT=$FILE_SELF.out
FILE_DEBUG=$FILE_SELF.debug
FILE_PROCESS=$FILE_SELF.process
SOCKET_TCP_S_PORT_0=5126  #bash 

#app define 
#backup_log  USE
COUNT_BACKUP_LOG=20

FILE_REBOOT_REASON=$DIRE_LOG_SELF/reboot_reason.txt
FILE_REBOOT_REASON_HISTORY=$DIRE_LOG_SELF/reboot_reason_history.txt


GPIO_DOG=1d
GPIO_DOG_FLAG="start"  # start or stop
FILE_LOG_DOG=/OAM/log/dog.log
SIZE_LOG_DOG=102400 #100K


FILE_PROCESS_DOG=$FILE_PROCESS.dog
echo "$GPIO_DOG_FLAG" > $FILE_PROCESS_DOG  #init file

FILE_LOG_FS_MONITOR=/OAM/log/fs_monitor.log




##############################define function
#/******************library function




date_get()
{
	$(date "+%Y%m%d%H%M%S").$tmp_uptime
}

echo_debug()
{
	local tmp="$*"
	local tmp_uptime=`cat /proc/uptime | awk '{print $1}'`	
	echo "[$(date "+%Y%m%d%H%M%S").$tmp_uptime][$FILE_SELF][line_$BASH_LINENO]<debug:$tmp"  >> $FILE_LOG_SELF	
}
echo_info()
{
	local tmp="$@"
	local tmp_uptime=`cat /proc/uptime | awk '{print $1}'`	
	echo "[$(date "+%Y%m%d%H%M%S").$tmp_uptime][$FILE_SELF][line_$BASH_LINENO]<info:$tmp"  >> $FILE_LOG_SELF	
}

echo_warn()
{
	local tmp="$@"
	local tmp_uptime=`cat /proc/uptime | awk '{print $1}'`	
	echo "[$(date "+%Y%m%d%H%M%S").$tmp_uptime][$FILE_SELF][line_$BASH_LINENO]<warn:$tmp"  >> $FILE_LOG_SELF	
}

echo_error()
{
	local tmp="$@"
	local tmp_uptime=`cat /proc/uptime | awk '{print $1}'`	
	echo "[$(date "+%Y%m%d%H%M%S").$tmp_uptime][$FILE_SELF][line_$BASH_LINENO]<error:$tmp" >> $FILE_LOG_SELF
}


echo_debug_nolog()
{
	local tmp="$*"
	local tmp_uptime=`cat /proc/uptime | awk '{print $1}'`	
	echo "[$(date "+%Y%m%d%H%M%S").$tmp_uptime][$FILE_SELF][line_$BASH_LINENO]<debug:$tmp"	
}
echo_info_nolog()
{
	local tmp="$@"
	local tmp_uptime=`cat /proc/uptime | awk '{print $1}'`	
	echo "[$(date "+%Y%m%d%H%M%S").$tmp_uptime][$FILE_SELF][line_$BASH_LINENO]<info:$tmp"	
}

echo_warn_nolog()
{
	local tmp="$@"
	local tmp_uptime=`cat /proc/uptime | awk '{print $1}'`	
	echo "[$(date "+%Y%m%d%H%M%S").$tmp_uptime][$FILE_SELF][line_$BASH_LINENO]<warn:$tmp"	
}

echo_error_nolog()
{
	local tmp="$@"
	local tmp_uptime=`cat /proc/uptime | awk '{print $1}'`	
	echo "[$(date "+%Y%m%d%H%M%S").$tmp_uptime][$FILE_SELF][line_$BASH_LINENO]<error:$tmp"	
}


funciont_moduel() 
{
	local i=0
	local ret=$SUCCESS
	local res=$SUCCESS
	local tmp="x"
	
	#echo $#
	#bash bug:"if [ $# == 0 ] " will run but $# is 1 actually,must add something befor if condition
	#bug general condition
	#function is run in background with argument,and "if $#" or other judge condition was run first
	echo "" > /dev/null
	echo "" > /dev/null
	
	if test $# -eq 0 ;then
		echo_info "function descriptor"
		echo_info "Usage: $FUNCNAME <a|b>  [c|d] [-ef]"
		echo_info "List directory contents"
        	echo_info "a    argument a"
		echo_info "-e   argument e"
		return $FAILED;
	fi
	echo_info "start $FUNCNAME ********************************************"
	echo_info ""
	if test $1 != 'a' ;then
		:
	fi

	while true
	do
		ret=$SUCCESS
		break
	done

# ;; 相当于 c语言中swich的break
# ;; 只能在分支的最后，不能放在if语句里面因此，在if 中需要跳出本次循环的则使用casx=xxxx;continue 1;代替 ;;
#break/continue n  跳出/继续 第 n 层循环
#即便 if里面已经有了continue 但是分支的最后 ;;不能省略

	local casx=CASX_INIT

	while [ $casx != CASX_EXIT ]
	do
	case $casx in 
		CASX_INIT )
			echo_info "------------CASX_INIT--------------"
			if false;then
				casx=CASX_STEP_01;
				continue 1;
			else
				casx=CASX_STEP_02;
				continue 1;
			fi
			casx=CASX_STEP_00;;
		CASX_STEP_00 )
			echo_info "------------CASX_STEP_00-----------"		
			casx=CASX_STEP_01;;
		CASX_STEP_01 )		
			echo_info "------------CASX_STEP_01-----------"
			casx=CASX_STEP_02;;
		CASX_STEP_02 )
			echo_info "------------CASX_STEP_02-----------"		
			casx=CASX_STEP_03;;
		CASX_STEP_03 )	
			echo_info "------------CASX_STEP_03-----------"	
			casx=CASX_CLOSE_FILE;;
		CASX_LOOP_00 )
			echo_info "------------CASX_LOOP_00-----------"	
			sleep 1;
			;;
		CASX_LOOP_01 )	
			echo_info "------------CASX_LOOP_01-----------"
			sleep 1;	
			;;
		CASX_CLOSE_FILE )
			echo_info "------------CASX_CLOSE_FILE--------"		
			casx=CASX_EXIT;;
		--[hH][eE][lL][pP] | -[hH] )
			#echo_info "Usage: $0 help ";
			casx=CASX_EXIT;;
		*)
			echo_info  "jmp to help";
			casx=--help;;
	esac	
	done


	echo_info "end   $FUNCNAME ********************************************"
	return $ret;
}


safe_kill()
{	
	local pid=`/bin/pidof $1`
	if [ -n "$pid" ]; then
		kill -9 $pid
	fi
}




self_lock_flock()
{
	#local ret=$SUCCESS
	#1. 这里需要先确认flock命令是否存在。
	if [ -z $(which flock) ]; then
		echo_info "flock doesn't exist."
		exit 1
	fi
}
self_lock()
{
	:
}
self_unlock()
{
	:
}


file_size_get()
{
	local tmp=0
	if test $# -eq 0 ;then
		echo_info "get file size"
		echo_info "Usage: $FUNCNAME <filename>"
		return $FAILED;
	fi
	if  [ ! -f $1 ];then
		tmp=0
	else
		tmp=`ls -l $1 | awk '{print $5}' `
	fi

	echo $tmp
}

# /******************script function

version_get()
{
	:
}


backup_log()
{
	local i=0
	local ret=$SUCCESS
	local res=$SUCCESS
	local tmp="x"
	local src=''
	local dest=''
	local rm_src=''

	echo "" > /dev/null
	echo "" > /dev/null
	
	if test $# -eq 0 ;then
		echo_info "backup log"
		echo_info "Usage: $FUNCNAME <src> <dest> [--rm]"
		echo_info "List directory contents"
        	echo_info "src  source:dir or file"
		echo_info "dest destination:destination file.use absolute path"
		echo_info "--rm will delete source file or directory"
		return $FAILED;
	fi

	src=$1
	dest=$2

	#echo_info "start $FUNCNAME ********************************************"
	
	if [ $3'x' == '--rm''x' ];then
		echo_info "backup $1 to $2.tar.gz and rm $1"
		rm_src="rm -r $src"
	else
		echo_info "backup $1 to $2.tar.gz and reserve $1 "
	fi
	#0--8	loop 9 times 
	for((i=$COUNT_BACKUP_LOG - 1; i>0;i=i-1))  
	do
		mv ${dest}_$((i-1)).tar.gz  ${dest}_$i.tar.gz >> $FILE_LOG_SELF 2> /dev/null
	done

	#the file att has date
	tar -czvf ${dest}_0.tar.gz ${src} >> $FILE_LOG_SELF 2> /dev/null
		
	$rm_src >> $FILE_LOG_SELF 2>&1

	#echo_info "end   $FUNCNAME ********************************************"
	return $ret;
}

self_log_loopback()
{
	#sleep 1
	
	while true
	do
		sleep 60
		if [ ! -e $FILE_LOG_SELF ];then
			touch $FILE_LOG_SELF
		fi
		
		local tmp=`ls -l $FILE_LOG_SELF | awk '{print $5}' `
		#echo_debug "backup file size = $tmp"
		if [ $tmp"x" != "x" ] && [ $tmp -gt $SIZE_LOG_SELF ];then	
			echo_debug "backup file size = $tmp"
			backup_log ${FILE_LOG_SELF} ${FILE_LOG_SELF} "--rm"
		fi
	done
}

monitor_reboot()
{
	echo_info "start $FUNCNAME ********************************************"

	echo "" >> $FILE_LOG_SELF 2>&1
	echo "" >> $FILE_LOG_SELF 2>&1
	#memory
	free -m  >> $FILE_LOG_SELF 2>&1

	echo "" >> $FILE_LOG_SELF 2>&1
	echo "" >> $FILE_LOG_SELF 2>&1
	#disk
	df -h   >> $FILE_LOG_SELF 2>&1

	echo "" >> $FILE_LOG_SELF 2>&1
	echo "" >> $FILE_LOG_SELF 2>&1
	#net
	ifconfig -a >> $FILE_LOG_SELF 2>&1

	echo "" >> $FILE_LOG_SELF 2>&1
	echo "" >> $FILE_LOG_SELF 2>&1
	#process,process memory,process state,cpu
	top -b -n 1  >> $FILE_LOG_SELF 2>&1

	echo_info "end   $FUNCNAME ********************************************" 
}

monitor_loop()
{
	echo_info_nolog "start $FUNCNAME ********************************************"  >> $FILE_LOG_FS_MONITOR 2>&1
	while true
	do
		sleep 100
	done
	echo_info_nolog "end   $FUNCNAME ********************************************"  >> $FILE_LOG_FS_MONITOR 2>&1
}

monitor_once_start()
{
	echo_info "start $FUNCNAME ********************************************"
	echo_info "fs_ver=`cat /version`"
	echo_info "disk_fs_ver=`cat /mnt/disk1/rootfs/version`"
	echo_info "kernel_ver=`uname -a`"
	echo_info "end   $FUNCNAME ********************************************"
}
close_radio()
{
	dw wr spi02 04b9 1 >> $FILE_LOG_SELF 2>&1
	dw wr spi02 04d1 0 >> $FILE_LOG_SELF 2>&1
	sleep 1
	dw wr spi02 04b9 1 >> $FILE_LOG_SELF 2>&1
}


gpio_set_high()
{
	dw wr gpio $1 1 
}
gpio_set_low()
{
	dw wr gpio $1 0 
}


dog_feed()
{
	local i=0
	local ret=$SUCCESS
	local res=$SUCCESS
	local tmp="x"
	
	#echo $#
	#bash bug:"if [ $# == 0 ] " will run but $# is 1 actually,must add something befor if condition
	#bug general condition
	#function is run in background with argument,and "if $#" or other judge condition was run first
	echo "" > /dev/null
	echo "" > /dev/null

	echo_info "start $FUNCNAME ********************************************"

	while true;
	do
		GPIO_DOG_FLAG=`cat $FILE_PROCESS_DOG`
		if [ $GPIO_DOG_FLAG == "start"  ];then			
		        gpio_set_high $GPIO_DOG  > /dev/null
			echo_info_nolog "$GPIO_DOG feed 1" >> $FILE_LOG_DOG
		        sleep 1
		        gpio_set_low  $GPIO_DOG  > /dev/null
			echo_info_nolog "$GPIO_DOG feed 0" >> $FILE_LOG_DOG
		        sleep 1
		else
			echo_info_nolog "stop feed dog"   >> $FILE_LOG_DOG
			sleep 1
		fi
		local tmp=` file_size_get $FILE_LOG_DOG `
		if [ $tmp -gt $SIZE_LOG_DOG ];then
			mv $FILE_LOG_DOG $FILE_LOG_DOG.0
		fi
	done


	echo_info "end   $FUNCNAME ********************************************"
	return $ret;

}


#看来函数能覆盖 系统命令，很有用处的东西,需要找到调用原系统命令的方法配合使用
#exec reboot 待测试
#hz_reboot 被后台执行，则无法再影响父进程中的  GPIO_DOG_FLAG
hz_reboot() 
{

	local i=0
	local ret=$SUCCESS
	local res=$SUCCESS
	
	local tmp_src="x"
	local tmp_dest="x"
	local tmp_app="x"
	local tmp_reason='x'
	local tmp_file_history=/dev/shm/reboot.tmp
	echo "" > /dev/null
	echo "" > /dev/null

	local debug_reboot=0
	
	if test $# -lt 2 ;then
		echo_info "Usage: $FUNCNAME <source> <reason>"
		echo_info "source which application generate reboot"
        	echo_info "reason why to reboot"		
		return $FAILED;
	fi

	echo_info "start $FUNCNAME ********************************************"
	tmp_app="$1"
	tmp_reason="""$2"""
	#待优化
	#echo $1 
	#echo $2

	#echo "$@" 
	tmp_src="/OAM/bin/enb/log/  /OAM/bin/enb/arm/blackbox*  /OAM/log/ /var/log/messages  $FILE_REBOOT_REASON"
	tmp_dest="$DIRE_LOG_SELF/ram.log"  #$DIRE_LOG_SELF/ram.log.tar.gz
	
	monitor_reboot

	echo_info "close radio"
	close_radio

	echo_info_nolog "app=$tmp_app"     > $FILE_REBOOT_REASON
	echo_info_nolog "reason=$tmp_reason"   >> $FILE_REBOOT_REASON

	echo_info "reboot app=$tmp_app"
	echo_info "reboot reason=$tmp_reason"

	echo_info_nolog "app=$tmp_app"     >> $FILE_REBOOT_REASON_HISTORY
	echo_info_nolog "reason=$tmp_reason"   >> $FILE_REBOOT_REASON_HISTORY
	tail -n 200 $FILE_REBOOT_REASON_HISTORY > $tmp_file_history
	cat  $tmp_file_history > $FILE_REBOOT_REASON_HISTORY




	backup_log "$tmp_src" "$tmp_dest" 
		
	#stop feeddog
	GPIO_DOG_FLAG="stop"
	echo "$GPIO_DOG_FLAG" > $FILE_PROCESS_DOG  #init file

	if [ $debug_reboot == '1' ];then
		:
	else
		reboot
	fi

	echo_info "end   $FUNCNAME ********************************************"
	return $ret;
}


socket_s()
{
	#nc -l 1234
	sleep 1
	echo "" > /dev/null
	echo "" > /dev/null
	echo_info "listen port $SOCKET_TCP_S_PORT_0"
	while true
	do
		tmp=`nc -lp $SOCKET_TCP_S_PORT_0`
		#tmp=`nc -llp $SOCKET_TCP_S_PORT_0 -e $tmp`
		if test "$tmp"'x' != 'x';then
			#防止错误命令卡住后不再监听端口号
			# "$tmp" 使用引号，则导致无法执行命令，暂时没有解决参数传递问题
			$tmp >> $FILE_LOG_SELF 2>&1  &
			echo_info "cmd=$tmp"
		fi
	done
}

action_moduel()
{
	#funciont_moduel $@
	#sleep 1
	#self_init

	monitor_once_start
	sleep 1
	socket_s  &
	self_log_loopback &
	

	#loop ,not exist
	dog_feed

	return $SUCCESS
}

input_get()
{
	:

}

output_put()
{
	:
}



main()
{
	local i=0
	local ret=$SUCCESS
	#local res=$SUCCESS
	#local tmp="x"
	echo_info "/****************************start $NAME_SELF **************************************" 
	if test $# -eq 0 ;then
		echo_info_nolog "Usage: $NAME_SELF <a|b>  [c|d] [-ef]"  	| tee  -a $FILE_LOG_SELF 
		echo_info_nolog "List directory contents"  	 		| tee  -a $FILE_LOG_SELF 
        	echo_info_nolog "a|b  must select only one"   	 		| tee  -a $FILE_LOG_SELF 
		echo_info_nolog "c|d  select only one or not select"  		| tee  -a $FILE_LOG_SELF 
		echo_info_nolog "ef   can select more than one"  		| tee  -a $FILE_LOG_SELF 

		return $FAILED;
	fi
		
	#action description
	echo_info "/--------------------" 	
	echo_info "version=$VERSION_SELF" 	
	echo_info "action description"  	
	echo_info "run module.sh "  		
	echo_info "--------------------/"  


	while true
	do		
		#1. 这里需要先确认flock命令是否存在。
		if [ -z $(which flock) ]; then
			echo_warn "flock doesn't exist." #| tee  -a $FILE_LOG_SELF		
			flag_flock=$FAILED
		fi

#		LCK="$FILE_LOCK_SELF";
#		exec 200>$LCK;
#		flock -xn 200
#		if test $? -eq 0 ; then
#			echo "I'm in ($$)";
#			sleep 5; # XXX: Do something interesting here.
#			echo "I'm done ($$)";
#		else
#			echo "I'm rejected ($$)";
#		fi

		
		exec 200>$FILE_LOCK_SELF;
		flock -xn 200
		if [ $? -eq 0 ] || [ $flag_flock == $FAILED ]; then
			echo_info "lock success"
			action_moduel $@  # >> $FILE_LOG_SELF 2>&1
			if test $? = $SUCCESS;then
				ret=$SUCCESS
			else
				ret=$FAILED
			fi
		else	
			echo_warn "lock failed. $NAME_SELF is busy" 
			ret=$FAILED
		fi
		
		break
	done


	local tmp=`ls -l $FILE_LOG_SELF | awk '{print $5}' `
	#touch $FILE_LOG_SELF
	#echo "$tmp $SIZE_FILE_LOG_SELF"
	echo_info "*****************************end   $NAME_SELF *************************************/"
	if test $tmp -gt $SIZE_LOG_SELF ;then	
		backup_log ${FILE_LOG_SELF} ${FILE_LOG_SELF} "--rm"
	fi
	
	return $ret
}



main $@
value_exit=$?
exit $value_exit


