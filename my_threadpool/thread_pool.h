#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_
#include "condition.h"
#include <queue>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;
typedef void* (*FuncType)(void* arg);
typedef unsigned int uint;

//任务结构：由回调函数和其参数构成。
struct TaskInfo
{
    TaskInfo(FuncType func, void* arg):m_func(func),m_arg(arg)
    {}
    FuncType m_func;
    void* m_arg;
};

//线程池
class ThreadPool
{
    
    friend void* StartRoutine(void* arg);
    public:
        ThreadPool(uint max_thread_num, uint wait_seconds);
        ~ThreadPool();
    public:
        void AddTask(FuncType func, void* arg);    //添加任务接口;
    private: 
        void StartTask();     
    private:
        Condition m_cond;               //条件变量;
        queue<TaskInfo*> m_tasks;       //任务队列;
        uint m_idle;                    //空闲线程数量;
        uint m_counter;                 //已经创建的进程总数量;
        bool m_is_quit;                 //线程池退出标志;
        uint m_max_thread_num;          //最大创建线程的数量;
        uint m_wait_seconds;            //线程可以等待的秒数，超过这个时间线程将被回收节约资源;
};
#endif
