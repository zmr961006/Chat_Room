/*************************************************************************
	> File Name: login.h
	> Author: 
	> Mail: 
	> Created Time: 2015年08月02日 星期日 21时45分22秒
 ************************************************************************/

#ifndef _LOGIN_H
#define _LOGIN_H

#include"../common/List.h"
#include"../prest/login_prest.h"
int login(int connfd,seruser_t *temp,struct sockaddr_in cil_addr,seruser_list_t list);
inline int serve_srv_fetchall(seruser_list_t list);
//int login_srv_inlist(seuser_list_t list,user_list_t newuser);
//新用户将用户名写入文件

//int login_srv_fetchall(seuser_list_t list);
//从文件中读取链表进内存

//int login_srv_syslog();
//向日志文件写入账户登录信息

inline int seruser_srv_add(seruser_t *data);//添加一个新用户到文件

int find_seruser(seruser_list_t list_ser,char *username,char *userpasd,int connfd);
//查找链表中是否有这个用户

int seruser_srv_modify(const seruser_t *data);//下线更改在线状态

#endif
