/*************************************************************************
	> File Name: common.h
	> Author: 
	> Mail: 
	> Created Time: 2015年08月04日 星期二 21时44分07秒
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H
#include<apue.h>
#include<netdb.h>
#include<pthread.h>
#include"./List.h"
#include<gtk/gtk.h>

#define SERVER_PORT 8003            //固定端口为8003
#define MAXDATASIZE 1024            //最大缓冲区限制
#define MAXBUF      1024            

#define PRIVATE     1               //私人聊天
#define PUBLIC      2               //多人聊天
#define FRIEND      3               //朋友标识
#define FILESOME    4               //文件信息
#define DOWNLINE    5               //离线状态
#define SHOWFRIEND  6               //展示朋友标识
#define SHOWONLINE  7               //展示在线人员标识
#define TIME        8               //时间信息
#define LAST        9               //离线消息
#define CHANGEPSD   10  
#define KILL        11



typedef struct user{
    
    char username[20];
    char userpasd[20];
    char objip[32];
    int  previe;
    int  many  ;
    char msg[20];
    int  root   ;
    int  submit ;
}user_t;                            //用户结构体

typedef struct file_info{
    char name[10];
    int  head    ;
    int  flag    ;
    int  len      ;
}file_info;                         //文件结构体 

typedef struct message{
    char fname[20];
    char oname[20];
    int  type     ;
    char message[800];
    file_info  file;
}message_t;                         //消息结构体

int sd;                             //全局的套接字
typedef struct window{
   
   char name[20];
   
}window_t;                          //窗口注册结构体

typedef struct window_node{
    window_t data;
    struct window_node *next;
    struct window_node *prev;
}window_node_t,*window_list_t;      //窗口注册链表       

window_list_t list_name;

char get_com_buf[1024];  //公共缓冲区

char local_name[30];     //用户名
char mess_name[30];      //消息记录文件名

char filenames[30];      //发送文件名
char getname[30];        //应当接受文件名
char whogive[20];
int  file;               //文件发送信号标示，当信号为1时，即时发送消息

int   signal_on_message;

char ftp_oname[20];      //传送文件名
char ftp_tname[20];      //文件名
char ftp_yname[20];      //目标文件名


typedef struct hismessage{

      char fname[10]   ;
      char oname[10]   ;
      char message[800];
      char time[50]    ;
      int  pub         ;

}hismessage_t;           //消息结构体 
     

void BYBY( GtkWidget *widget, gpointer data );  //全局关闭窗口函数

void BYBY_PB( GtkWidget *widget, gpointer data );

#endif
