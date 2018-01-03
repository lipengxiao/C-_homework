#include <iostream>
#include<stdlib.h>
#include<time.h>
//#include<vld.h>//内存泄漏检测
using namespace std;

//用OOP实现循环队列   内存的自增
class CircleQueue
{
public:
	CircleQueue(int size=20)
	{
		pQueue = new int[size];
		_front = 0;
		_rear = 0;
		_size = size;
	}

	CircleQueue(const CircleQueue &src)
	{
		pQueue = new int[src._size];
//		memcpy(pQueue,src.pQueue,sizeof(int)*src._size);//考虑有效数据的拷贝
		
		_front = src._front;
		_rear = src._rear;
		_size = src._size;
		for (int i=_front;i<_rear;i=(i+1)%_size)
		{
			pQueue[i] = src.pQueue[i];
		}
	}

	void operator=(const CircleQueue &src)
	{
		if (this == &src)
		{
			return;
		}
		delete []pQueue;
		pQueue = new int[src._size];
		/*memcpy(pQueue,src.pQueue,sizeof(int)*src._size);*/
		_front = src._front;
		_rear = src._rear;
		_size = src._size;
		for (int i=_front;i<_rear;i=(i+1)%_size)
		{
			pQueue[i] = src.pQueue[i];
		}
	}

	~CircleQueue()
	{
		delete []pQueue;
		pQueue = NULL;
	}

	void addQue(int data)
	{
		if ((_rear+1)%_size == _front)
		{
			resize();
		}
		pQueue[_rear] = data;
		_rear = (_rear+1)%_size;
	}

	void delQue()
	{
		if (_rear == _front)
		{
			return;
		}
		_front = (_front+1)%_size;
	}

	int front()
	{
		return pQueue[_front];
	}

	int back()
	{
		return pQueue[(_rear-1+_size)%_size];
	}
	void show()
	{
		for (int i=_front;i<_rear;i++)
		{
			cout<<pQueue[i]<<" ";
		}
		cout<<endl;
	}
private:
	int *pQueue;
	int _front;
	int _rear;
	int _size;

	void resize()
	{
		int *temp = new int[_size*2];
//		memcpy(temp,pQueue,sizeof(int)*_rear);//考虑队头如果在队尾前面
		int j =0;
		for(int i=_front,j=0;i != _rear;i = (i+1)%_size,j++)
		{
			temp[i] = pQueue[i];
		}
		_front =0;
		_rear = j;
		_size *=2; 
		delete []pQueue;
		pQueue = temp;
	}
};

int main()
{
	CircleQueue cq;
//	srand(time(0));
	int i=0;
	for (i=0;i<24;i++)
	{
		cq.addQue(rand()%100);
	}
	cq.show();
	cout<<"cq.front():"<<cq.front()<<" "<<"cq.back():"<<cq.back()<<endl;
	
	CircleQueue cq_2 = cq;
	cq_2.show();
	CircleQueue cq_3;
	cq_3 = cq_2;
	cq_3.show();
	cq_3.addQue(66);
	cq_2.delQue();
	cq_2.show();
	cq_3.show();
	return 0;
}
