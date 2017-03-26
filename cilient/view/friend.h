/*************************************************************************
	> File Name: friend.h
	> Author: 
	> Mail: 
	> Created Time: 2015年08月11日 星期二 19时21分01秒
 ************************************************************************/

#ifndef _FRIEND_H
#define _FRIEND_H
#include "../common/common.h"
#include "./prive.h"
#include "./public.h"
#include <gtk/gtk.h>

typedef struct area{        //传递缓冲区与窗口结构体

     GtkWidget *entry;
     GtkWidget *window;
}area;

typedef struct addfriend{      //传递消息结构体与窗口函数
     GtkWidget *window;
     message_t message;
}af;


void show_add_friend(GtkButton *button,gpointer data);   //展示添加好友界面

GtkWidget *show_add();                                 //创建一个好友界面

int add_friend(GtkButton *button,gpointer data);        //向服务器发送一条请求添加好友的请求

int f_show_friend(GtkButton *button,gpointer data);      //向服务器发送一个消息，需要更新好友列表

void show_del_friend(GtkButton *button,gpointer data);   //展示一个添加好友界面

GtkWidget *show_del();                                  //创建一个删除好友的界面

int del_friend(GtkButton *button,gpointer data);         //给服务器发送一个删除好友的请求

//void * recv_add(void *arg);                        //处理好友添加操作

//int tell_add(message_t message);

//int tell_add_recv(GtkButton *button,gpointer data);
#endif
