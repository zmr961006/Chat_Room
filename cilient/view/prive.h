/*************************************************************************
	> File Name: prive.h
	> Author: 
	> Mail: 
	> Created Time: 2015年08月06日 星期四 02时53分23秒
 ************************************************************************/

#ifndef _PRIVE_H
#define _PRIVE_H

#include<stdio.h>
#include<gtk/gtk.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<apue.h>
#include<pthread.h>
#include"../common/common.h"
#include"./friend.h"
//int sd;                  //全局一个套接字
//struct sockaddr_in s_in; //链接套接字
char username[64];      //用户名
//char buf[1024];         //写缓冲区
//char get_buf[1048];     //读缓冲区

//gboolean isconnected = FALSE;  //定义逻辑表示

//static GtkWidget *text;      //文本构件
//static GtkTextBuffer *buffer; //显示对话内容的文本显示缓冲区
//static GtkWidget *message_entry; //显示输入消息的单行陆入控件
static GtkWidget *name_entry;//输入用户名的单行控件
//static GtkWidget *login_button;//链接按钮
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//全局的一个锁，专门为线程准备
//static GtkWidget *entry6;

void *get_message(void *arg);       //接受服务器数据总线程

void on_destory(GtkWidget *widget,GdkEvent *event,gpointer data);    //关闭窗口函数

void on_button_clicke(GtkButton *button,gpointer data);             //按钮事件触发

void create_win(void);                                               //创建窗口函数

gboolean do_connect(void);                                          //连接函数

void on_send(GtkButton *button,gpointer data);                     //发送消息函数

void on_login(GtkWidget *button,gpointer data);                      //登录函数


void on_delete_event(GtkWidget *widget,GdkEvent *event,gpointer data);   //关闭窗口函数

void *private_t();                                                    //创建私聊窗口函数

void *on_message(void *arg);                                         //接受并且打印消息到屏幕上函数

typedef struct val{
      	GtkTextBuffer *buffer;    //聊天消息显示缓冲区
        GtkWidget *text;
	GtkWidget *message_entry;
        GtkWidget *name_entry;
        
        GtkTextBuffer *buffer_f;//朋友显示信息
        GtkWidget *text_f;
        GtkWidget *button;
        int    sig;
    }val;

typedef struct show_message{                                  //历史消息传参结构体

     GtkWidget     *text  ;
     GtkTextBuffer *buffer;
     GtkWidget     *view  ;
     GtkWidget     *entry ;

}his_message_t;

GtkWidget *private_t_n();                                     //创建私聊消息窗口函数
 
window_list_t list_name;                                      //注册窗口结构体

void start_talk(GtkButton *button,gpointer data);             //开始私聊函数

void showtalk(GtkButton *button,gpointer data);               //启动私聊函数线程函数

int find_byname(char *fname);                                 //查找名字

int find_public();                                            //查找是否有公共聊天标记

void BYBY_p( GtkWidget *widget, gpointer data );              //关闭群聊窗口及其线程

void show_history(GtkButton *button,gpointer data);           //显示历史消息按钮

GtkWidget * history(gpointer data);         //创建历史消息按钮

int show_history_message(GtkButton *button,gpointer data);  //展示历史消息窗口

int add_hismessage(message_t message,char *time);            //将受到的消息添加进文件

void last_mess_get();                                         //请求离线消息

#endif
