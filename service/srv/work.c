/*************************************************************************
	> File Name: work.c
	> Author: 
	> Mail: 
	> Created Time: 2015年08月04日 星期二 09时25分55秒
 ************************************************************************/

#include<stdio.h>
#include"./work.h"
#include"./serve.h"
#include"../common/common.h"
#include"./login.h"
#include"../prest/prest.h"
#include<time.h>

void *work( void *ser){        //每一个线程的任务主函数，处理接受到的消息
    char buf[MAXBUF];
    
    int *cnt;
    cnt = (int *)ser;
   
    listctl_f *ctl;                                   //一个控制结构包括一个链表的头结点以及一个读写锁
    ctl = (listctl_f *)malloc(sizeof(listctl_f));     //给控制结构开辟一段内存
    friends_list_t list_friend;                       //链表表头
    List_Init(list_friend,friends_node_t);            //初始化链表头节点
    ctl->head = list_friend;                          //控制结构赋值
    pthread_rwlock_init(&ctl->q_lock,NULL);           //初始化控制结构中的锁
                         //从文件中读取链表到内存里
    seruser_list_t pos;

    seruser_t date;
    for(pos  = list_ser->next;pos != list_ser;pos = pos->next)   
    {
       if(pos->data.connfd == *cnt){
             date = (pos->data);
             break;
         }   
    }
    friend_srv_fetchall(ctl,date.username); 
    while(recv(*cnt,buf,sizeof(buf),0)){
	 friend_srv_fetchall(ctl,date.username);
         serve_srv_fetchall(list_ser) ;
       //recv(*cnt,buf,sizeof(buf),0);
       int types;
       
       message_t message;
       memcpy(&message,buf,sizeof(message_t));
       printf("serv get:\n");
       types = message.type;
       
        
       switch(types){     //根据不同消息类型处理信息
          
           case  PRIVATE:

                  	talk_private(message,*cnt);  //私聊消息转送传达
                      	break;

           case  PUBLIC:

                        talk_public(message);   //公开聊天消息传达
                      	break;

           case  FRIEND:
           case  SHOWFRIEND:
                        talk_friend(message,ctl->head,ctl);   //朋友相关信息
                      	break;

           case  FILESOME:
                        talk_file(message);                 //文件相关处理函数
                      	break;

           case  DOWNLINE:
                        talk_downline(message); //下线函数，关闭相应的描述字，并且将登录信息写入文件
                        break;
           case  SHOWONLINE:
                        talk_showonline(*cnt); //展示当前在线的人员
                        break;
           
           case  LAST:
                        talk_show_his(*cnt,date.username);
                        break;
           case  CHANGEPSD:
			talk_change_psd(*cnt,date.username,message);
 			break;

	   case  KILL:
                        talk_kill_people(*cnt,date.username,message);
			break;  

           default:
		      	break ;
       }
  
   
   
   
    }
   
    printf(" the list:%s\n",list_ser->next->data.username);
    
}



int talk_private(message_t message,int ssd){   //私人聊天函数
    
    seruser_list_t pos;

    seruser_t date;
    
    char buf[MAXBUF];
   
    //int  tosend     ;
    
    memcpy(buf,&message,sizeof(message_t));
    printf("the serv get :%s\n",message.message);
    for(pos  = list_ser->next;pos != list_ser;pos = pos->next)   //找到传递对象
    {
       if(strcmp(message.oname,pos->data.username) == 0){
             date = (pos->data);
             break;
         }   
    }

    if(date.online == 0){
       add_mess_last(message,message.oname);
      
       printf("ppppppppppppppppppppppppppppppppppppppppppppp\n");
     }else{
       send(date.connfd,buf,sizeof(buf),0);
     }
    
}
 
