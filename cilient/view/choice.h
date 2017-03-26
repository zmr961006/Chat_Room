/*************************************************************************
	> File Name: choice.h
	> Author: 
	> Mail: 
	> Created Time: 2015年08月05日 星期三 09时59分50秒
 ************************************************************************/

#ifndef _CHOICE_H
#define _CHOICE_H

#include<stdio.h>
#include<gtk/gtk.h>
#include<stdlib.h>
#include"../srv/srv.h"
#include"./prive.h"
#include"./ftp.h"


int choice_view(user_t *user,const char *servip,int sd);
//聊天模式选择主界面


//void destroy( GtkWidget *widget,gpointer data );

void createview(void *arg);


typedef struct psd{
	 GtkWidget *old_psd;
          GtkWidget *new_psd;
          GtkWidget *window ;
}psd;

typedef struct root{

    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *text  ;
    GtkWidget *view  ;
    GtkWidget *box   ;
    GtkTextBuffer *buffer;
}root;


void change_show(GtkWidget *widget,gpointer data);

GtkWidget *change_show_p();

int change_psd_s(GtkWidget *widget,gpointer data);

void root_show(GtkWidget *widget,gpointer data);

GtkWidget *root_show_p();

int kill_people(GtkWidget *widget,gpointer data);

#endif
