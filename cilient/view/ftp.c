/*************************************************************************
	> File Name: ftp.c
	> Author: 
	> Mail: 
	> Created Time: 2015年08月12日 星期三 21时54分47秒
 ************************************************************************/

#include<stdio.h>
#include"./ftp.h"
#include<gtk/gtk.h>

pthread_cond_t    cond;         //一个条件变量用来阻塞

void showFTP(GtkButton *button,gpointer data){   //显示FTP主窗口
      
      GtkWidget *window;
      printf("lalallalalalalla\n");
      window = ftp();
      gtk_widget_show_all(window);
      
}


GtkWidget* ftp( )   //ftp 主窗口创建函数
{
	GtkWidget *window;
        GtkWidget *vbox  ;
	GtkWidget *button;
        GtkWidget *entry ;
        GtkWidget *text  ;
        GtkWidget *view  ;
        GtkTextBuffer *buffer;
	
        file_t *data;
        data = (file_t *)malloc(sizeof(file_t));

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);       //构建主窗口
	g_signal_connect(G_OBJECT(window),"delete_event",
                     G_CALLBACK(BYBY),window);
        gtk_window_set_default_size(GTK_WINDOW(window),400,300);
        gtk_container_set_border_width(GTK_CONTAINER(window),10);
	gtk_window_set_title(GTK_WINDOW(window),"choice dir & files");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	
        data->window = window;

        vbox = gtk_vbox_new(FALSE,0);
        gtk_container_add(GTK_CONTAINER(window),vbox);

	button = gtk_button_new_with_label("choice file and dir");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(on_button_c),NULL);
	gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,10);
        
        view = gtk_scrolled_window_new(NULL,NULL);//创建滑动窗口，显示选择的文件
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(view),
            	GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
        text = gtk_text_view_new();//创建文本框
        gtk_box_pack_start(GTK_BOX(vbox),view,FALSE,FALSE,10);//加入
        gtk_container_add(GTK_CONTAINER(view),text);//将文本加入视图
        buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text));//确定缓冲区和文本的关系

        button = gtk_button_new_with_label("confirmed");   //确认传送文件名
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(sure_file),(gpointer)buffer);
	gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,10);

        
        entry = gtk_entry_new();                       //获取文件传送目标名
        gtk_box_pack_start(GTK_BOX(vbox),entry,FALSE,FALSE,10);
        
        data->entry = entry;

        button = gtk_button_new_with_label("send");       //发送按钮
	gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,10);
        g_signal_connect(G_OBJECT(button),"clicked",
                    G_CALLBACK(send_file_f),(gpointer)data);
        
        button = gtk_button_new_with_label("recv");        //接受按钮
	gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,10);
        g_signal_connect(G_OBJECT(button),"clicked",
                    G_CALLBACK(recv_file),NULL);

	return window;
}    


void on_button_c (GtkWidget *button,gpointer userdata)  //弹出选择文件的窗口
{
	GtkWidget* dialog ;
	dialog = gtk_file_selection_new("choice a file & dir:");
	gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
	gtk_signal_connect(GTK_OBJECT(dialog),"destroy",GTK_SIGNAL_FUNC(gtk_widget_destroy),&dialog);
	gtk_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(dialog)->ok_button),"clicked",GTK_SIGNAL_FUNC(on_file_select_ok),GTK_FILE_SELECTION	(dialog));
	gtk_signal_connect_object(GTK_OBJECT(GTK_FILE_SELECTION(dialog)->cancel_button),
 	"clicked",GTK_SIGNAL_FUNC(gtk_widget_destroy),
	GTK_OBJECT(dialog));
	gtk_widget_show(dialog);
}

void on_file_select_ok (GtkWidget *button,gpointer data)   //选择一个文件窗口函数
{
	GtkWidget *dialog;
	gchar message[1024];
	const gchar *filename;
        
	filename = gtk_file_selection_get_filename(data);
   
	if(g_file_test(filename,G_FILE_TEST_IS_DIR))
		sprintf(message,"You choice dir:%s",filename);
	else
		sprintf(message,"You choice file:%s",filename);

        strcpy(filenames,filename);

	dialog = gtk_message_dialog_new(NULL,GTK_DIALOG_DESTROY_WITH_PARENT,
		GTK_MESSAGE_INFO,GTK_BUTTONS_OK,message,NULL);
	gtk_widget_destroy(GTK_WIDGET(data));
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}

void sure_file(GtkWidget *button,gpointer data){   //确认发送文件名函数
            
	char buf[100];
        printf("the filenames is %s\n",filenames);
        strcpy(buf,filenames);
        strcat(buf,"\n");
        GtkTextIter iter;
        gtk_text_buffer_get_end_iter(data,&iter);
        gtk_text_buffer_insert(data,&iter,buf,-1); 
}      

