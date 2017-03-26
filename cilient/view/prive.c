/*************************************************************************
	> File Name: prive.c
	> Author: 
	> Mail: 
	> Created Time: 2015年08月06日 星期四 02时53分16秒
 ************************************************************************/

#include<stdio.h>
#include"./prive.h"
#include"../common/common.h"
#define OUTPORT 8003        //定义端口号



//static GtkWidget *text;      //文本构件
//显示对话内容的文本显示缓冲区
 //显示输入消息的单行陆入控件
//输入用户名的单行控件
//static GtkWidget *login_button;//链接按钮
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//全局的一个锁，专门为线程准备
//static GtkWidget *entry6;
//static GtkWidget *name_entry;

void BYBY_p( GtkWidget *widget, gpointer data ){
    ((val *)data)->sig = 1;
    
    gtk_widget_hide(data);
}


void BYBY_H(GtkWidget *widget, gpointer data){

   /*const char *ptemp ;
   char  off_name[30];
   printf("111111111111111111111111111111111111\n");
   ptemp = gtk_entry_get_text(GTK_ENTRY(data));
   printf("444444444444444444444444444444444444\n");
   
   strcpy(off_name,ptemp);
   printf("the off name is %s\n",off_name);
   printf("555555555555555555555555555555555555\n");
   window_list_t pos;
   printf("444444444444444444444444444444444444\n");
   for(pos = list_name->next;pos != list_name;pos = pos->next){
                if(strcmp(pos->data.name,off_name) == 0){
                        break;
               }
    }
   printf("22222222222222222222222222222222222222\n");
   List_DelNode(pos);
   printf("3333333333333333333333333333333333333\n");
  */
    
    gtk_widget_destroy(data);
   
}




pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//gboolean isconnected = FALSE;
void *get_message(void *arg)//读取服务器数据线程（主函数）
{
    //GtkTextIter iter;
    //char get_buf[1024];
    char buf[1024];
    //message_t message;
    // last_mess_get();
    printf("i check the receve message ...............\n");
    while(recv(sd,buf,sizeof(buf),0))
    {
        message_t message;
        //printf(" i get message :%s\n",buf);
        memcpy(get_com_buf,buf,sizeof(buf));
        
        memcpy(&message,get_com_buf,sizeof(get_com_buf));
        if(message.type == 4 && (strcmp(message.message,"GIVE") == 0)){   //独立于其它模块首先辨识是不是文件传输
                
                strcpy(getname,message.file.name);
                strcpy(whogive,message.fname);
                memset(get_com_buf,0,sizeof(get_com_buf));

        }else if(message.type == 4 && (strcmp(message.message,"RECV") == 0)){
		
                file = 1;
                memset(get_com_buf,0,sizeof(get_com_buf));
        }              
                   
        sleep(1);
        
        
    }
}

