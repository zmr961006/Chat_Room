/*************************************************************************
	> File Name: serve.h
	> Author: 
	> Mail: 
	> Created Time: 2015年08月03日 星期一 21时40分19秒
 ************************************************************************/

#ifndef _SERVE_H
#define _SERVE_H


#include<apue.h>
#include<pthread.h>
#include<pthread.h>
#include"./pthreadpool.h"
#include"../common/common.h"
#define SERVER_PORT 8003
#define BACKLOG     10


int add_srv_syslog(syslog_t * data); //将日志写入文件

int make_sys(seruser_t temp,char *dowork);    //写日志文件进文件

#endif
