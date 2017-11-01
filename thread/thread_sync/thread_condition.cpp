#include <iostream>
#include <pthread.h>
#include <queue>
#include <unistd.h>
#include <stdlib.h>
using namespace std;
pthread_cond_t qready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

queue<int> g_nums;

void* AddData(void* arg)
{
	sleep(1);
	cout << "Enter AddData..." << endl;
	int err;
	for(int i = 0; i < 5; i++)
	{
		pthread_mutex_lock(&qlock);
		g_nums.push(i);
		pthread_mutex_unlock(&qlock);	
		pthread_cond_signal(&qready);
	//	cout << "Input data i = " << i << endl;
		sleep(1);
	}
	pthread_exit((void*)1);
}
void* PrintData(void* arg)
{
	cout << "Enter PrintData..." << endl;
	while(1)
	{
		pthread_mutex_lock(&qlock);
		while(g_nums.size() == 0)
		{
		//	cout << "wait data..." << endl;	
			pthread_cond_wait(&qready, &qlock);
		}
	//	cout << "print data i = ";
		int tmp_num = g_nums.front();
		g_nums.pop();
		pthread_mutex_unlock(&qlock);
		//这里最后的那个endl一定要有，否则会直接输出 0 1 2 3 4，并不会表现出随着生产者消费，一个一个的打印出来。与输出缓冲区有关，以后再研究。
		cout << tmp_num << endl;
	//	sleep(1);
		if(tmp_num == 4)
			break;
	}
	cout << endl;
	pthread_exit((void*)2);
}
int main()
{
	pthread_t tid_add;
	pthread_t tid_write;
	
	int err;
	err = pthread_create(&tid_add, NULL, AddData, NULL);
	if(err != 0)
	{
		cout << "create tid_add error! err = " << err << endl;
	}
	err = pthread_create(&tid_write, NULL, PrintData, NULL);
	if(err != 0)
	{
		cout << "create tid_write error! err = " << err << endl;
	}

	err = pthread_join(tid_add, NULL);
	if(err != 0)
	{
		cout << "join tid_add error! err = " << err << endl;	
	}
	err = pthread_join(tid_write, NULL);
	if(err != 0)
	{
		cout << "join tid_write error! err = " << err << endl;	
	}
	exit(0);
}
