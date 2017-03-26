/*************************************************************************
	> File Name: public.c
	> Author: 
	> Mail: 
	> Created Time: 2015年08月10日 星期一 21时31分08秒
 ************************************************************************/

#include<stdio.h>
#include"./public.h"
#include"./prive.h"
#include"./friend.h"
pthread_mutex_t mute = PTHREAD_MUTEX_INITIALIZER;

void showtalk_p(GtkButton *button,gpointer data){    //展示群聊窗口
     
      GtkWidget *window;
      printf("lalallalalalalla\n");
      window = private_t_p();
      gtk_widget_show_all(window);
      
}
    
void start_talk_p(GtkButton *button,gpointer data){   //开始群聊函数

    printf("kokokokokokoko\n");
  
    pthread_t thid;                       
    pthread_create(&thid,NULL,on_message_p,(void *)data);

}

GtkWidget *private_t_p(){              //创建群聊窗口
 
   GtkWidget *window;
   GtkWidget *vbox,*hbox,*button,*label,*view,*vbox1,*hbox1,*hbox2,*hbox3,*view2;
   GtkWidget *message_entry;  //变量局部化实验
   GtkTextBuffer *buffer,*buffer2;
   GtkWidget *text,*text2;
   GtkWidget *entry6;
   GtkWidget *login_button;
   GtkWidget *history     ;   
   val *data ;  //发送消息结构体变量
   data = (val *)malloc(sizeof(val));
   
   window = gtk_window_new(GTK_WINDOW_TOPLEVEL);//创建主窗口
   gtk_window_set_title(GTK_WINDOW(window),"cilect_P");
   g_signal_connect(G_OBJECT(window),"delete_event",
                     G_CALLBACK(BYBY_PB),(gpointer)window);
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
                    G_CALLBACK(show_online),NULL);

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

   //label = gtk_label_new("link");//创建一个标签
   //gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,5);//将标签加入H

   entry6 = gtk_entry_new();//输入需要聊天的目标姓名
   //gtk_box_pack_start(GTK_BOX(hbox),entry6,FALSE,FALSE,5);
   login_button = gtk_button_new_with_label("This is PUBLIC");//创建按钮，暂时没什么用
   gtk_box_pack_start(GTK_BOX(hbox),login_button,TRUE,TRUE,5);
   data->button = login_button;
   g_signal_connect(G_OBJECT(login_button),"clicked",
                    G_CALLBACK(start_talk_p),(gpointer)data);
   

   login_button = gtk_button_new_with_label("History");//创建按钮，暂时没什么用
   gtk_box_pack_start(GTK_BOX(hbox),login_button,TRUE,TRUE,5);
   data->button = login_button;
   g_signal_connect(G_OBJECT(login_button),"clicked",
                    G_CALLBACK(show_history_p),(gpointer)data);
   





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
                    G_CALLBACK(on_send_p),(gpointer)data);
 
    return window;
 }

void on_send_p(GtkButton *button,gpointer data) 
{  //向服务器发送数据
   //static GtkWidget *message_entry;

   GtkTextIter iter;
   val * test = (val*)data;
   message_t  message;
   char get_buf[1024];
   char buf[1024]    ;
   char objname[20]  ;
   
   const char *getmessage;
  
   
   getmessage = gtk_entry_get_text(GTK_ENTRY(test->message_entry));
   
   strcpy(message.message,getmessage);      //将消息写入结构体，且初始化消息结构体 
   strcpy(message.fname,local_name);
    
   message.type = 2;
   
   memcpy(buf,&message,sizeof(message_t));
   send(sd,buf,sizeof(buf),0);               //发送消息
   printf("the send is %s\n",message.message);
   sprintf(get_buf,"I: %s\n",message.message);//将输入写入缓冲区

   time_t timep;
   time(&timep);
   strcat(get_buf,ctime(&timep));
   char timeP[50];
   memset(timeP,0,sizeof(timeP));
   strcat(timeP,ctime(&timep));

   pthread_mutex_lock(&mute);
   gtk_text_buffer_get_end_iter(test->buffer,&iter);
   gtk_text_buffer_insert(test->buffer,&iter,get_buf,-1);
   add_hismessage(message,timeP);
   pthread_mutex_unlock(&mute);
   gtk_entry_set_text(GTK_ENTRY(test->message_entry),"");
     
}


