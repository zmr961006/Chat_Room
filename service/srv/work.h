/*************************************************************************
	> File Name: work.h
	> Author: 
	> Mail: 
	> Created Time: 2015年08月04日 星期二 15时15分27秒
 ************************************************************************/

#ifndef _WORK_H
#define _WORK_H

#include"../common/common.h"
#include"../prest/prest.h"
#include"./login.h"

void *work(void *ser);                 //客户端与服务器端建立的常驻链接

int talk_private(message_t message,int ssd);   //处理点对点私人聊天，以及多个点对点私人聊天

int talk_public(message_t message);    //处理公开聊天室的给种消息交互

int talk_downline(message_t message);  //下线函数

int talk_friend(message_t message,friends_list_t list,listctl_f *ctl);    //获取好友信息函数

int friend_srv_fetchall(listctl_f *ctl,char *name);   //将本来好友信息添加进自己的链表之中

int friend_srv_add(friends_t *data,char *name);    //添加一个好友

int friend_srv_modify(const friends_t *data); //更改一个好友信息对于自己（不可更改对方实际的信息）

int friend_Srv_DeleteByname(char *name,char *obj);   //根据名字删除相关的好友信息

void show_test(message_t message);    //服务器测试首发信息函数

int find_online(seruser_list_t list,char *name); //查找这个好友是否在线，1:on,2:off; 

int talk_showonline(int connfd);  //发送全部在线的人给群聊

int talk_file(message_t message);  //发送文件相关函数 

int talk_show_his(int connfd,char *username);           //发送离线消息

int add_mess_last(message_t message,char *oname);   //记录离线消息

int talk_change_psd(int connfd,char *username,message_t message); 

int talk_kill_people(int connfd,char *username,message_t message); 

#endif
