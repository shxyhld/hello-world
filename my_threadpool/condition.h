#ifndef _CONDITION_H
#define _CONDITION_H
#include <pthread.h>
#include <time.h>
class Condition
{
    public:
        Condition(const pthread_mutexattr_t* mutex_attr = NULL, const pthread_condattr_t* cond_attr = NULL);
        ~Condition();
    private:
        pthread_mutex_t m_mutex;
        pthread_cond_t m_cond;
    public:
        //互斥锁相关方法;
        int Lock();
        int TryLock();
        int Unlock();

        //条件变量;
        int Signal();
        int Broadcast();
        int Wait();
        int TimeWait(int seconds);
};
#endif