void  * on_message_p(void *arg){   //接受群聊信息

      GtkTextIter iter;          //显示屏指针
      const char *ptemp;
      char objname[20];
      char get_buf[1024];        //显示屏缓冲区
      val * test = (val *)arg;   //结构体指针转换

      message_t  message;       
      signal_on_message = 1;
      printf("lalalalalallalalalalal\n");
     // memcpy(&message,get_com_buf,sizeof(message_t));
      //printf("the get :%s\n",message.message);
      window_list_t windo;
      List_Init(windo,window_node_t);
      strcpy(windo->data.name,"PUBLIC");
      List_AddHead(list_name,windo);  
      gtk_widget_set_sensitive(test->button,TRUE);    
      memset(get_com_buf,0,sizeof(get_com_buf));
      printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
      while(1){
         //printf("+++++++++++++++++++++\n");
          printf("the conmmon is %s\n",get_com_buf);
          if(signal_on_message == -1){               //结束接受线程机制
	 	window_list_t pos;
    		for(pos = list_name->next;pos != list_name;pos = pos->next){
			if(strcmp(pos->data.name,"PUBLIC") == 0){
				break;
  		 		}
    	       	}
    		List_DelNode(pos);

                  break;
            }
        if(strlen(get_com_buf)!= 0){
           printf("the get_com_buf is %s\n",get_com_buf);
	   memcpy(&message,get_com_buf,sizeof(message_t));
            printf("the message buf is %d\n",message.type);
            if(message.type == 7){
                 
                char friend[50];
                printf("lalalalalalllllllllllllllllllll\n");
                strcpy(friend,message.oname);
                strcat(friend,":");
                strcat(friend,message.message);
                strcat(friend,"\n");
         
                pthread_mutex_lock(&mute);
            	gtk_text_buffer_get_end_iter(test->buffer_f,&iter);
            	gtk_text_buffer_insert(test->buffer_f,&iter,friend,-1);
                memset(get_com_buf,0,sizeof(get_com_buf));
            	pthread_mutex_unlock(&mute);
                continue;
            }
           
           
           if(message.type == 2){       
                printf("lalalalallalal\n");
                sprintf(get_buf,"%s: %s\n",message.fname,message.message);//将输入写入显示屏缓冲区
                char timetp[50];
                memset(timetp,0,sizeof(timetp));
                time_t timep;
                time(&timep);
                strcat(get_buf,ctime(&timep));
                strcat(timetp,ctime(&timep));
                //message.pub = 1    ;
                //add_hismessage(message,timetp);
                

            	pthread_mutex_lock(&mute);
            	gtk_text_buffer_get_end_iter(test->buffer,&iter);
            	gtk_text_buffer_insert(test->buffer,&iter,get_buf,-1);
                memset(get_com_buf,0,sizeof(get_com_buf));
                 add_hismessage(message,timetp);
            	pthread_mutex_unlock(&mute);
                continue;
            }
         }  
	sleep(1);        
       } 
} 

int show_online(GtkButton *button,gpointer data){   //展示当前在线人员
    
     char buf[MAXBUF];
     message_t message;
     message.type = SHOWONLINE;
     strcpy(message.fname,local_name);
     strcpy(message.oname,"server");
     strcpy(message.message,"SHOWONLINE");
     memcpy(buf,&message,sizeof(message_t));
    
     send(sd,buf,sizeof(buf),0);     


}


void show_history_p(GtkButton *button,gpointer data){    //展示历史消息窗口
      
    GtkWidget *window;
    
    window = history_p();
    
    gtk_widget_show_all(window);
}



GtkWidget *history_p(){                           //创建历史消息窗口
   
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
   
  // hm->view   = view    ;
   hm->buffer = buffer  ;
   //hm->text   = text    ;
   //hm->entry  = data    ;
   
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
                    G_CALLBACK(show_history_message_p),(gpointer)hm);
   
   return window;
}

int  show_history_message_p(GtkButton *button,gpointer data){  //展示历史消息
    

    //printf("the first ________________________\n");
    his_message_t *test;
    test = (his_message_t *)data;
    GtkTextIter iter;
   
    //printf("the second _______________________\n");
    const char *temp;
    //temp = gtk_entry_get_text(GTK_ENTRY(test->entry));
    char gname[10];
    //strcpy(gname,temp);
    //printf("the third _________________________\n");
    /*while(1){
    printf("the four __________________________\n");
         printf("the gname is %s\n",gname);
         sleep(1);
    }    
    printf("the five___________________________\n");
    */

    char tes[30];
    strcpy(tes,"./user/");
    strcat(tes,local_name);




    FILE *fp = fopen(tes, "rb+");
	if (NULL == fp) {
		printf("Cannot open file %s!\n", tes);
		return 0;
	}

	hismessage_t buf;
	int found = 0;
        
        char gb[MAXBUF];
	while (!feof(fp)) {
        //printf("i am in fp\n");
         
		if (fread(&buf, sizeof(hismessage_t), 1, fp)) {
	              	      if(buf.pub == 1){
                                  printf("the buf.pub is %d\n",buf.pub);

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