void  * on_message(void *arg){       //接受信息线程函数

      GtkTextIter iter;          //显示屏指针
      GtkTextIter start,end;
      const char *ptemp;
      char objname[20];
      char get_buf[1024];        //显示屏缓冲区
      val * test = (val *)arg;   //结构体指针转换

      last_mess_get();           //尝试获取离线消息

      message_t  message;       
      ptemp = gtk_entry_get_text(GTK_ENTRY(test->name_entry));
      memcpy(&message,get_com_buf,sizeof(message_t));
      printf("the get :%s\n",message.message);
      printf("the type is %d\n",message.type);
      window_list_t window;
      List_Init(window,window_node_t);
      strcpy(window->data.name,ptemp);
      List_AddHead(list_name,window);      
      

      while(1){
        /*if(test->sig == 1){
            break;
        }*/
       //printf("lalalalalalalala\n");
        if(strlen(get_com_buf )!= 0){
            printf("nanananananananna\n");
	    memcpy(&message,get_com_buf,sizeof(message_t));
            //printf("the buf recv is %s\n",message.message);
            int i = -1;
            int p = -1;
            printf("the type is %d\n",message.type);
           if(message.type == 2){
            p = find_public();
            if(p == 0){                                     //处理有群聊消息发送过来，但是没有打开群聊窗口的情况
                char temp[1024];
                strcpy(temp,"You got a PUBLIC message!\n");
                strcat(temp,message.fname);
                strcat(temp,":");
                strcat(temp,message.message);
                strcat(temp,"\n");

                time_t timepb;
                time(&timepb);
                //memset(temp,0,sizeof(temp));
                strcat(temp,ctime(&timepb));
                //message.pub = 1;                
                add_hismessage(message,temp);
                
                pthread_mutex_lock(&mutex);
            	gtk_text_buffer_get_end_iter(test->buffer,&iter);
            	gtk_text_buffer_insert(test->buffer,&iter,temp,-1);
                memset(get_com_buf,0,sizeof(get_com_buf));
		//add_hismessage(message,temp);
            	pthread_mutex_unlock(&mutex);
                continue ;
                
               }
            }
	    if(message.type == 11){
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





            if(message.type == 6 || message.type == 8){
                 if(message.type == 6){
                	char friend[50];
                	strcpy(friend,message.oname);
                	strcat(friend,":");
                	strcat(friend,message.fname);
                	strcat(friend,"\n");
         
                	pthread_mutex_lock(&mutex);
            		gtk_text_buffer_get_end_iter(test->buffer_f,&iter);
            		gtk_text_buffer_insert(test->buffer_f,&iter,friend,-1);
                	memset(get_com_buf,0,sizeof(get_com_buf));
            		pthread_mutex_unlock(&mutex);
                	continue ;
                 }
                 if(message.type == 8){
                        char time[50];
                	strcpy(time,"--");
                        strcat(time,message.message);
                	strcat(time,"--\n");
         
                	pthread_mutex_lock(&mutex);
            		gtk_text_buffer_get_end_iter(test->buffer_f,&iter);
            		gtk_text_buffer_insert(test->buffer_f,&iter,time,-1);
                	memset(get_com_buf,0,sizeof(get_com_buf));
            		pthread_mutex_unlock(&mutex);
                	continue ;
                 }


            }
           
            i = find_byname(message.fname);
            if(i == 0 && message.type != 2 && message.type != 6 && message.type != 7  ){                //处理当有人发来消息，但是目标客户端并没有打开对应的窗口的情况
            	char temp[1024];
                strcpy(temp,"You got a new message!\n");
                strcat(temp,message.fname);
                strcat(temp,":");
                strcat(temp,message.message);
                strcat(temp,"\n");
                
                time_t timen;
                time(&timen);
                strcat(temp,ctime(&timen));
                
                char timeN[50];
                memset(timeN,0,sizeof(timeN));
                strcat(timeN,ctime(&timen));
                //add_hismessage(message,timeN);

                pthread_mutex_lock(&mutex);
            	gtk_text_buffer_get_end_iter(test->buffer,&iter);
            	gtk_text_buffer_insert(test->buffer,&iter,temp,-1);
                memset(get_com_buf,0,sizeof(get_com_buf));
		add_hismessage(message,timeN);
            	pthread_mutex_unlock(&mutex);
                continue;
                  
	    }
           //将输入写入显示屏缓冲区
            strcpy(objname,ptemp);
            //printf("the local name:%s ,the objname:%s\n",local_name,objname);
            //strcpy(objname,local_name);
            time_t timep; 
            time(&timep); 
            printf("%s\n",ctime(&timep));
            //strcat(get_buf,ctime(&timep));
            if((strcmp(message.fname,objname) == 0) && (message.type == 1)){         //只显示与其单个私聊的人发送的信息 
                char gettime[50];
                memset(gettime,0,sizeof(gettime));              ///////////////////////////////
                strcat(gettime,ctime(&timep));
                int AAA;
                 printf("the recv is %s : %s \n",message.fname,message.message);
               // AAA = add_hismessage(message,gettime);
                //printf("the AAA is %d\n",AAA);
                printf("after add_mess _____________________\n");
               // printf("the recv is %s : %s \n",message.fname,message.message);
                sprintf(get_buf,"%s: %s\n",message.fname,message.message);
                strcat(get_buf,ctime(&timep));
                printf("check the write>>>>>>>>>>>>>>>>>>>>.\n");
            	pthread_mutex_lock(&mutex);
            	gtk_text_buffer_get_end_iter(test->buffer,&iter);
            	gtk_text_buffer_insert(test->buffer,&iter,get_buf,-1);
                memset(get_com_buf,0,sizeof(get_com_buf));
                add_hismessage(message,gettime);
            	pthread_mutex_unlock(&mutex);
                continue;
            }
            
         }
	sleep(1);         
       } 
} 


gboolean do_connect(void)
{
 }


void on_destory(GtkWidget *widget,GdkEvent *event,gpointer data)
{//关闭当前窗口执行
    sprintf(username,"gust");
    if(do_connect() == TRUE)
    {
        pthread_t thid;
        //gtk_widget_set_sensitive(login_button,FALSE);
        pthread_create(&thid,NULL,get_message,NULL);
    }
    gtk_widget_destroy(widget);
}

void on_button_clicke(GtkButton *button,gpointer data)
{   //当点击链接按钮时执行
    const char * name;
     
    name = gtk_entry_get_text(GTK_ENTRY(name_entry));
    sprintf(username,"%s",name);
    if(do_connect()){
        pthread_t thid;
        //gtk_widget_set_sensitive(login_button,FALSE);
        pthread_create(&thid,NULL,on_message,NULL);
    }
    gtk_widget_destroy(data);
}


void create_win(void)

{
    //创建登录窗口
    GtkWidget *win,*vbox;
    GtkWidget *button;

    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(win),"please name");
    gtk_container_set_border_width(GTK_CONTAINER(win),10);
    g_signal_connect(G_OBJECT(win),"delete_event",
                     G_CALLBACK(on_destory),NULL);
    gtk_window_set_modal(GTK_WINDOW(win),TRUE);
    gtk_window_set_position(GTK_WINDOW(win),GTK_WIN_POS_CENTER);

    vbox = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(win),vbox);
    name_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox),name_entry,TRUE,TRUE,5);

    button = gtk_button_new_from_stock(GTK_STOCK_OK);
    g_signal_connect(G_OBJECT(button),"clicked",
                    G_CALLBACK(on_button_clicke),win);
    gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,5);

    gtk_widget_show_all(win);
}



