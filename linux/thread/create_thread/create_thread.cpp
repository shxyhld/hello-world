#include <pthread.h>
#include <vector>
#include <iostream>
#include <unistd.h>
using namespace std;

void PrintPid()
{
	pid_t pid = getpid();
	pthread_t tid = pthread_self();
	cout << "pid = " << pid << ",tid = " << tid << endl;
}
void* PthreadFunc(void* arg)
{
	PrintPid();
	return (void*)0;
}
int main()
{
	pthread_t tid;
	
	int err = 0;
	err = pthread_create(&tid, NULL, PthreadFunc, NULL);
	if(err != 0)
	{
		cout << "create tid_write error!" << endl;
	}
	PrintPid();
	//这里要sleep的原因是：要主线程先休眠，如果主线程不休眠，那么主线程运行退出后，整个进程就运行结束了，新创建的线程就没有运行机会了。
	sleep(2);

	return 0;
}
