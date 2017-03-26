/*************************************************************************
	> File Name: login.c
	> Author: 
	> Mail: 
	> Created Time: 2015年08月03日 星期一 08时38分21秒
 ************************************************************************/

#include<stdio.h>
#include<gtk/gtk.h>
#include"login.h"
#include"../srv/srv.h"
#include"./choice.h"
#include"../common/common.h"
#include"./prive.h"
#include"../common/cilent.h"
#include"../common/List.h"
#include<apue.h>
static GtkWidget *entry1;
static GtkWidget *entry2;
void sub_sucess() ;

GdkPixbuf *create_pixbuf(const gchar *filename)       //创建图片标识函数
{
  GdkPixbuf *pixbuf;
  GError    *error = NULL;
  pixbuf = gdk_pixbuf_new_from_file(filename,&error);
  if(!pixbuf){
	fprintf(stderr,"%s\n",error->message);
        g_error_free(error);
  }
  return pixbuf;
}


int destroy_son(GtkWidget *widget,gpointer data)      //一个关闭窗口函数（使用的不多）
{
	return 0;
}

void destroy( GtkWidget *widget,gpointer data )     //破坏一个窗口函数
{
	gtk_main_quit ();
	
}

static GtkWidget* entry3;                          //一个公共缓冲区






void on_button_submit(GtkWidget *buttton,gpointer data)//注册按钮
{
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(entry2));
    off *test = (off *)data;
    gtk_widget_hide(test->window1);
    printf("password %s \n",password);
	//GtkWidget* entry3;
    GtkWidget* window;
    GtkWidget* box;
	GtkWidget* box1;
    GtkWidget* button;
	GtkWidget* label3;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window),300,300);
	g_signal_connect(G_OBJECT(window),"destroy",
	G_CALLBACK(destroy_son),NULL);
    gtk_window_set_title(GTK_WINDOW(window),"submit");
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window),20);
	
	box = gtk_vbox_new(TRUE,0);
	gtk_container_add(GTK_CONTAINER(window),box);
	
	box1 = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(box),box1,FALSE,FALSE,5);
	
    label3 = gtk_label_new("twice pass:");
	entry3 = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry3),FALSE);
	gtk_box_pack_start(GTK_BOX(box1),label3,FALSE,FALSE,10);
	gtk_box_pack_start(GTK_BOX(box1),entry3,TRUE,TRUE,10);
	
	button = gtk_button_new_with_label(" submit");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK
			(on_button_entry3),window); //尝试注册调用函数on_button_entry3
	//g_signal_connect(G_OBJECT(button),"destroy",G_CALLBACK
			//(gtk_widget_destroy),window);
	gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,5);
        
	gtk_widget_show_all(window);

	
}




static GtkWidget* entry1;
static GtkWidget* entry2;
static GtkWidget* entry5;
GtkWidget * login_view ( int ac , char* av[])   //登录主界面
{
	GtkWidget* window;
	GtkWidget* box;
	GtkWidget* box1;
	GtkWidget* box2;
	GtkWidget* label1;
	GtkWidget* label2;
        GtkWidget* label3;
	GtkWidget* button;
	GtkWidget* sep;
    	
        off  *data;
        data = (off *)malloc(sizeof(off));      

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);          //生成登录主窗口
 	gtk_window_set_default_size(GTK_WINDOW(window),500,500);
        data->window1 = window;
	g_signal_connect(G_OBJECT(window),"destroy",
	G_CALLBACK(gtk_main_quit),NULL);
	gtk_window_set_title(GTK_WINDOW(window),"login");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window),20);
	gtk_window_set_icon(GTK_WINDOW(window),create_pixbuf("../p1.png"));   //图片标识
	box = gtk_vbox_new(TRUE,0);
	gtk_container_add(GTK_CONTAINER(window),box);

	box1 = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(box),box1,FALSE,FALSE,5);

	box2 = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(box),box2,FALSE,FALSE,5);

	sep = gtk_hseparator_new();
	gtk_box_pack_start(GTK_BOX(box),sep,FALSE,FALSE,5);

	label1 = gtk_label_new("THENAME:");      //输入用户名
	entry1 = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(box1),label1,FALSE,FALSE,10);
	gtk_box_pack_start(GTK_BOX(box1),entry1,TRUE,TRUE,10);
	label2 = gtk_label_new("  passwd: ");   //输入密码
	entry2 = gtk_entry_new();
	gtk_entry_set_visibility(GTK_ENTRY(entry2),FALSE);
	gtk_box_pack_start(GTK_BOX(box2),label2,FALSE,FALSE,10);
	gtk_box_pack_start(GTK_BOX(box2),entry2,TRUE,TRUE,10);
    
    
    label3 = gtk_label_new("the server ip:");   //输入IP 
    entry5 = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box),label3,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),entry5,TRUE,TRUE,10);



	button = gtk_button_new_with_label(" login ");    //登录按钮
	g_signal_connect(G_OBJECT(button),"clicked",
	G_CALLBACK(on_button_clicked),window);
	//g_signal_connect_swapped(G_OBJECT(button),"clicked",
	//G_CALLBACK(gtk_widget_destroy),window);
	gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,5);

    button = gtk_button_new_with_label(" submit ");    //注册按钮
    g_signal_connect(G_OBJECT(button),"clicked",
        G_CALLBACK(on_button_submit),(gpointer)data);
    gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,5);



	return window;
}




