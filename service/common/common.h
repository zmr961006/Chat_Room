/*************************************************************************
	> File Name: common.h
	> Author: 
	> Mail: 
	> Created Time: 2015年08月02日 星期日 21时57分09秒
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H
#include<apue.h>
#include<time.h>

#define MAXBUF    1024
#define PRIVATE     1
#define PUBLIC      2
#define FRIEND      3
#define FILESOME    4
#define DOWNLINE    5
#define SHOWFRIEND  6
#define SHOWONLINE  7
#define LAST        9 //离线消息
#define CHANGEPSD   10
#define KILL        11

typedef struct user{
    char username[20];
    char userpasd[20];
    char objip[32]   ;
    int  previe      ;
    int  many        ; 
    char msg[20]     ;
    int  root        ;
    int submit       ;
}user_t;  //用户首发信息，用来登录，注册报告状态等等

typedef struct user_node{
    user_t data;
    struct user_node *next;
    struct user_node *prev;
}user_node_t,*user_list_t;  //用户首发信息链表节点信息

typedef struct ser_user{
    char username[20];
    char userpasd[20];
    struct sockaddr_in useraddr;
    int    previe    ;
    int    many      ;
    int    online    ;      //1:on;0:off
    int    connfd    ;       //链接套接字
}seruser_t;                 //服务器保存用户信息结构体

typedef struct seruser_node{
    seruser_t data;
    struct seruser_node *next;
    struct seruser_node *prev;
}seruser_node_t,*seruser_list_t; //服务器保存用户链表节点信息

typedef struct listctl_s{
    seruser_list_t head;
    pthread_rwlock_t q_lock;
}listctl_s;                        // 用户信息链表控制结构，读写锁

typedef struct file_info{          //传送文件信息结构体
    char name[10];                 //文件名
    int  head    ;                //文件头（计划排序数据包，。。。。—）
    int  flag    ;                 //标识
    int  len     ;                 //长度
}file_info;



typedef struct message{
    char fname[20]   ;                //发送人
    char oname[20]   ;                //给什么人
    int  type        ;                //消息类型 群发，私聊，文件，好友信息
    char message[800];            //消息主体
    file_info file   ;
}message_t;                        //通讯信息通用结构体


typedef struct friends{
    char name[20];
    int type     ;
    char online  ;
    seruser_t  data;
}friends_t;                  //好友信息结构体

typedef struct friends_node{
    friends_t data;
    struct friends_node *next;
    struct friends_node *prev;
}friends_node_t,*friends_list_t; //好友信息链表节点


typedef struct listctl_f{

    friends_list_t head;
    pthread_rwlock_t q_lock;

}listctl_f;


typedef struct syslog{      //日志信息
    
    char name[20];
    char time[100];
    char work[20];
}syslog_t;


seruser_list_t list_ser;









#endif
