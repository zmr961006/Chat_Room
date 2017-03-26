/*************************************************************************
	> File Name: login.h
	> Author: 
	> Mail: 
	> Created Time: 2015年08月03日 星期一 09时32分57秒
 ************************************************************************/

#ifndef _LOGIN_H
#define _LOGIN_H
#include<stdio.h>
#include<gtk/gtk.h>
#include<stdlib.h>
#include<pthread.h>
#include"../srv/srv.h"
#include"./choice.h"
#include"./prive.h"


typedef struct off{
   GtkWidget *window1;
   GtkWidget *window2;
}off;

GtkWidget * login_view();

int on_button_clicked(GtkWidget *button,gpointer data);

int destroy_son(GtkWidget *widget,gpointer data);

int on_button_entry3(GtkWidget *button,gpointer data);

#endif
