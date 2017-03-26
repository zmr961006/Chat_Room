/*************************************************************************
	> File Name: cilent.c
	> Author: 
	> Mail: 
	> Created Time: 2015年08月03日 星期一 09时33分49秒
 ************************************************************************/

#include<stdio.h>
#include"./cilent.h"
#include"../view/login.h"
#include"../view/prive.h"
int main(int argc,char **argv)
{
    GtkWidget *window;
    
    if(!g_thread_supported())
 	g_thread_init(NULL);
    gtk_init(&argc,&argv);
    window = login_view();
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}



