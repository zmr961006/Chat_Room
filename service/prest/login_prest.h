/*************************************************************************
	> File Name: login_prest.h
	> Author: 
	> Mail: 
	> Created Time: 2015年08月02日 星期日 22时03分59秒
 ************************************************************************/

#ifndef _LOGIN_PREST_H
#define _LOGIN_PREST_H


#include"../common/List.h"
#include"../common/common.h"
int serve_Perst_SelectAll(seruser_list_t list);  //从文件中读取链表

int seruser_Perst_Insert(seruser_t *data);       //将信息写入
 
int seruser_perst_update(const seruser_t * data);   //更新用户信息

int add_prest_syslog(syslog_t * data);            //将日志写入文件
#endif
