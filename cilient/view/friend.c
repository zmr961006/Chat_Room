/*************************************************************************
	> File Name: friend.c
	> Author: 
	> Mail: 
	> Created Time: 2015年08月11日 星期二 19时20分57秒
 ************************************************************************/

#include<stdio.h>
#include"./friend.h"
#include"./prive.h"
void show_add_friend(GtkButton *button,gpointer data){  //展示添加好友界面
     
      GtkWidget *window;
      printf("friend is git\n");
      window = show_add();
      gtk_widget_show_all(window);
      
}


GtkWidget *show_add(){                     //创造添加好友界面
     
    GtkWidget *win,*vbox;
    GtkWidget *button;
    GtkWidget *name_entry;
    area * ar;
    ar = (area *)malloc(sizeof(area));
   
   
   
    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(win),"pleae enter name");
    gtk_container_set_border_width(GTK_CONTAINER(win),10);
    g_signal_connect(G_OBJECT(win),"delete_event",
                     G_CALLBACK(BYBY),NULL);
    gtk_window_set_modal(GTK_WINDOW(win),TRUE);
    gtk_window_set_position(GTK_WINDOW(win),GTK_WIN_POS_CENTER);

    vbox = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(win),vbox);
    name_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox),name_entry,TRUE,TRUE,5);
    ar->entry  = name_entry;
    button = gtk_button_new_with_label("sure");        //确认添加好友
    g_signal_connect(G_OBJECT(button),"clicked",
                    G_CALLBACK(add_friend),(gpointer)ar);
    gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,5);
    
    ar->window = win;
    //gtk_widget_show_all(win);
    return win;
}

int add_friend(GtkButton *button,gpointer data){     //添加好友参数
    
    const char *objname;
     
    area *test = (area *)data;
   
    objname = gtk_entry_get_text(GTK_ENTRY(test->entry));
    
    gtk_widget_hide(test->window);
    
    printf("i want friend is %s\n",objname);
    char buf[MAXBUF];
    message_t message;
    message.type = FRIEND;
    strcpy(message.fname,local_name);
    strcpy(message.oname,objname);
    strcpy(message.message,"ADD");
    
    memcpy(buf,&message,sizeof(message_t));
    
    send(sd,buf,sizeof(buf),0);
}



int f_show_friend(GtkButton *button,gpointer data){    //请求得到好友信息
    
     
     char buf[MAXBUF];
     /*GtkTextIter start,end;
     val * test = (val *)data;
     gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(test->buffer_f),&start,&end);
     printf("lalalallalalalalallalalalalalalla\n");
     gtk_text_buffer_delete(test->buffer_f,&start,&end);
     printf("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\n");
     */
     message_t message;
     message.type = SHOWFRIEND;
     strcpy(message.fname,local_name);
     strcpy(message.oname,"server");
     strcpy(message.message,"SHOW");
     memcpy(buf,&message,sizeof(message_t));
    
     send(sd,buf,sizeof(buf),0);
}   


void show_del_friend(GtkButton *button,gpointer data){   //展示删除好友窗口
     
      GtkWidget *window;
      printf("friend is git\n");
      window = show_del();
      gtk_widget_show_all(window);
      
}

GtkWidget *show_del(){                                   //创建删除好友窗口
     
    GtkWidget *win,*vbox;
    GtkWidget *button;
    GtkWidget *name_entry;
    area * ar;
    ar = (area *)malloc(sizeof(area));
   
     
    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(win),"pleae enter name");
    gtk_container_set_border_width(GTK_CONTAINER(win),10);
    g_signal_connect(G_OBJECT(win),"delete_event",
                     G_CALLBACK(BYBY),NULL);
    gtk_window_set_modal(GTK_WINDOW(win),TRUE);
    gtk_window_set_position(GTK_WINDOW(win),GTK_WIN_POS_CENTER);

    vbox = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(win),vbox);
    name_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox),name_entry,TRUE,TRUE,5);
    ar->entry  = name_entry;
    button = gtk_button_new_with_label("sure");  //未开始
    g_signal_connect(G_OBJECT(button),"clicked",
                    G_CALLBACK(del_friend),(gpointer)ar);
    gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,5);
    
    ar->window = win;
    return win;
}

int del_friend(GtkButton *button,gpointer data){        //删除好友
    
    const char *objname;
     
    area *test = (area *)data;

    objname = gtk_entry_get_text(GTK_ENTRY(test->entry));
    
    gtk_widget_hide(test->window);
    
    printf("i want friend is %s\n",objname);
    char buf[MAXBUF];
    message_t message;
    message.type = FRIEND;
    strcpy(message.fname,local_name);
    strcpy(message.oname,objname);
    strcpy(message.message,"DEL");
    
    memcpy(buf,&message,sizeof(message_t));
    
    send(sd,buf,sizeof(buf),0);

}

/*void *recv_add(void *arg){
     message_t mess;
     message_t* message;
     message = (message_t *)arg;
     //message = *mess;
     printf("LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL\n");
     printf("the mseeages = %s\n",message->message);
     tell_add(mess);
    if(strcmp(message->message,"ADD") == 0){
            
       	     tell_add(mess);

    }
   /* if(strcmp(message.message,"RECV") == 0){
    
         message_t mess;
         char buf[MAXBUF];
         strcpy(mess.fname,local_name);
         strcpy(mess.oname,message.fname);
         strcpy(mess.message,"GET");
         mess.type = FRIEND;
         memcpy(buf,&mess,sizeof(message_t));
         send(sd,buf,sizeof(buf),0);
           
    }

}

int tell_add(message_t message)
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *label;
    GtkWidget *vbox;
    printf("momomomomomomomomomo\n");
    af *data;
    data = (af *)malloc(sizeof(af));
    char buf[30];
    strcpy(buf,message.fname);
    strcat(buf," want add you!");
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"friend add new");
    gtk_window_set_default_size(GTK_WINDOW(window),200,300);
    gtk_container_set_border_width(GTK_CONTAINER(window),10);
    g_signal_connect(G_OBJECT(window),"delete_event",
                     G_CALLBACK(BYBY),NULL);
    //gtk_window_set_modal(GTK_WINDOW(window),TRUE);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  
    vbox = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(window),vbox);
    
    label = gtk_label_new(buf);
    gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,5);
    
    data->message = message;
    data->window = window;
    button = gtk_button_new_with_label("sure");//创建按钮，暂时没什么用
    gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,5);
    g_signal_connect(G_OBJECT(button),"clicked",
                    G_CALLBACK(tell_add_recv),(gpointer)data);
   
    gtk_widget_show_all(window);
}
    
int tell_add_recv(GtkButton *button,gpointer data){
     
	af *test = (af*)data;
        gtk_widget_hide(test->window);
        
        message_t message;
        char buf[MAXBUF];
        
        strcpy(message.fname,local_name);
        strcpy(message.oname,test->message.oname);
        strcpy(message.message,"RECV");
        message.type = FRIEND;
        
        memcpy(buf,&message,sizeof(message_t));
        send(sd,buf,sizeof(buf),0);
}*/









