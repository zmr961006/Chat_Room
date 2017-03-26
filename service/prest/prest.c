/*************************************************************************
	> File Name: prest.c
	> Author: 
	> Mail: 
	> Created Time: 2015年08月03日 星期一 21时43分30秒
 ************************************************************************/

#include<stdio.h>
#include"./prest.h"


int friend_Perst_SelectAll(friends_list_t list,char *name){
        friends_node_t *newNode;
        friends_t data;
        int recCount = 0;
        List_Free(list, friends_node_t);

        char buf[30];
        strcpy(buf,"./user/");
        strcat(buf,name);
        strcat(buf,".f");
   
        FILE *fp = fopen(buf, "rb");
        if (NULL == fp) {
                printf("Cannot open file %s!\n",buf); 
                return 0;
        }
        while (!feof(fp)) {
                if (fread(&data, sizeof(friends_t), 1, fp)) {
                        newNode = (friends_node_t*) malloc(sizeof(friends_node_t));
                        if (!newNode) {
                                printf(
                                                "Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
                                break;
                        }
                        //newNode->data.online = 0;
                        //newNode->data.connfd = -1;
                        newNode->data = data;
                        
                        List_AddTail(list, newNode);
                        recCount++;
                }
        }
        fclose(fp);
        return recCount;

}

int friends_Perst_Insert(friends_t *data,char *name) {
	assert(NULL!=data);
        char buf[30];
        strcpy(buf,"./user/");
        strcat(buf,name);
        strcat(buf,".f");   
	FILE *fp = fopen(buf, "ab+");
	int rtn = 0;
	if (NULL == fp) {
		printf("Cannot open file %s!!\n",buf);
		return 0;
	}

	rtn = fwrite(data, sizeof(friends_t), 1, fp);

	fclose(fp);
	return rtn;
}

int friends_Perst_DeleteByname(char *name,char *obj) {
        char BUF[30];
        strcpy(BUF,"./user/");
        strcat(BUF,name);
        strcat(BUF,".f");        

        char TEMP[30];
        strcpy(TEMP,"./user/");
        strcat(TEMP,name);
        strcat(TEMP,".t");        

        //printf("11111111111111111111111111111111111\n");
	if(rename(BUF, TEMP)<0){
		printf("Cannot open file %s!\n", BUF);
		return 0;
	}

	FILE *fpSour, *fpTarg;
	fpSour = fopen(TEMP, "rb");
	if (NULL == fpSour ){
		printf("Cannot open file %s!\n", BUF);
		return 0;
	}
        //printf("22222222222222222222222222222222222222\n");
	fpTarg = fopen(BUF, "wb");
	if ( NULL == fpTarg ) {
		printf("Cannot open file %s!\n", TEMP);
		return 0;
	}


	friends_t buf;
        //printf("3333333333333333333333333333333333333333333\n");
	int found = 0;
	while (!feof(fpSour)) {
		if (fread(&buf, sizeof(friends_t), 1, fpSour)) {
			 printf("the name is %s , the bufname is %s\n",name,buf.name);
			if (strcmp(obj,buf.name) == 0) {
                                printf("the name is %s , the bufname is %s\n",name,buf.name);
				found = 1;
				continue;
			}
			fwrite(&buf, sizeof(friends_t), 1, fpTarg);
		}
	}

	fclose(fpTarg);
	fclose(fpSour);
	remove(TEMP);
	return found;
}



