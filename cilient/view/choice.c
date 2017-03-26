/*************************************************************************
	> File Name: choice.c
	> Author: 
	> Mail: 
	> Created Time: 2015年08月05日 星期三 09时59分36秒
 ************************************************************************/

#include<stdio.h>
#include"./choice.h"
#include<gtk/gtk.h>
#include"./prive.h"
#include"../common/common.h"
#include"./public.h"
#include"./ftp.h"
static GtkWidget *entry4;

void destroybyby( GtkWidget *widget,gpointer data );

void destroybyby( GtkWidget *widget,gpointer data )  //窗口关闭函数
{
        char buf[MAXBUF];
    	message_t message;
        strcpy(message.message,"qxff951124");
        strcpy(message.fname,local_name);
        message.type = DOWNLINE;
        memcpy(buf,&message,sizeof(message_t));
        send(sd,buf,sizeof(buf),0);            
        printf("the send is %d\n");
	sleep(1);
	gtk_main_quit ();
	
}



int  choice_view(user_t *user,const char *servip,int sd)   //选择聊天模式窗口界面
{
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *button;
    //formal_link(user,servip);
    strcpy(local_name,user->username);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window),
                               500,500);
    g_signal_connect(G_OBJECT(window),"destroy",
                    G_CALLBACK(destroybyby),NULL);
    gtk_window_set_title(GTK_WINDOW(window),"welcom T&T");
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window),20);

    box = gtk_vbox_new(TRUE,0);
    gtk_container_add(GTK_CONTAINER(window),box);

    pthread_t thid;                                         
    pthread_create(&thid,NULL,get_message,NULL);  //全局一个接收信息函数


    button = gtk_button_new_with_label("Private"); //测试阶段
    g_signal_connect(G_OBJECT(button),"clicked",
                    G_CALLBACK(showtalk),NULL);
    gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,5);
    
     button = gtk_button_new_with_label("Public");  //未开始
    g_signal_connect(G_OBJECT(button),"clicked",
                    G_CALLBACK(showtalk_p),NULL);
    gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,5);
    
    button = gtk_button_new_with_label("FTP");    //未开始
    g_signal_connect(G_OBJECT(button),"clicked",
                    G_CALLBACK(showFTP),(gpointer)user);
    gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,5);
    
    button = gtk_button_new_with_label("change password"); //测试阶段
    g_signal_connect(G_OBJECT(button),"clicked",
                    G_CALLBACK(change_show),NULL);
    gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,5);

    button = gtk_button_new_with_label("root/mangerment"); //测试阶段
    g_signal_connect(G_OBJECT(button),"clicked",
                    G_CALLBACK(root_show),NULL);
    gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,5);

    
    gtk_widget_show_all(window);

    //formal_link(user,servip);
}

void createview(void *arg)             //创建界面函数（废弃）
{
     pthread_t thid;
     //pthread_create(&thid,NULL,private_t,NULL);
     
}


void change_show(GtkWidget *widget,gpointer data){
    GtkWidget *window;
    
    window = change_show_p();
    
    gtk_widget_show_all(window);

}



GtkWidget *change_show_p(){

    GtkWidget *win,*vbox;
    GtkWidget *button;
    GtkWidget *old_psd;
    GtkWidget *new_psd;
   
   psd *chps;
   chps = (psd *)malloc(sizeof(psd));
   
    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(win),"change psd");
    gtk_container_set_border_width(GTK_CONTAINER(win),20);
    g_signal_connect(G_OBJECT(win),"delete_event",
                     G_CALLBACK(BYBY),NULL);
    gtk_window_set_modal(GTK_WINDOW(win),TRUE);
    gtk_window_set_position(GTK_WINDOW(win),GTK_WIN_POS_CENTER);

    vbox = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(win),vbox);
    old_psd= gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(old_psd),FALSE);
    gtk_box_pack_start(GTK_BOX(vbox),old_psd,TRUE,TRUE,5);
    
    new_psd= gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(new_psd),FALSE);
    gtk_box_pack_start(GTK_BOX(vbox),new_psd,TRUE,TRUE,5);
    
    chps->old_psd = old_psd;
    chps->new_psd = new_psd;

    button = gtk_button_new_with_label("sure");        
    g_signal_connect(G_OBJECT(button),"clicked",
                    G_CALLBACK(change_psd_s),(gpointer)chps);
    gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,5);
    chps->window = win;    
    return win;
}