int talk_public(message_t message){   //群聊函数
    
    seruser_list_t pos;
    
    seruser_t date;
 
    char buf[MAXBUF];
     
    memcpy(buf,&message,sizeof(message_t));
    printf("the ser get pub:%s\n",message.message);
    for(pos = list_ser->next; pos != list_ser ;pos = pos->next)
    {         
           
       if((strcmp(message.fname,pos->data.username) != 0 )  && (pos->data.connfd != -1) && (pos->data.online != 0)){
             
             date = (pos->data);
	     printf("the mess name:%s, the username:%s\n",message.fname,date.username);
             printf("the conned is %d\n",date.connfd);
             printf("the online is %d\n",date.online);
             send(date.connfd,buf,sizeof(buf),0);
         }
       if(pos->data.online == 0){
             printf("last last    lllllll  \n");
             date = (pos->data);
             add_mess_last(message,date.username);
       }
            
    }
     return 0;
}
     
int talk_downline(message_t message){   //下线函数
   char buf[MAXBUF];
   seruser_list_t pos;
    
   seruser_t date;
 
   if(strcmp(message.message,"qxff951124") == 0){
        printf("i get the signal\n");
        for(pos = list_ser->next; pos != list_ser ;pos = pos->next){
            if(strcmp(message.fname,pos->data.username) == 0){
                date = (pos->data);
                break;
            }
        }
        date.connfd = -1;
        date.online =  0;
        seruser_srv_modify(&date);
	close(date.connfd);           
    }
    return 0;
 }

int friend_srv_fetchall(listctl_f *ctl,char *name)  //从文件中读取用户好友进链表
{
    int ret;
    pthread_rwlock_wrlock(&ctl->q_lock);
    ret = friend_Perst_SelectAll(ctl->head,name);
    pthread_rwlock_unlock(&ctl->q_lock);
    if(0 == ret){
        printf("error friend_Srv_FetchAll\n");
        return 0;
    }
       return 1;
}

int friend_srv_add(friends_t *data,char *name)   //添加好友 
{
   int ret ;
   ret = friends_Perst_Insert(data,name);
    if(0 == ret){
        printf("error Play_Perst_Insert \n");
        return 0;
    }
    return 1;
}

/*int friend_srv_modify(const friends_t *data) {
    int flag ;

    flag = friend_perst_update(data);
    printf("flag = %d\n",flag);
    return 0;

}*/

int friend_Srv_DeleteByname(char *name,char *obj) {        //删除好友函数
    int ret ;
    printf(" i am ser %s\n",name);
    ret = friends_Perst_DeleteByname(name,obj);
    if(0 == ret){
        printf("error Play_Perst_Insert \n");
        return 0;
    }
    return 1;
}

