/*************************************************************************
	> File Name: serve.c
	> Author: 
	> Mail: 
	> Created Time: 2015年08月02日 星期日 21时44分11秒
 ************************************************************************/

#include<stdio.h>
#include"./pthreadpool.h"
#include"./serve.h"
#include"./work.h"
#include"./login.h"
#include"../common/List.h"
/*void *work(void *connfd){
    char buf[200];
    int s,r;
    int *cnt = (int *)connfd;
    printf("commfd--%d\n",*cnt);
    close(*cnt);
    exit(0);
}*/




int main()      // 服务器主函数
{
  int sockfd,connfd;
  struct sockaddr_in ser_addr;
  struct sockaddr_in cil_addr;
  int sin_size;

  FILE *fp = fopen("server", "ab");
	
  if (NULL == fp) {
      printf("Cannot open file %s!\n", "server");
      return 0;
  }	
  fclose(fp);
	
   

  //seruser_list_t list_ser;
  List_Init(list_ser,seruser_node_t); //创建用户链表管理结构
  //serve_srv_fetchall(list_ser);
  listctl_s *ctl;
  ctl = (listctl_s *)malloc(sizeof(listctl_s));
  ctl->head = list_ser;
  pthread_rwlock_init(&ctl->q_lock,NULL);
  //printf("lalalalalalalallalalalal\n");


  pool_init(4);
  if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1){
	fprintf(stderr,"socket error!\n");
         exit(0);
   }

   ser_addr.sin_family = AF_INET;
   ser_addr.sin_port   = htons(SERVER_PORT);
   ser_addr.sin_addr.s_addr = INADDR_ANY;
   bzero(&(ser_addr.sin_zero),8);

   if(bind(sockfd,(struct sockaddr *)&ser_addr,sizeof(struct sockaddr_in)) == -1){
	    fprintf(stderr,"bind error!\n");
	    exit(1);
   }
   
    if(listen(sockfd,BACKLOG) == -1){
        fprintf(stderr,"bind error\n");
        exit(1);
    }

    
    sin_size = sizeof(struct sockaddr_in);
    int cfd[100];
    char work_result[30];
    int i = 0;
    int on;
    for(;;)
    {
        int goin = 0;
	   if((connfd = accept(sockfd,(struct sockaddr*)&cil_addr,&sin_size))== -1){
            printf("accept is error\n");
            continue;
        }
        //epoll_create(......................);
        //epoll_ctl(epollfd, EPOLL_CTL_ADD, confd, &event);
        //int nfds = epoll_wait(epfd, events, MAX_FD, -1);
        seruser_t temp;
        serve_srv_fetchall(list_ser);
        on = login(connfd,&temp,cil_addr,list_ser);
           
        if(on == 0){    //返回值为0表示非注册用户，需要对比是否为真
            int find;
            serve_srv_fetchall(list_ser); //重新读取文件信息建立链表
            seruser_list_t  pos;
            find = find_seruser(list_ser,temp.username,temp.userpasd,connfd);
            if(find == 0){
               printf("there is no this one\n");
                char tp[2] = "N";
                goin = 1;
                send(connfd,tp,sizeof(tp),0);
                close(connfd);
                strcpy(work_result,"login fail  !");
                make_sys(temp,work_result);
            }else{
                printf("i find this gay\n");
                char dp[2] = "Y";
                send(connfd,dp,sizeof(dp),0);
		strcpy(work_result,"login success!");
                make_sys(temp,work_result);

              }   
            }else if(on == 3){
		printf("the man is double,login fail\n");
                printf("sdajlkasjdklasjdkljaslkdjlkasjdlkasjdlkjaslkdjlksa\n");
                char dd[2] = "D";
                send(connfd,dd,sizeof(dd),0);
                close(connfd);
                goin = 1;
                strcpy(work_result,"submit failed");
                make_sys(temp,work_result);
            }else{
                printf("i find this gay\n");
                char dp[2] = "Y";
                send(connfd,dp,sizeof(dp),0);
                strcpy(work_result,"submit success!");
                make_sys(temp,work_result);
            
        }      
        serve_srv_fetchall(list_ser);
        seruser_list_t pos;
        for(pos  = list_ser->next;pos != list_ser;pos = pos->next)
        {
            printf("list_ser = %s\n",pos->data.username);
            printf("lise_ser = %d\n",pos->data.online);
        }
        printf("==%s\n = %s\n",temp.username,temp.userpasd);
        cfd[i] = connfd;
        printf("i am in connfd:%d\n",connfd);
        if(!goin){
            //pool_add_worker(work,(void *)temp.username);
            pool_add_worker(work,(void *)&cfd[i]);
        }
            i++;          
    }
    close(connfd);
}
	



int add_srv_syslog(syslog_t * data){   //写日志函数
 
    int ret;
    ret = add_prest_syslog(data);
    if(ret == 0){
        printf("the file is something wrong\n");
        return 0;
    }
    
    return 1;
}


int make_sys(seruser_t temp,char *dowork){       //制造一条日志信息
    
      printf("i am in make_first\n");
      int reslut;
      syslog_t* sys;
      sys = (syslog_t *)malloc(sizeof(syslog_t));
      memset(sys,0,sizeof(syslog_t));
      printf(" i am behand malloc\n");
      memset(sys->name,0,sizeof(sys->name));
      strcpy(sys->name,temp.username);
      sys->name[strlen(temp.username)+1] = '\0';
      sys->name[strlen(temp.username)+2] = ' ';
      sys->name[strlen(temp.username)+3] = ' ';
      printf(" i am the name cpy\n");
      //strcat(sys->name,'\0');
      
      printf("i am in make_sys \n");    

      time_t timep; 
      time(&timep);
      memset(sys->time,0,sizeof(sys->time));
      strcat(sys->time,ctime(&timep));
      //memcpy(sys->time,ctime(&timep),sizeof(ctime(&timep)));
      strcpy(sys->work,dowork);
      strcat(sys->work,"\n");
      
      reslut = add_srv_syslog(sys);
}
    
       
       	
