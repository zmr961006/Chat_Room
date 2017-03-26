/*************************************************************************
	> File Name: login_prest.c
	> Author: 
	> Mail: 
	> Created Time: 2015年08月04日 星期二 16时40分54秒
 ************************************************************************/

#include<stdio.h>
#include"./login_prest.h"
#include"../common/common.h"
#include"../srv/serve.h"
int serve_Perst_SelectAll(seruser_list_t list){
        seruser_node_t *newNode;
        seruser_t data;
        int recCount = 0;

        List_Free(list, seruser_node_t);

        FILE *fp = fopen("server", "rb");
        if (NULL == fp) {
                printf("Cannot open file %s!\n", "server"); 
                return 0;
        }
        while (!feof(fp)) {
                if (fread(&data, sizeof(seruser_t), 1, fp)) {
                        newNode = (seruser_node_t*) malloc(sizeof(seruser_node_t));
                        if (!newNode) {
                                printf(
                                                "Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
                                break;
                        }
                        //newNode->data.online = 0;
                        //newNode->data.connfd = -1;
                        newNode->data = data;
                        data.connfd = -1;
                        data.online = 0;
                        List_AddTail(list, newNode);
                        recCount++;
                }
        }
        fclose(fp);
        return recCount;

}


int seruser_Perst_Insert(seruser_t *data) {
	assert(NULL!=data);
	FILE *fp = fopen("server", "ab+");
	int rtn = 0;
	if (NULL == fp) {
		printf("Cannot open file %s!\n","server");
		return 0;
	}

	rtn = fwrite(data, sizeof(seruser_t), 1, fp);

	fclose(fp);
	return rtn;
}




int seruser_perst_update(const seruser_t * data) {
	assert(NULL!=data);
    //printf("i am in prest");
	FILE *fp = fopen("server", "rb+");
	if (NULL == fp) {
		printf("Cannot open file %s!\n", "server");
		return 0;
	}

	seruser_t buf;
	int found = 0;

	while (!feof(fp)) {
        //printf("i am in fp\n");
		if (fread(&buf, sizeof(seruser_t), 1, fp)) {
			if (strcmp(buf.username ,data->username) == 0) {
                printf("buf=%s data:%s\n",buf.username,data->username);
				fseek(fp, -sizeof(seruser_t), SEEK_CUR);
				fwrite(data, sizeof(seruser_t), 1, fp);
				found = 1;
				break;
			}

		}
	}
	fclose(fp);

	return found;
}

/*int seruser_Perst_Insert(seruser_t *data) {
	assert(NULL!=data);
	FILE *fp = fopen("server", "ab+");
	int rtn = 0;
	if (NULL == fp) {
		printf("Cannot open file %s!\n","server");
		return 0;
	}

	rtn = fwrite(data, sizeof(seruser_t), 1, fp);

	fclose(fp);
	return rtn;
}*/

int add_prest_syslog(syslog_t * data){            //将日志信息写进文件
        
       assert(NULL != data);
       FILE *fp = fopen("syslog","ab+");
       int rtn = 0;
       if(NULL == fp){
             printf("Cannot open file %s!\n","syslog");
             return 0;
       }
       
       rtn = fwrite(data,sizeof(syslog_t),1,fp);
       
       fclose(fp);
       return rtn;
}






