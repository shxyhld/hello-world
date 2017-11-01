#include <pthread.h>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
using namespace std;

//使用pthread_cancel返回。
void* ThreadFunc2(void* arg)
{
	cout << "ThreadFunc2 exit ..." << endl;
	pthread_exit((void*)2);
}

//使用return返回。
void* ThreadFunc1(void* arg)
{
	cout << "ThreadFunc1 return ..." << endl;
//	sleep(2);
	return ((void*)1);
}

int main()
{
	pthread_t tid1;
	pthread_t tid2;

	void* tret1;
	void* tret2;
	int err = 0;
	
	err = pthread_create(&tid1, NULL, ThreadFunc1, NULL);
	if(err != 0)
	{
		cout << "create tid1 error! err = " << err << endl;
	}
	
	err = pthread_create(&tid2, NULL, ThreadFunc2, NULL);
	if(err != 0)
	{
		cout << "create tid2 error! err = " << err << endl;
	}
	
	err = pthread_join(tid1, &tret1);
	if(err != 0)
	{
		cout << "tid1 pthread_join error! err = " << err << endl;
	}
	//注意：此处跟书上的例子不一样，x86机器上的指针占8个字节，因此需要将tret转成long，否则会有精度损失的编译报错。
	cout << "After pthread join, tret1 = " << (long)tret1 << endl;
	//cout << "sizeof(int) = " << sizeof(int) << ",sizeof(void*) = " <<sizeof(void*) << endl;	
	
	err = pthread_join(tid2, &tret2);
	if(err != 0)
	{
		cout << "tid2 pthread_join error! err = " << err << endl;
	}
	cout << "After pthead join, tret2 = " << (long)tret2 << endl;	
	//这里要sleep的原因是：要主线程先休眠，如果主线程不休眠，那么主线程运行退出后，整个进程就运行结束了，新创建的线程就没有运行机会了。
	sleep(4);

	return 0;
}
