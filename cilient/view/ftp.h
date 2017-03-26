/*************************************************************************
	> File Name: ftp.h
	> Author: 
	> Mail: 
	> Created Time: 2015年08月12日 星期三 21时54分53秒
 ************************************************************************/

#ifndef _FTP_H
#define _FTP_H

#include "../common/common.h"
#include <stdio.h>
typedef struct file{
     GtkWidget *window;
     GtkWidget *entry;
}file_t;



void showFTP(GtkButton *button,gpointer data); //显示FTP主窗口

GtkWidget* ftp( );       //ftp主要创建窗口

void on_button_c(GtkWidget *button,gpointer userdata); //弹出选择文件的窗口

void on_file_select_ok (GtkWidget *button,gpointer data);//选择完成后的提示窗口

void sure_file(GtkWidget *button,gpointer data);         //回显确认需要传送的文件

void send_file_f(GtkWidget *button,gpointer data);         //发送文件前提消息

void recv_file(GtkWidget *button,gpointer data);         //接受文件函数

void send_file(char *tname,char *oname,char *yname);     //正式开始发送文件

void * temp_file(void *arg);                    //发送文件函数，中间件  
 
void * recv_file_get(void *arg);                     //接受文件线程函数                           
#endif