void on_send(GtkButton *button,gpointer data)
{  //向服务器发送数据
   //static GtkWidget *message_entry;

   GtkTextIter iter;
   val * test = (val*)data;
   message_t  message;
   char get_buf[1024];
   char buf[1024]    ;
   char objname[20]  ;
   
   const char *getmessage;
   const char *ptemp ;
   
   
   getmessage = gtk_entry_get_text(GTK_ENTRY(test->message_entry));
   ptemp = gtk_entry_get_text(GTK_ENTRY(test->name_entry));
   strcpy(objname,ptemp);

   strcpy(message.message,getmessage);      //将消息写入结构体，且初始化消息结构体 
   strcpy(message.fname,local_name);
   strcpy(message.oname,objname);
    

   message.type = 1;
   
   memcpy(buf,&message,sizeof(message_t));
   send(sd,buf,sizeof(buf),0);               //发送消息
   printf("the send is %s\n",message.message);
   sprintf(get_buf,"I: %s\n",message.message);//将输入写入缓冲区

   time_t times; 
   time(&times);

   //strcat(gettime,ctime(&timep));
   strcat(get_buf,ctime(&times));
   char timet[50];
   strcat(timet,ctime(&times));
   add_hismessage(message,timet);
   pthread_mutex_lock(&mutex);
   gtk_text_buffer_get_end_iter(test->buffer,&iter);
   gtk_text_buffer_insert(test->buffer,&iter,get_buf,-1);
   pthread_mutex_unlock(&mutex);
   gtk_entry_set_text(GTK_ENTRY(test->message_entry),"");
    //gtk_entry_set_text(GTK_ENTRY(message_entry),"");
    //清除单行录入的文字
}

void on_login(GtkWidget *button,gpointer data)
{
    //点击登录按钮执行，显示输入名称等信息
    create_win();
}


