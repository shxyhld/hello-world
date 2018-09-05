#include <iostream>
#include <queue>
using namespace std;
typedef int (*FuncPointType)(int num);
int FuncTest1(int num)
{
	cout << "call FuncTest1! param = " << num << endl;
	return num;
}
int FuncTest2(int num)
{
	cout << "call FuncTest2! param = " << num << endl;
	return num;
}

//回调信息:由回调方法和回调方法对应的参数构成。
struct CallBackInfo
{
	CallBackInfo():m_func(0),m_num(0)
	{}
	CallBackInfo(FuncPointType func, int num):m_func(func),m_num(num)
	{}
	FuncPointType m_func;
	int m_num;
};
//任务信息：主要维护一个任务队列，提供添加任务和执行任务的功能。
struct TaskInfo
{
	//添加任务：形参列表由函数指针和其对应的参数构成，由形参构造成一个回调信息，添加到任务队列中。
	void AddTask(FuncPointType func, int num)
	{
		CallBackInfo call_back_info(func, num);
		m_tasks.push(call_back_info);
	}
	//执行任务：任务列表不为空，则执行任务。
	//执行任务即调用回调信息里的函数指针实际指向的函数，其参数为回调信息里的m_num。
	void Run()
	{
		while(m_tasks.size())
		{
			CallBackInfo call_back = m_tasks.front();
			m_tasks.pop();
			call_back.m_func(call_back.m_num);
		}
	}
	queue<CallBackInfo> m_tasks;
};

int main()
{
	//以下分别将FuncTest1和FuncTest2分别赋值给FuncPointType类型的函数指针f1,并且通过f1分别调用这两个函数。
	//此处需要注意的是，函数类型一定要一致（函数的返回值，形参列表要一样）。
	FuncPointType f1 = 0;
	f1 = FuncTest1;
	cout << f1(1) << endl;
	//通过函数名直接赋值和通过函数名取地址符（&）效果是一样的。
	f1 = &FuncTest2;
	cout << f1(2) << endl;
	
	//下面的例子用来演示将函数指针作为参数，进行传递。
	TaskInfo task_info;
	task_info.AddTask(FuncTest1, 1);
	task_info.AddTask(FuncTest1, 2);
	
	task_info.AddTask(FuncTest2, 3);
	task_info.AddTask(FuncTest2, 4);
	
	task_info.Run();
	return 0;
}
