#include <pthread.h>
#include <vector>
#include <iostream>
#include <unistd.h>
using namespace std;
/*
 * 线程互斥示例：
 * 1.在main函数中定义了一个Data对象data。
 * 2.创建了3个线程：一个打印数据的线程(PrintData)，两个写数据的线程(AddData1和AddData2)。这三个线程都可以操作main函数中定义的Data对象data
 * 3.在不进行互斥处理的情况下，添加到m_ids中的数据将是乱的（1和2交叉出现）。（可以注释掉代码中，pthread_mutex_lock、pthread_mutex_unlock进行结果对比）
 * 4.进行了互斥处理的情况下，添加到m_ids中的数据会是顺序的（1和2不会交叉出现）
 */
//数据结构：该数据可能由多个线程同时操作，因此要对该数据添加互斥变量，保证只有当一个线程处理完成后，另外一个线程才可以处理。
struct Data
{
	vector<int> m_ids;
	pthread_mutex_t m_lock;	//互斥锁，
};

//打印线程：
void* PrintData(void* arg)
{
	Data* data = (Data*)arg;
	if(NULL == data)
		return (void*)-1;
	//延时3秒，留足够的时间，让写数据的线程添加数据。
	sleep(3);

	//此处也要加锁，防止其他线程操作，导致迭代器失效。
	pthread_mutex_lock(&data->m_lock);
	vector<int>::iterator iter = data->m_ids.begin();
	for(; iter != data->m_ids.end(); iter++)
	{
		cout << *iter << ' ';
	}
	pthread_mutex_unlock(&data->m_lock);
	cout << endl;
	return (void*)0;
}

void* AddData1(void* arg)
{
	Data* data = (Data*)arg;
	if(NULL == data)
		return (void*)-2;
	pthread_mutex_lock(&data->m_lock);
	for(int i = 0; i < 20; i++)
	{
		//进行延时，可以让两个写数据的线程交替运行。
		usleep(200);
		data->m_ids.push_back(1);
	}
	pthread_mutex_unlock(&data->m_lock);
	return (void*)0;
}

void* AddData2(void* arg)
{
	Data* data = (Data*)arg;
	if(NULL == data)
		return (void*)-2;
	pthread_mutex_lock(&data->m_lock);
	for(int i = 0; i < 20; i++)
	{
		usleep(200);
		data->m_ids.push_back(2);
	}
	pthread_mutex_unlock(&data->m_lock);
	return (void*)1;
}

int main()
{
	Data data;
	pthread_mutex_init(&data.m_lock, NULL);
	pthread_t tid_read;
	pthread_t tid_write1;
	pthread_t tid_write2;

	int err = 0;
	cout << "before create thread" << endl;
	err = pthread_create(&tid_write1, NULL, AddData1, (void*)&data);
	if(err != 0)
	{
		cout << "create tid_write error!" << endl;
	}

	err = pthread_create(&tid_write2, NULL, AddData2, (void*)&data);
	if(err != 0)
	{
		cout << "create tid_write2 error!" << endl;
	}

	err = pthread_create(&tid_read, NULL, PrintData, (void*)&data);
	if(err != 0)
	{
		cout << "create tid_read error!" << endl;
	}
	
	//此处的pthread_join一定要加，否则新创建的线程未执行完毕，主线程将不会阻塞，则直接运行到pthread_mutex_destroy销毁掉互斥锁。新线程里面的互斥锁将不再生效。
	pthread_join(tid_write1, NULL);
	pthread_join(tid_write2, NULL);
	pthread_join(tid_read, NULL);

	pthread_mutex_destroy(&data.m_lock);
	sleep(4);

	return 0;
}
