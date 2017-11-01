#include <iostream>
#include "condition.h"
#include "thread_pool.h"
#include <string>
using namespace std;

//具体的任务信息:将传进来的参数打印出来。
void* MyTask(void* arg)
{
    int number = *(int*)arg;
    delete (int* )arg;
    
    cout << "tid = " << pthread_self() << ",number = " << number << endl;
    return (void*)0;
}

int main()
{
    //创建线程池对象。
    //添加任务。
    cout << "Input max pthread number:";
    int max_thread_num;
    cin >> max_thread_num;
    
    cout << "Input create task number:";
    int task_number;
    cin >> task_number;

    ThreadPool thread_pool(max_thread_num, task_number);
    for(int i = 0; i < task_number; i++)
    {
        cout << i << endl;
        thread_pool.AddTask(MyTask, new int(i));
        sleep(1);
    }
    
    exit(0);
}