int on_button_entry3(GtkWidget *button,gpointer data)//注册辨识按钮
{
  gtk_widget_hide(data);
  gboolean isconnected = FALSE;
  const gchar *username = gtk_entry_get_text(GTK_ENTRY(entry1)); 
  const gchar *servip   = gtk_entry_get_text(GTK_ENTRY(entry5));
  //const gchar *passwd = (const gchar *)data;
  const gchar *passwd = gtk_entry_get_text(GTK_ENTRY(entry2));
  const gchar *pad = gtk_entry_get_text(GTK_ENTRY(entry3));
  char p1[20];
  char p2[20];
  strcpy(p1,pad);
  strcpy(p2,passwd);
  printf("pad = %s\n",pad);
  printf("passwd = %s\n",passwd);
  int dif = 0;
  if(strcmp(p1,p2) == 0){
    
    printf("the pasd is ok\n");
    printf("\n pad = %s\n",pad);
    printf("username = %s\n",username);
    user_t *user;
    user = (user_t *)malloc(sizeof(user_t));
    strcpy(user->username,username);
    strcpy(user->userpasd,passwd);
    user->previe = 0;
    //user->objip  = NULL;
    user->many   = 0;
    user->root   = 0;
    user->submit = 0;
    isconnected = trylink(username,passwd,1,servip);
    if(isconnected == FALSE){
             
        printf("the name is already exit\n");
        return 0;

    }else{
       
       printf("submit is successful !\n");
       sub_sucess();
       gtk_widget_show_all(data);
    }
   
   
    
    //choice_view(user,servip,sd); 
     
  }else{                                      //注册时两次输入的密码不相同
    printf("the password twice input is diffent");
    printf("\n pad = %s\n",pad);
    GtkWidget *window;
    GtkWidget *button;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"input error");
    gtk_window_set_default_size(GTK_WINDOW(window),300,300);
    g_signal_connect(G_OBJECT(window),"destory",
                     G_CALLBACK(gtk_widget_destroy),NULL);
    gtk_window_set_position(GTK_WINDOW(window),
                            GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window),40);
    button = gtk_button_new_with_label("twicw passd is wrong");
    g_signal_connect(G_OBJECT(button),"clicked",
                     G_CALLBACK(destroy),NULL);
    gtk_container_add(GTK_CONTAINER(window),button);
    gtk_widget_show_all(window);
    return 0;   

  }
  
}

void *test(void *arg);
int on_button_clicked(GtkWidget *button,gpointer data)     //登录函数，向服务器发送信息
{
    gboolean isconnected = FALSE;
   const gchar *username = gtk_entry_get_text(GTK_ENTRY(entry1));
   const gchar *password = gtk_entry_get_text(GTK_ENTRY(entry2));
   const gchar *servip   = gtk_entry_get_text(GTK_ENTRY(entry5));
    g_print("The name  :%s",username);
    g_print("\n");
    g_print("The password:%s",password);
    g_print("\n");
    isconnected = trylink(username,password,0,servip);
    //printf("link = %d\n",link);
    if(isconnected == FALSE){
        printf("login is error\n");
        return 0;
    }else{
        printf("login is sucess\n");
        gtk_widget_hide(data);
        user_t *user;
        user = (user_t *)malloc(sizeof(user_t));
        strcpy(user->username,username);
        strcpy(user->userpasd,password);
        user->previe = 0;
        //user->objip  = NULL;
        user->many   = 0;
        user->root   = 0;
        user->submit = 0;
        //formal_link(user,servip);
        //pthread_t tid;
        //pthread_create(&tid,NULL,test,NULL);
        List_Init(list_name,window_node_t);
        choice_view(user,servip,sd);    
    }
    
}

//void *test(void *arg);
void * test(void *arg)
{
    while(1){
        printf("i am the test thread\n");
        sleep(1);
    }
}


void sub_sucess()  //窗口关闭函数
{
        char buf[MAXBUF];
    	message_t message;
        strcpy(message.message,"qxff951124");
        strcpy(message.fname,local_name);
        message.type = DOWNLINE;
        memcpy(buf,&message,sizeof(message_t));
        send(sd,buf,sizeof(buf),0);            
        printf("the send is %d\n");
        gtk_main_quit ();
	
}



