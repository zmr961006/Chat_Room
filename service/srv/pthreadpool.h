/*************************************************************************
	> File Name: pthreadpool.h
	> Author: 
	> Mail: 
	> Created Time: 2015年08月03日 星期一 21时17分49秒
 ************************************************************************/

#ifndef _PTHREADPOOL_H
#define _PTHREADPOOL_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>
#include<assert.h>

typedef struct worker  
{  
    /*回调函数，任务运行时会调用此函数，注意也可声明成其它形式*/  
    void *(*process) (void *arg);  
    void *arg;/*回调函数的参数*/  
    struct worker *next;  
  
} CThread_worker;  
 


/*线程池结构*/  
typedef struct  
{  
    pthread_mutex_t queue_lock;  
    pthread_cond_t queue_ready;  
  
    /*链表结构，线程池中所有等待任务*/  
    CThread_worker *queue_head;  
  
    /*是否销毁线程池*/  
    int shutdown;  
    pthread_t *threadid;  
    /*线程池中允许的活动线程数目*/  
    int max_thread_num;  
    /*当前等待队列的任务数目*/  
    int cur_queue_size;  
  
} CThread_pool;  
  static CThread_pool *pool = NULL;

int pool_add_worker (void *(*process) (void *arg), void *arg);  
void *thread_routine (void *arg); 
int  pool_destroy () ;
void *  thread_routine (void *arg); 
void  pool_init (int max_thread_num);  


#endif