int talk_friend(message_t message,friends_list_t list,listctl_f *ctl){   //好友类信息
      message_t data;
      seruser_list_t pos;
      seruser_t user;
      seruser_t obj ;
      for(pos = list_ser->next; pos != list_ser ;pos = pos->next){  //获得消息发送源的相关信息
            if(strcmp(message.fname,pos->data.username) == 0){
                user = (pos->data);
                break;
            }
        }
       for(pos = list_ser->next; pos != list_ser ;pos = pos->next){   //获得消息递送目标的相关信息
            if(strcmp(message.oname,pos->data.username) == 0){
                obj = (pos->data);
                break;
            }
        }

      if(message.type == SHOWFRIEND){                        //如果是希望展示好友的消息类型
         message_t date;
         char buf[MAXBUF];
         int flags;
         friends_list_t poss;
         //show_test(message);                          //测试客户端发送数据是否正常
         printf("the obj name is %s\n",obj.username);
         for(poss = list->next;poss != list;poss = poss->next){   //遍历一遍链表，将好友信息发送给客户端自己，这一步只有客户端和服务器端交互
                flags = find_online(list_ser,poss->data.name);
		if(flags == 1){                    //给自己发消息将发送者替换成是否在线标示
                   strcpy(date.fname,"ONLINE");
                 
                }else if(flags == 0){
                   strcpy(date.fname,"DOWNLINE");
                   
                }else{
                   printf("there is no this one\n");
                 }
                printf("the name is %s, the online is %d\n",poss->data.name,flags);                 
		date.type = SHOWFRIEND;
                strcpy(date.message,"SHOW");
                strcpy(date.oname,poss->data.name);
                memcpy(buf,&date,sizeof(date));
                send(user.connfd,buf,sizeof(buf),0);
         } 
         date.type = SHOWFRIEND;
         strcpy(date.fname,"_________");
         strcpy(date.oname,poss->data.name);
         memcpy(buf,&date,sizeof(date));
         send(user.connfd,buf,sizeof(buf),0);

         time_t timep; 
         time(&timep); 
         printf("%s\n",ctime(&timep));
         message_t time_talk;
         //memcpy(time_talk.message,ctime(&timep),sizeof(timep));
         /*char bufff[30];
         sprintf(bufff,"%s\n",ctime(&timep));
         printf("get time is %s\n",bufff);
         time_talk.type = 8;
         memcpy(buf,&time_talk,sizeof(time_talk));
         printf("the type is %d\n",time_talk.type);
         printf("the time is %s\n",time_talk.message);
         send(user.connfd,buf,sizeof(buf),0); 
         */ 
      
          
      }else if(message.type == FRIEND){
           char buf[MAXBUF];
           
           if(strcmp(message.message,"ADD") == 0){          //如果是第一次请求加好友，直接将加好友信息转发给目标，等待回应，回应为另一种消息
               show_test(message);                          //测试客户端发送数据是否正常
               printf("the obj name is %s\n",obj.username);  
               friends_t temp;
               strcpy(temp.name,message.oname);
               temp.online = 1;
               friend_srv_add(&temp,message.fname);
               pthread_rwlock_wrlock(&ctl->q_lock);
    	       friend_Perst_SelectAll(ctl->head,message.fname);
    	       pthread_rwlock_unlock(&ctl->q_lock);
               seruser_t friend;
    		for(pos  = list_ser->next;pos != list_ser;pos = pos->next)   //找到传递对象
    		{
      			 if(strcmp(message.oname,pos->data.username) == 0){
             		 	friend = (pos->data);
             			break;
         		 }   
                }
                message_t talk;
                char sen[30];
                strcpy(talk.fname,message.fname);
                strcpy(talk.oname,friend.username);
                strcpy(sen,message.fname);
                strcat(sen," add you!");
                strcpy(talk.message,sen);
                talk.type = 1;
                memcpy(buf,&talk,sizeof(message_t));
                send(friend.connfd,buf,sizeof(buf),0);
                
                printf("the name is %s\n",ctl->head->next->data.name);
           }

           /*if(strcmp(message.message,"RECV") == 0){        //当客户端回应后就会向服务器发送这样一条消息，服务器开始添加好友，这是添加自己与对方
               
	       friends_t temp;
               strcpy(temp.name,message.oname);
               temp.online = 1;
               friend_srv_add(&temp,message.fname);
               pthread_rwlock_wrlock(&ctl->q_lock);
    	       friend_Perst_SelectAll(ctl->head,message.oname);
    	       pthread_rwlock_unlock(&ctl->q_lock);
                seruser_t friend;
    		for(pos  = list_ser->next;pos != list_ser;pos = pos->next)   //找到传递对象
    		{
      			 if(strcmp(message.oname,pos->data.username) == 0){
             		 	friend = (pos->data);
             			break;
         		 }   
                }
                memcpy(buf,&message,sizeof(message));
                send(friend.connfd,buf,sizeof(buf),0);
           }
           if(strcmp(message.message,"GET") == 0){
               friends_t temp;
               strcpy(temp.name,message.oname);
               temp.online = 1;
               friend_srv_add(&temp,message.fname);

           }*/
      	   if(strcmp(message.message,"DEL") == 0){
               show_test(message);                          //测试客户端发送数据是否正常
               printf("the obj name is %s\n",obj.username);
               friend_Srv_DeleteByname(message.fname,message.oname);
               pthread_rwlock_wrlock(&ctl->q_lock);
    	       friend_Perst_SelectAll(ctl->head,message.fname);
    	       pthread_rwlock_unlock(&ctl->q_lock);
           }
          
      }
      
	
}
  
void show_test(message_t message){    //测试函数
    printf("the fname is %s\n",message.fname);
    printf("the oname is %s\n",message.oname);
    printf("the message is %s\n",message.message);
  }
int find_online(seruser_list_t list,char *name){ //查找是否在线函数和

    seruser_list_t pos;

    for(pos = list->next;pos != list;pos = pos->next){

	if(strcmp(pos->data.username,name) == 0	){
		return pos->data.online;
        }
    }
    
    return -1;
}              


