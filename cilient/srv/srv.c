/*************************************************************************
	> File Name: srv.c
	> Author: 
	> Mail: 
	> Created Time: 2015年08月03日 星期一 09时37分08秒
 ************************************************************************/

#include <stdio.h>
#include "./srv.h"
#include <apue.h>
#include <gtk/gtk.h>
#include "../view/prive.h"
#include "../common/common.h"
#include"../common/List.h"
int Connect(const char *username,const char *userpasd,int submit)    //链接函数第一版
{
    int sockfd, numbytes;
    char buf[MAXDATASIZE];
    struct hostent *he;
    struct sockaddr_in serv_addr;
    char ip[50];
    strcpy(ip,"127.0.0.1");

    /*if (argc != 2)
    {
        fprintf(stderr, "usage: cilent hostname\n");
        exit(1);
    }*/

    if ((he = gethostbyname(ip)) == NULL)            //获取
    {
        fprintf(stderr, "gethostbyname error!\n");
        exit(1);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)    //建立一个套接字
    {
        fprintf(stderr, "socket error!\n");
        exit(1);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVER_PORT);
    serv_addr.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(serv_addr.sin_zero), 8);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1) //发送链接请求
    {
        fprintf(stderr, "connect error!:%d\n",__LINE__);
        exit(1);
    }

    /*if ((numbytes = read(sockfd, buf, MAXDATASIZE)) == -1)      //读取发送来的数据
    {
        fprintf(stderr, "read error!\n");
        exit(1);
    }

    buf[numbytes] = '\0';
    printf("Received: %s\n", buf);*/
    while(1){
        user_t msg;
        strcpy(msg.username ,username);
        strcpy(msg.userpasd ,userpasd);
        strcpy(msg.objip    , "127.0.0.1");
        msg.previe   = 1;
        msg.many     = 1;
        strcpy(msg.msg      , "hello world");
        msg.root     = 0;
        msg.submit   = submit;
        memcpy(buf,&msg,sizeof(msg));
        printf("buf:%s\n",buf);
        printf("i am connecting\n");
        send(sockfd,buf,sizeof(buf),0);
        read(sockfd,buf,MAXDATASIZE);
        printf("get %s\n",buf);
        sleep(2);
    }
    close(sockfd);
}



gboolean isconnected = FALSE;
//正式链接函数
gboolean trylink(const char *username,const char *userpasd,int submit,const char *servip)
{
    int  numbytes;
    char buf[MAXDATASIZE];
    struct hostent *he;
    struct sockaddr_in serv_addr;
    char ip[50];
    strcpy(ip,servip);

    /*if (argc != 2)
    {
        fprintf(stderr, "usage: cilent hostname\n");
        exit(1);
    }*/

    if ((he = gethostbyname(ip)) == NULL)            //获取
    {
        fprintf(stderr, "gethostbyname error!\n");
        exit(1);
    }

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)    //建立一个套接字
    {
        fprintf(stderr, "socket error!\n");
        exit(1);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVER_PORT);
    serv_addr.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(serv_addr.sin_zero), 8);

    if (connect(sd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1) //发送链接请求
    {
        fprintf(stderr, "connect error!:%d\n",__LINE__);
        exit(1);
    }

    /*if ((numbytes = read(sockfd, buf, MAXDATASIZE)) == -1)      //读取发送来的数据
    {
        fprintf(stderr, "read error!\n");
        exit(1);
    }

    buf[numbytes] = '\0';
    printf("Received: %s\n", buf);*/
        int s;
        user_t msg;
        user_t *userinfo;
        userinfo = &msg;
        strcpy(msg.username ,username);
        strcpy(msg.userpasd ,userpasd);
        strcpy(msg.objip    , "127.0.0.1");
        msg.previe   = 1;
        msg.many     = 1;
        strcpy(msg.msg      , "hello world");
        msg.root     = 0;
        msg.submit   = submit;
        memcpy(buf,&msg,sizeof(msg));
        printf("buf:%s\n",buf);
        printf("i am connecting\n");
        s = send(sd,buf,sizeof(buf),0);
        memset(buf,0,sizeof(buf));
        read(sd,buf,MAXDATASIZE);
        printf("buf = %s\n",buf);
        printf("sd = %d\n",sd);
        //char try[MAXDATASIZE];
        //strcpy(try,"firstlink");
        //int s;
        //s = send(sockfd,try,sizeof(try),0);
        //printf("s = %d\n",s);
        if(strcmp(buf,"N") == 0   || strcmp(buf,"D") == 0){
            close(sd);
             printf("asdhlaskjdlkasjdlkjaslkdjlksajdlkas\n");
            //formal_link(msg,servip);
            isconnected = FALSE;
        
            return FALSE;
        }else{
            //formal_link(msg,servip);
            printf("lalalalallalalallalalalla\n");
            memset(buf,0,sizeof(buf));
            int abb;
	    /*while(1){
            strcpy(buf,"exit");
            abb = send(sd,buf,sizeof(buf),0);
            printf("i abb = %d\n",abb);
            sleep(1);
            }*/
            //close(sockfd);
            //formal_link(userinfo,servip);
	    printf("the normal s is %d\n",s);
	    //choice_view(&msg,servip,sd);
            isconnected = TRUE;
            return TRUE;
        }
        //printf("get %s\n",buf);
       
}


//gboolean isconnected = FALSE;

gboolean formal_link(user_t *user,const char *servip)   //链接函数第三版
{
    int  numbytes;
    char buf[MAXDATASIZE];
    struct hostent *he;
    struct sockaddr_in serv_addr;
    char ip[50];
    strcpy(ip,servip);

    if ((he = gethostbyname(ip)) == NULL)            //获取
    {
        fprintf(stderr, "gethostbyname error!\n");
        exit(1);
    }

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)    //建立一个套接字
    {
        fprintf(stderr, "socket error!\n");
        exit(1);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVER_PORT);
    serv_addr.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(serv_addr.sin_zero), 8);

    if (connect(sd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1) //发送链接请求
    {
        fprintf(stderr, "connect error!:%d\n",__LINE__);
        exit(1);
    }

    
    memcpy(buf,user,sizeof(user_t));
    
    send(sd,buf,sizeof(buf),0);
    read(sd,buf,MAXDATASIZE);
    printf("get %s\n",buf);
    
    char try[MAXDATASIZE];
    strcpy(try,"twice");
    send(sd,try,MAXDATASIZE,0);

    if(strcmp(buf,"Y") == 0){
        isconnected = TRUE;
        return TRUE;
    }else{
        isconnected = FALSE;
        return FALSE;
    }
  
    //close(sockfd);
}














