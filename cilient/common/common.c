/*************************************************************************
	> File Name: common.c
	> Author: 
	> Mail: 
	> Created Time: 2015年08月03日 星期一 09时36分26秒
 ************************************************************************/

#include<stdio.h>
#include"./common.h"
#include<gtk/gtk.h>
void BYBY( GtkWidget *widget, gpointer data ){
    signal_on_message  = -1;
    gtk_widget_destroy(GTK_WIDGET(data));
}


void BYBY_PB(GtkWidget *widget,gpointer data){

   /* window_list_t pos;
    if(list_name != NULL){
    	for(pos = list_name->next;pos != list_name;pos = pos->next){
		if(strcmp(pos->data.name,"PUBLIC") == 0){
			break;
  		 }
    	}
    	List_DelNode(pos);*/
    	signal_on_message = -1;
    
    	gtk_widget_destroy(GTK_WIDGET(data));
}