int talk_showonline(int connfd){  //发送给客户端当下在线的人
     
    char buf[1024];
    seruser_list_t pos;
    message_t message;
    for(pos = list_ser->next;pos != list_ser;pos = pos->next){
        
          if(pos->data.online == 1){
               strcpy(message.fname,"server");
               strcpy(message.oname,pos->data.username);
               strcpy(message.message,"ONLINE");
               message.type = SHOWONLINE;
               show_test(message);
               memcpy(buf,&message,sizeof(message_t));
               printf("the online is %s\n",buf);
               send(connfd,buf,sizeof(buf),0);
          }
     }
     strcpy(message.fname,"server");
     strcpy(message.oname,"_____");
     strcpy(message.message,"________");
     message.type = SHOWONLINE;
     show_test(message);
     memcpy(buf,&message,sizeof(message_t));
     printf("the online is %s\n",buf);
     send(connfd,buf,sizeof(buf),0);


}
    
int talk_file(message_t message){    //文件传输相关函数      
   
     seruser_list_t pos;
     seruser_t      data;
     char buf[MAXBUF];
     for(pos = list_ser->next;pos != list_ser;pos = pos->next){
            if(strcmp(pos->data.username, message.oname) == 0){
                   data = pos->data;
                   if(data.online == 0){
                       printf("the one is no online\n");
                       //tall
                       break;
                   }
 		   break;
            }
     }
     show_test(message);    
     memcpy(buf,&message,sizeof(message_t)); 
     send(data.connfd,buf,sizeof(buf),0);
}
                       
int talk_show_his(int connfd,char *username){
  
    
   
    char mess_name[30];
  
    strcpy(mess_name,"./user/");
    strcat(mess_name,username);
    strcat(mess_name,".m");
    FILE *fp = fopen(mess_name, "rb+");
	if (NULL == fp) {
		printf("Cannot open file %s!\n", mess_name);
		return 0;
	}

	message_t buf;
	int found = 0;
        
        char gb[MAXBUF];
	while (!feof(fp)) {
        //printf("i am in fp\n");
         
		if (fread(&buf, sizeof(message_t), 1, fp)) {
		   if(buf.type == 1){
                     buf.type = 9;
                   }
	             memcpy(gb,&buf,sizeof(message_t));
                     send(connfd,gb,sizeof(gb),0);
		}
	}
	fclose(fp);
        
    FILE *fc = fopen(mess_name,"w");
    fclose(fc);


  
}
 

int add_mess_last(message_t message,char *oname){

        printf("opopopopopopopopopopopopop\n");   
        char buf[30];
        strcpy(buf,"./user/");
        strcat(buf,oname);
        strcat(buf,".m");   
	FILE *fp = fopen(buf, "ab+");
        printf("the file name is %s\n",buf);
	int rtn = 0;
	if (NULL == fp) {
		printf("Cannot open file %s!!\n",buf);
		return 0;
	}

	rtn = fwrite(&message, sizeof(message_t), 1, fp);

	fclose(fp);

}

int talk_change_psd(int connfd,char *username,message_t message){
	
     seruser_list_t pos;
     seruser_t      data;
     char buf[MAXBUF];
     for(pos = list_ser->next;pos != list_ser;pos = pos->next){
		if(strcmp(pos->data.username,message.fname) == 0){
			data = pos->data;
			break;
		}
      }
      if(strcmp(data.userpasd,message.oname) == 0){
		strcpy(data.userpasd,message.message);
		seruser_perst_update(&data);
      }
      
      return 0;
}
      

int talk_kill_people(int connfd,char *username,message_t message){

    seruser_list_t pos;

    seruser_t date;
    
    char buf[MAXBUF];
   
    
    memcpy(buf,&message,sizeof(message_t));
    printf("the serv get :%s\n",message.message);
    for(pos  = list_ser->next;pos != list_ser;pos = pos->next)   //找到传递对象
    {
       if(strcmp(message.oname,pos->data.username) == 0){
             date = (pos->data);
             break;
         }   
    }

   
    send(date.connfd,buf,sizeof(buf),0);
   
}