void send_file_f(GtkWidget *button,gpointer data){    //发送文件先遣信息
       
        const char *yname;
        char tname[100];
        char oname[20] ;
        char buf[MAXBUF];
        int i,j;
        file_t *test = (file_t *)data;
        //gtk_widget_hide(test->window);
        char tests[30];
        yname = gtk_entry_get_text(GTK_ENTRY(test->entry));
        strcpy(tests,yname);
        printf(" the test is %s\n",tests);
        strcpy(tname,filenames);
        for(i = 0,j = 0; i < strlen(tname);i++){
            if(tname[i] == '/'){
                j = 0;
                continue;
             }
            oname[j++] = tname[i];
        }
        oname[j] = '\0';
        printf("LLLLLLLLLLLLLLLLLLLLL\n");
        message_t   message;
        strcpy(message.oname,yname);
        strcpy(message.fname,local_name);
        strcpy(message.message,"GIVE");
        strcpy(message.file.name,oname);
        printf("the file message is %s\n",message.file);
        message.type = 4 ;
        memcpy(buf,&message,sizeof(message_t));
        send(sd,buf,sizeof(buf),0);
        
        strcpy(ftp_tname , tname);  //绝对路径
        strcpy(ftp_oname , oname);  //文件名
        strcpy(ftp_yname , yname);   //发送目标名
        
        
        pthread_t thid;
        int status;
        pthread_create(&thid,NULL,temp_file,NULL);   //创建发送线程
        pthread_join(thid,(void *)&status);
}


void * temp_file(void * arg){    //准备开始传送文件函数
        
   
       
       printf("the name is %s\n",ftp_yname);
       while(1){
              if(file == 1){
                  send_file(ftp_tname,ftp_oname,ftp_yname);
                  
                  break;
              }
            sleep(2);
       }
}


void send_file(char *tname,char *oname,char *yname){  //发送文件函数
    int fd;
    int len;
    fd = open(tname, O_RDONLY);
    char buff[800];
    char buf[MAXBUF];
    message_t message;
    //FILE *fp = fopen(tname, "r"); 
     //ff = open("hello",O_CREAT|O_EXCL|O_RDWR,S_IRWXU);
    //FILE *ff = fopen("hello","w");
    while((len =read(fd, buff, sizeof(buff))) >0){     //发送文件
      //while((len = fread(buff, 1, sizeof(buff), fp)) >0){
        strcpy(message.oname,yname);
        strcpy(message.fname,local_name);
        memcpy(message.message,buff,sizeof(buff));
        strcpy(message.file.name,oname);
        message.type = FILESOME;
        message.file.flag = 1;
        message.file.len = len;
        printf("the file is %d\n",len);
        memcpy(buf,&message,sizeof(message_t));
        int a;
        a = send(sd, buf, sizeof(buf) ,0);
        memset(buff,0,sizeof(buff));
        printf("the file is %d\n",a);
        //write(ff,buff,sizeof(buff));
         //fwrite(buff, 1,sizeof(buff), ff);
        
  
    }
        strcpy(message.oname,yname);                  //文件传送完毕后发送一个完毕的消息给对方
        strcpy(message.fname,local_name);
        strcpy(message.message,"EOFF");
        strcpy(message.file.name,oname);
        message.file.flag = 1;
        message.type = FILESOME;
        memcpy(buf,&message,sizeof(message_t));
        send(sd, buf, sizeof(buf) ,0);
        close(fd);
        //close(ff);
        file = -1; 
}

       
void recv_file(GtkWidget *button,gpointer data){   //接受文件函数
      
       message_t message;
       char buf[MAXBUF];

       if(strlen(getname) != 0){
	     strcpy(message.message,"RECV");
             strcpy(message.oname,whogive);
             strcpy(message.fname,local_name);
             message.type = 4;
             
             memcpy(buf,&message,sizeof(message_t));
             send(sd,buf,sizeof(buf),0);
              
             pthread_t thid ;
             pthread_create(&thid,NULL,recv_file_get,NULL);  //创建接受文件线程
             
        }
}            
     
void * recv_file_get(void *arg){     //接受文件函数
        
       int  fd;
       
       char buf[MAXBUF];
       message_t message;
       printf("the message is %s\n",getname);
       fd = open(getname,O_CREAT|O_EXCL|O_RDWR,S_IRWXU);
       
       //FILE *fp = fopen(getname, "w");
       if(fd == -1){
          printf("create file is error!:%d\n",__LINE__);
       }
       
       while(1){
             memcpy(&message,get_com_buf,sizeof(get_com_buf));
             if(message.type == 4 && message.file.flag == 1){    //当接受完成文件后，结束
             	if(strcmp(message.message,"EOFF") == 0){
                  	printf("i got the file\n");
                        memset(get_com_buf,0,sizeof(get_com_buf));
                  	close(fd);
                  	break;
             	}
             	int len;
             	//len = write(fd,message.message,message.file.len);
                len = write(fd,message.message,message.file.len);
                //fwrite(message.message, sizeof(char),message.file.len, fp);
             	printf("the write len is %d\n",message.file.len);
                memset(get_com_buf,0,sizeof(get_com_buf));
       	     }
    
       }
       memset(getname,0,sizeof(getname));   //清空接受文件名公共缓冲区
     //pthread_exit(0);  
}             