void on_delete_event(GtkWidget *widget,GdkEvent *event,gpointer data)
{
    //关闭窗口时主动执行，关闭主窗口
    close(sd);
    gtk_main_quit();
}





GtkWidget *private_t_n()      //私聊主要交互界面创建函数
{
   GtkWidget *window;
   GtkWidget *vbox,*hbox,*button,*label,*view,*vbox1,*hbox1,*hbox2,*hbox3,*view2;
   GtkWidget *message_entry;  //变量局部化实验
   GtkTextBuffer *buffer,*buffer2;
   GtkWidget *text,*text2;
   GtkWidget *entry6;
   GtkWidget *login_button;   
   val *data ;  //发送消息结构体变量
   data = (val *)malloc(sizeof(val));
   
  
   data->sig = 0;
   entry6 = gtk_entry_new();
   window = gtk_window_new(GTK_WINDOW_TOPLEVEL);//创建主窗口
   gtk_window_set_title(GTK_WINDOW(window),"cilect_P");
   g_signal_connect(G_OBJECT(window),"delete_event",
                    G_CALLBACK(BYBY_H),(gpointer)window);
   gtk_window_set_default_size(GTK_WINDOW(window),400,600);
   gtk_container_set_border_width(GTK_CONTAINER(window),10);
   
   hbox1 = gtk_hbox_new(FALSE,0);
   gtk_container_add(GTK_CONTAINER(window),hbox1);//创建最大的总装盒子

   
   vbox = gtk_vbox_new(FALSE,0);//创建左边部分的总装盒子
   gtk_box_pack_start(GTK_BOX(hbox1),vbox,FALSE,FALSE,10);


   vbox1 = gtk_vbox_new(FALSE,0);//创建右边部分的总装盒子
   gtk_box_pack_start(GTK_BOX(hbox1),vbox1,FALSE,FALSE,10);

   hbox2 = gtk_hbox_new(FALSE,0);//左边盒子的分盒子
   gtk_box_pack_start(GTK_BOX(vbox1),hbox2,FALSE,FALSE,10);

   label = gtk_label_new("your ");//右边盒子的两个标签
   gtk_box_pack_start(GTK_BOX(hbox2),label,TRUE,TRUE,10);
   label = gtk_label_new(" friends");
   gtk_box_pack_start(GTK_BOX(hbox2),label,TRUE,TRUE,10);

   
   view2 = gtk_scrolled_window_new(NULL,NULL);//显示好友信息
   gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(view2),
            GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
   text2 = gtk_text_view_new();//好友信息接受框
   gtk_box_pack_start(GTK_BOX(vbox1),view2,TRUE,TRUE,5);//向盒子加入视图
   gtk_container_add(GTK_CONTAINER(view2),text2);//将文本框加入视图
   buffer2 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text2)); //buffer接受文本框信息    
   data->buffer_f = buffer2;
   data->text_f   = text2  ;
   
  
   hbox3 = gtk_hbox_new(FALSE,0);//创建左边盒子的盒子部件
   gtk_box_pack_start(GTK_BOX(vbox1),hbox3,FALSE,FALSE,10);
   
   button = gtk_button_new_with_label(" F5");//更新好友列表
   gtk_box_pack_start(GTK_BOX(hbox3),button,FALSE,FALSE,5);
   g_signal_connect(G_OBJECT(button),"clicked",
                    G_CALLBACK(f_show_friend),(gpointer)data);

   button = gtk_button_new_with_label("Add");//添加好友
   gtk_box_pack_start(GTK_BOX(hbox3),button,FALSE,FALSE,5);
   g_signal_connect(G_OBJECT(button),"clicked",
                    G_CALLBACK(show_add_friend),NULL);

   button = gtk_button_new_with_label("Del");//删除好友
   gtk_box_pack_start(GTK_BOX(hbox3),button,FALSE,FALSE,5);
   g_signal_connect(G_OBJECT(button),"clicked",
                    G_CALLBACK(show_del_friend),NULL);
   
   hbox = gtk_hbox_new(FALSE,0);//创建第二个盒子H
   gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,5);//H->V


   //entry6 = gtk_entry_new();//输入需要聊天的目标姓名
   button = gtk_button_new_with_label("history");//创建一个标签
   gtk_box_pack_start(GTK_BOX(hbox),button,TRUE,TRUE,5);//将标签加入H
   g_signal_connect(G_OBJECT(button),"clicked",
                    G_CALLBACK(show_history),(gpointer)entry6);          //历史消息传参

   /*const char *temp;
   temp = gtk_entry_get_text(GTK_ENTRY(entry6));
   char gname[10];
   strcpy(gname,temp);
   printf("the third _________________________\n");
 
   printf("the four __________________________\n");
         printf("the gname is %s\n",gname);*/
       
 
   

   //entry6 = gtk_entry_new();//输入需要聊天的目标姓名
   gtk_box_pack_start(GTK_BOX(hbox),entry6,FALSE,FALSE,5);
   login_button = gtk_button_new_with_label("Start");//创建按钮，暂时没什么用
   data->button = login_button;
   gtk_box_pack_start(GTK_BOX(hbox),login_button,FALSE,FALSE,5);
   g_signal_connect(G_OBJECT(login_button),"clicked",
                    G_CALLBACK(start_talk),(gpointer)data);
     //g_signal_connect(G_OBJECT(window),"delete_event",
                    //G_CALLBACK(BYBY_H),(gpointer)entry6);   //test.................
   data->name_entry = entry6;
   view = gtk_scrolled_window_new(NULL,NULL);//创建滑动窗口，显示收发信息
   gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(view),
            GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
   text = gtk_text_view_new();//创建文本框
   gtk_box_pack_start(GTK_BOX(vbox),view,TRUE,TRUE,5);//加入v
   gtk_container_add(GTK_CONTAINER(view),text);//将文本加入视图
   buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text));
   
    
    data->buffer = buffer; //传递参数缓冲区
    
    data->text   = text  ;  //传递参数文本框
    
    hbox = gtk_hbox_new(FALSE,0);//创建第左边的盒子组件
    gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,5);//将H->V
    label = gtk_label_new("input:");//发送信息相关部分开始
    gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,5);
    message_entry = gtk_entry_new();//输入文本框，是为局部变量，可以实现在线一对多私人聊天
    data->message_entry = message_entry;
    gtk_box_pack_start(GTK_BOX(hbox),message_entry,FALSE,FALSE,5);
    //向结构体传入输入需要发送的信息。
    //printf("111111111111111111111111111\n");
    button = gtk_button_new_with_label("goon");//发送按钮
    //printf("111111111111111111111111112\n");
    gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,5);
    g_signal_connect(G_OBJECT(button),"clicked",
                    G_CALLBACK(on_send),(gpointer)data);
 
    return window;
 }


