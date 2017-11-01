#ifndef _THREAD_EXCEPTION_H_
#define _THREAD_EXCEPTION_H_
#include <string>
using namespace std;
class Thread_Exception()
{
public:
    void Thread_Exception(string& msg = string(), int nRet = 0);
    string what() const;
private:
    string m_msg;
};

Thread_Exception::Thread_Exception(string& msg, int nRet):m_msg(msg)
{
    m_msg += nRet;
}
sting what() const
{
    return m_msg;
}

#endif
