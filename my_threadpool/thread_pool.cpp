#include "thread_pool.h"
///#include <pthread.h>
ThreadPool::ThreadPool(uint max_thread_num, uint wait_seconds):m_idle(0),m_counter(0),m_max_thread_num(0),m_wait_seconds(0)
{
    m_max_thread_num = max_thread_num;
    m_wait_seconds = wait_seconds;
}

//
ThreadPool::~ThreadPool()
{
    if(m_is_quit == true)
        return;

    m_cond.Lock();
    m_is_quit = true;
    if(m_counter > 0)
    {
        if(m_idle > 0)
        {
            m_cond.Broadcast();
            while(m_counter > 0)
            {
                m_cond.Wait();
            }
        }
    }
    m_cond.Unlock();
}

void* StartRoutine(void* arg)
{
    if(arg == NULL)
        pthread_exit((void*)-1);
    cout << "start routine... " << endl;
    pthread_detach(pthread_self());

    ThreadPool* thread_pool = (ThreadPool*)arg;
    
    while(true)
    {
        //获取互斥锁。
        thread_pool->m_cond.Lock();
        thread_pool->m_idle++;
        bool is_timeout = false;

        //判断任务队列是否为空，线程是否退出。
        
        //分为以下几种情况：
        //1。任务队列为空并且线程退出。则退出当前线程。
        //2。任务队列不为空，线程退出。处理任务。
        //3。任务队列为空，线程未退出。阻塞在这里。
        //4. 任务队列不为空，线程未退出。 处理任务。
        //5。线程等待超时。
        while(thread_pool->m_tasks.empty() && !thread_pool->m_is_quit)
        {
            
            //3
            cout << "thread wait... tid = " << pthread_self() << endl;
            if(0 != thread_pool->m_cond.TimeWait(thread_pool->m_wait_seconds))
            {
                is_timeout = true;
                thread_pool->m_cond.Unlock();
                break;
            }
        }
        thread_pool->m_idle--;
        //5
        if(is_timeout && thread_pool->m_tasks.empty())
        {
           thread_pool->m_cond.Unlock();
           thread_pool->m_counter--;
           break;
        }

        //1
        if(thread_pool->m_tasks.empty() && thread_pool->m_is_quit)
        {
           thread_pool->m_cond.Unlock();
           thread_pool->m_counter--;
           if(thread_pool->m_counter == 0)
                thread_pool->m_cond.Signal();
           break;
        }

        //2,4
        if(!thread_pool->m_tasks.empty())
        {
            cout << "run function..." << endl;
            TaskInfo* task_info = thread_pool->m_tasks.front();
            thread_pool->m_tasks.pop();
            thread_pool->m_cond.Unlock();
            task_info->m_func(task_info->m_arg);
            delete task_info;
        }
    }

    cout << "pthread exit... tid = " << pthread_self() << endl;
    pthread_exit((void*)0);
}

//添加任务：向任务队列中添加任务。
void ThreadPool::AddTask(FuncType func, void* arg)
{
    //根据传递进来的参数，新创建一个任务对象。放在任务队列中。(注意对任务队列加锁)
    TaskInfo *task_info = new TaskInfo(func, arg);
   
    cout << "Add Task arg = " << *(int*)arg << endl;
    m_cond.Lock();
    m_tasks.push(task_info);
    m_cond.Unlock();
    cout << "before call StartTask" << endl;
    //开始任务。
    StartTask();
}

//开始任务：判断是否有空闲的线程，如果则发送信号唤醒。否则在不超过最大线程数量的基础上，创建线程。
void ThreadPool::StartTask()
{
    if(m_idle > 0)
    {
        m_cond.Signal();
        cout << "start task... idle = " << m_idle << endl;
    }
    else if(m_counter < m_max_thread_num)
    {
        pthread_t tid;
        int err = 0;
        err = pthread_create(&tid, NULL, StartRoutine, this);
        if( err == 0)
        {
            cout << "Create thread error! err = " << err << endl; 
        }
        cout << "Create thread tid = " << tid << endl;

        m_counter++;
        m_cond.Signal();
    }
}
