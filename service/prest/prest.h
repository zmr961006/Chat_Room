/*************************************************************************
	> File Name: prest.h
	> Author: 
	> Mail: 
	> Created Time: 2015年08月12日 星期三 00时55分47秒
 ************************************************************************/

#ifndef _PREST_H
#define _PREST_H

#include"../common/common.h"
#include"../common/List.h"
int friend_Perst_SelectAll(friends_list_t list,char *name);


int friends_Perst_Insert(friends_t *data,char *name);

int friends_Perst_DeleteByname(char *name,char *obj);

#endif
