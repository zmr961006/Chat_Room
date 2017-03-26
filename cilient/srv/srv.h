/*************************************************************************
	> File Name: srv.h
	> Author: 
	> Mail: 
	> Created Time: 2015年08月04日 星期二 21时42分15秒
 ************************************************************************/

#ifndef _SRV_H
#define _SRV_H

#include "../common/common.h"
#include <gtk/gtk.h>

int Connect(const char *username,const char *userpasd,int submit);//测试建立链接

gboolean trylink(const char *username,const char *userpasd,int submit,const char *servip);//登录链接

//int seruser_srv_modify(seruser_t *data);//更改用户在线信息
gboolean formal_link(user_t *user,const char *servip);  //正式建立链接
#endif