void start_talk(GtkButton *button,gpointer data){    //开始聊天

    printf("kokokokokokoko\n");
    int status;
    val *test = (val *)data;
    pthread_t thi;  
     char name[10];
    strcpy(name,"hello");
    gtk_widget_set_sensitive(test->button,FALSE);
    g_thread_new(name,on_message,(gpointer)data); 
    printf("OOOOOOOOOOOOOOO\n");                     
    //pthread_create(&thi,NULL,on_message,(void *)data);
    //pthread_join(thi,(void *)&status);

}


void showtalk(GtkButton *button,gpointer data){     //展示私人聊天函数
     
      GtkWidget *window;
      printf("lalallalalalalla\n");
      window = private_t_n();
      gtk_widget_show_all(window);
      
}

int find_byname(char *fname){           //查找当前是否有注册窗口
     window_list_t pos;
     for(pos = list_name->next;pos != list_name;pos = pos->next){
		//printf("the open window is %s\n",pos->data.name);
           if(strcmp(fname,pos->data.name) == 0){
                    printf("check find_byname\n");
                    return 1;
              }
    
     }
     return 0;
}



int find_public(){              //查找是否有PUBLIC窗口打开
     window_list_t pos;
     char pb[20];
     strcpy(pb,"PUBLIC");
     for(pos = list_name->next;pos != list_name;pos = pos->next){
           
           if(strcmp(pos->data.name,pb) == 0){
              
                    return 1;
              }
    
     }
     return 0;
}



