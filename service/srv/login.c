/*************************************************************************
	> File Name: login.c
	> Author: 
	> Mail: 
	> Created Time: 2015年08月02日 星期日 21时45分15秒
 ************************************************************************/

#include<stdio.h>
#include"./login.h"
#include"../common/common.h"
#include"./serve.h"
#include"../prest/login_prest.h"
#include<string.h>
int login(int connfd,seruser_t* temp,struct sockaddr_in cil_addr,seruser_list_t list)
{
    char buf[MAXBUF];
    user_t check;
    int ret;
    int log;
    printf("i am in login \n");
    while(1){
        int flag = 1;
        printf(" i am in while");
        if(ret = recv(connfd,buf,sizeof(buf),0) < 0){  //接受发送的数据
            printf("recv is error:%d\n",__LINE__);
        }else{
            break;
        }
    }
    printf("the buf :%s\n",buf);
    memcpy(&check,buf,sizeof(check));
    //printf("username:%s\n",check.username);
    //printf("userpasd:%s\n",check.userpasd);
    

    if(check.submit == 1){
            seruser_list_t pos;
            for(pos = list->next;pos != list; pos = pos->next){
                   printf("the name is check is %s ,pos:%s\n",check.username,pos->data.username);
                   if(strcmp(check.username,pos->data.username) == 0){
                          return 3;
                   }
            }
        
            //sleep(100);
            char objtemp[35];
            strcpy(objtemp,"./user/");
	    strcat(objtemp,check.username);
            printf("==is %s\n",objtemp);
	    FILE *fp = fopen(objtemp, "ab");//创建一个自己的文件，以后用来存离线消息
	    if (NULL == fp) {
		    printf("Cannot open file %s!\n", check.username);
		    return 0;
	    }
	    fclose(fp);
	    printf("the user is already submit\n");
	    strcpy(temp->username , check.username);
            strcpy(temp->userpasd , check.userpasd);
    	    temp->useraddr = cil_addr;
    	    temp->previe   = check.previe;
            temp->many     = check.many;
            temp->online   = 1;
            temp->connfd   = connfd;
            seruser_srv_add(temp);
            //char rv[2];
            //strcpy(rv,"Y");
            //send(connfd,rv,sizeof(rv),0);
            return 1;
    }else{
        
    	strcpy(temp->username , check.username);
        strcpy(temp->userpasd,  check.userpasd);
    	temp->useraddr = cil_addr;
    	temp->previe   = check.previe;
    	temp->many     = check.many;
    	//temp->online   = 1;
    	//temp->connfd   = connfd;
        return 0;
        
    }
}

inline int serve_srv_fetchall(seruser_list_t list) {
	int ret;
    ret = serve_Perst_SelectAll(list);
    if(0 == ret){
        printf("error Schedule_Srv_FetchAll\n");
        return 0;
    }
       return 1;
}


inline int seruser_srv_add(seruser_t *data) 
{
   int ret ;
   ret = seruser_Perst_Insert(data);
    if(0 == ret){
        printf("error Play_Perst_Insert \n");
        return 0;
    }
    return 1;
}
	
int find_seruser(seruser_list_t list_ser,char *username,char *userpasd,int connfd)
{
    seruser_list_t pos;

    for(pos = list_ser->next;pos != list_ser;pos = pos->next){
        if((strcmp(pos->data.username,username) == 0 )&& (strcmp(pos->data.userpasd,userpasd) == 0)){
           printf("pos:%s %s\n",pos->data.username,username);
           printf("pwd:%s %s\n",pos->data.userpasd,userpasd);
            
            seruser_t date;
            date = pos->data;
            date.online = 1;
            date.connfd = connfd;
	    seruser_srv_modify(&date);
            return 1;
        }
    }
    return 0;


}
    

int seruser_srv_modify(const seruser_t *data) {
    int flag ;

	flag = seruser_perst_update(data);
    printf("flag = %d\n",flag);
    return 0;

}





