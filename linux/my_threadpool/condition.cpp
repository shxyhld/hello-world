#include "condition.h"

Condition::Condition(const pthread_mutexattr_t* mutex_attr, const pthread_condattr_t* cond_attr)
{
    pthread_mutex_init(&m_mutex, mutex_attr);
    pthread_cond_init(&m_cond, cond_attr);
}
Condition::~Condition()
{
    pthread_mutex_destroy(&m_mutex);
    pthread_cond_destroy(&m_cond);
}

int Condition::Signal()
{
    return pthread_cond_signal(&m_cond);
}
int Condition::Broadcast()
{
    return pthread_cond_broadcast(&m_cond);
}
int Condition::Wait()
{
    return pthread_cond_wait(&m_cond, &m_mutex);
}
int Condition::TimeWait(int seconds)
{
    struct timespec abstime;
    clock_gettime(CLOCK_REALTIME, &abstime);
    abstime.tv_sec += seconds;
    return pthread_cond_timedwait(&m_cond, &m_mutex, &abstime);
}


int Condition::Lock()
{
    return pthread_mutex_lock(&m_mutex);
}

int Condition::TryLock()
{
    return pthread_mutex_trylock(&m_mutex);
}

int Condition::Unlock()
{
    return pthread_mutex_unlock(&m_mutex);
}