void show_history(GtkButton *button,gpointer data){    //展示历史消息窗口
      
    GtkWidget *window;
    
    window = history(data);
    
    gtk_widget_show_all(window);
}



GtkWidget *history(gpointer data){                           //创建历史消息窗口
   
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *text  ;
    GtkWidget *view  ;
    GtkWidget *box   ;
    GtkTextBuffer *buffer;
    
    his_message_t *hm;
    hm = (his_message_t *)malloc(sizeof(his_message_t));

   window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(window),"show history message");
   g_signal_connect(G_OBJECT(window),"delete_event",
                     G_CALLBACK(BYBY_p),(gpointer)window);
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
   
   hm->view   = view    ;
   hm->buffer = buffer  ;
   hm->text   = text    ;
   hm->entry  = data    ;
   
   /*const char *temp;
   temp = gtk_entry_get_text(GTK_ENTRY(data));
   char gname[10];
   strcpy(gname,temp);
   printf("the third _________________________\n");
   while(1){
   printf("the four __________________________\n");
         printf("the gname is %s\n",gname);
         sleep(1);
   }*/

   
   button = gtk_button_new_with_label("show me the history message");          //显示历史消息
   gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,5);
   g_signal_connect(G_OBJECT(button),"clicked",
                    G_CALLBACK(show_history_message),(gpointer)hm);
   
   return window;
}

int show_history_message(GtkButton *button,gpointer data){  //展示历史消息
    

    //printf("the first ________________________\n");
    his_message_t *test;
    test = (his_message_t *)data;
    GtkTextIter iter;
    //printf("the second _______________________\n");
    const char *temp;
    temp = gtk_entry_get_text(GTK_ENTRY(test->entry));
    char gname[10];
    strcpy(gname,temp);
    //printf("the third _________________________\n");
    /*while(1){
    printf("the four __________________________\n");
         printf("the gname is %s\n",gname);
         sleep(1);
    }    
    printf("the five___________________________\n");
    */
    strcpy(mess_name,"./user/");
    strcat(mess_name,local_name);
    FILE *fp = fopen(mess_name, "rb+");
	if (NULL == fp) {
		printf("Cannot open file %s!\n", mess_name);
		return 0;
	}

	hismessage_t buf;
	int found = 0;
        
        char gb[MAXBUF];
	while (!feof(fp)) {
        //printf("i am in fp\n");
         
		if (fread(&buf, sizeof(hismessage_t), 1, fp)) {
	              if(strcmp(gname,buf.oname) == 0 || strcmp(gname,buf.fname) == 0){	      
                     		sprintf(gb,"%s:%s\n%s\n",buf.fname,buf.message,buf.time);
                     		gtk_text_buffer_get_end_iter(test->buffer,&iter);
            	     		gtk_text_buffer_insert(test->buffer,&iter,gb,-1);
		     		memset(gb,0,sizeof(gb));
                      }
		}
	}
	fclose(fp);
	return 0;
}

int add_hismessage(message_t message,char *time){   //记录接收到的信息

        printf("add_mess _________________first\n");
        hismessage_t buf;
        strcpy(buf.fname,message.fname);
        strcpy(buf.oname,message.oname);
        strcpy(buf.message,message.message);
        strcpy(buf.time,time);
        if(message.type == 2){
           buf.pub = 1;
        }
        
        strcpy(mess_name,"./user/");
        strcat(mess_name,local_name);
        printf("add_mess _________________sencond\n");
	FILE *fp = fopen(mess_name, "ab+");
	int rtn = 0;
	if (NULL == fp) {
		printf("Cannot open file %s!\n",mess_name);
		return -1;
	}

	rtn = fwrite(&buf, sizeof(hismessage_t), 1, fp);
        printf("add_mess ____________________third\n");
	fclose(fp);
        printf("add_mess ____________________four\n");
        return 0;	
}


void last_mess_get(){
  
    message_t message;
    char buf[1024];
    strcpy(message.fname,local_name);
    message.type = 9;
    memcpy(buf,&message,sizeof(message_t));
    send(sd,buf,sizeof(buf),0);
 
}