int change_psd_s(GtkWidget *widget,gpointer data){

	psd *test = (psd *)data;
        const char *old;
        const char *new;
        char old_p[30];
        char new_p[30];
        old = gtk_entry_get_text(GTK_ENTRY(test->old_psd));
        new = gtk_entry_get_text(GTK_ENTRY(test->new_psd));
	strcpy(old_p,old);
	strcpy(new_p,new);
	printf("the old is %s the new is %s \n",old_p,new_p);
        
	message_t message;
        char buf[1024];
        strcpy(message.fname,local_name);
        strcpy(message.oname,old_p);
        strcpy(message.message,new_p);
        message.type = 10;
        
        memcpy(buf,&message,sizeof(message_t));
        send(sd,buf,sizeof(buf),0);
        gtk_widget_destroy(test->window);
	return 0;
}    


void root_show(GtkWidget *widget,gpointer data){

	
    GtkWidget *window;
    
    window = root_show_p();
    
    gtk_widget_show_all(window);


}


GtkWidget *root_show_p(){                           //创建历史消息窗口
   
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *text  ;
    GtkWidget *view  ;
    GtkWidget *box   ;
    GtkTextBuffer *buffer;
     GtkWidget *objname;
   val *data;
   data = (val *)malloc(sizeof(val));
   

   window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(window),"root/meragement");
   g_signal_connect(G_OBJECT(window),"delete_event",
                     G_CALLBACK(BYBY_PB),(gpointer)window);
   gtk_window_set_default_size(GTK_WINDOW(window),400,600);
   gtk_container_set_border_width(GTK_CONTAINER(window),10);
   
   box = gtk_vbox_new(FALSE,0);
   gtk_container_add(GTK_CONTAINER(window),box);
   
   view = gtk_scrolled_window_new(NULL,NULL);                 //显示历史信息
   gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(view),
            GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
   text = gtk_text_view_new();                                //好友信息接受框
   gtk_box_pack_start(GTK_BOX(box),view,TRUE,TRUE,5);         //向盒子加入视图
   gtk_container_add(GTK_CONTAINER(view),text);               //将文本框加入视图
   buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text));    //buffer接受文本框信息 
   


    objname= gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(objname),FALSE);
    gtk_box_pack_start(GTK_BOX(box),objname,TRUE,TRUE,5);

   //data->view   = view    ;
   data->buffer_f = buffer  ;
   data->text_f   = text    ;
   
   button = gtk_button_new_with_label("show me the online people");          //显示历史消息
   gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,5);
   g_signal_connect(G_OBJECT(button),"clicked",
                    G_CALLBACK(show_online),NULL);

   
   button = gtk_button_new_with_label("start manage the online people");          //显示历史消息
   gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,5);
   g_signal_connect(G_OBJECT(button),"clicked",
                    G_CALLBACK(start_talk_p),(gpointer)data);
   data->button = button;
   
   button = gtk_button_new_with_label("kill people");          //显示历史消息
   gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,5);
   g_signal_connect(G_OBJECT(button),"clicked",
                    G_CALLBACK(kill_people),(gpointer)objname);
   
   return window;
}


int kill_people(GtkWidget *widget,gpointer data){

	message_t message;
        char buf[1024];
        const char *temp;
        char obj[30];
        strcpy(message.fname,local_name);
        temp = gtk_entry_get_text(GTK_ENTRY(data));
        strcpy(obj,temp);
        
        strcpy(message.oname,obj);
        message.type = 11;
        memcpy(buf,&message,sizeof(message_t));
        send(sd,buf,sizeof(buf),0);
        return 0;
}






	


