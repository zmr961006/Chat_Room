/*************************************************************************
	> File Name: public.h
	> Author: 
	> Mail: 
	> Created Time: 2015年08月10日 星期一 21时31分19秒
 ************************************************************************/

#ifndef _PUBLIC_H
#define _PUBLIC_H


#include"../common/common.h"
#include<gtk/gtk.h>
#include<stdio.h>
#include"./prive.h"
#include"./choice.h"

void showtalk_p(GtkButton *button,gpointer data);

GtkWidget *private_t_p();

void on_send_p(GtkButton *button,gpointer data);

void  * on_message_p(void *arg);

void start_talk_p(GtkButton *button,gpointer data);

int show_online(GtkButton *button,gpointer data);

void show_history_p(GtkButton *button,gpointer data); 


GtkWidget *history_p();

int  show_history_message_p(GtkButton *button,gpointer data);
#endif
