#include <pthread.h>
#include <vector>
#include <iostream>
#include <unistd.h>
using namespace std;
struct Data
{
	vector<int> m_ids;
};

void* PrintData(void* arg)
{
	Data* data = (Data*)arg;
	if(NULL == data)
		return (void*)-1;
	cout << "tid_read = " << pthread_self() << endl;
	vector<int>::iterator iter = data->m_ids.begin();
	for(; iter != data->m_ids.end(); iter++)
	{
		cout << *iter << ' ';
	}
	cout << endl;

	sleep(2);
	cout << "PrintData After sleep" << endl;
	iter = data->m_ids.begin();
	for(; iter != data->m_ids.end(); iter++)
	{
		cout << *iter << ' ';	
	}
	cout << endl;
	return (void*)0;
}

void* AddData(void* arg)
{
	Data* data = (Data*)arg;
	if(NULL == data)
		return (void*)-2;
	cout << "tid_write = " << pthread_self() << endl;
	for(int i = 0; i < 500; i++)
	{
		if(i == 100)
			sleep(1);
		data->m_ids.push_back(i);
	}
	return (void*)0;
}

int main()
{
	Data data;
	pthread_t tid_read;
	pthread_t tid_write;

	int err = 0;
	cout << "before create thread" << endl;
	err = pthread_create(&tid_write, NULL, AddData, (void*)&data);
	if(err != 0)
	{
		cout << "create tid_write error!" << endl;
	}

	err = pthread_create(&tid_read, NULL, PrintData, (void*)&data);
	if(err != 0)
	{
		cout << "create tid_read error!" << endl;
	}
	slee(5);

	return 0;
}
