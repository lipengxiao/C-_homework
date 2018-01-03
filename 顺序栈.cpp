#include <iostream>
#include <stdlib.h>
using namespace std;

//À≥–Ú’ªversion 1.0
class SqStack
{
public:
	SqStack():mTop(0)
	{
	}
	void push(int val)
	{
		if (full())
		{
			return;
		}
		mStack[mTop++] = val;
	}

	void pop()
	{
		if (empty())
		{
			return;
		}
		mTop--;
	}

	int top()
	{
		if (full()||empty())
		{
			return -1;
		}
		int tmp = mStack[mTop-1];
		mTop--;
		return tmp;
	}

	bool full()const
	{
		return mTop == STACK_LEN;
	}

	bool empty()const
	{
		return mTop == 0;
	}

	void show()
	{
		if (empty())
		{
			return;
		}
		int i=0;
		while (i<mTop)
		{
			cout<<mStack[i]<<" " ;
			i++;
		}
		cout<<endl;
	}
private:
	enum{STACK_LEN = 10};
	int mStack[STACK_LEN];
	int mTop;
};

int main()
{
	SqStack s1;
	for (int i=0;i<5;i++)
	{
		s1.push(rand()%10);
	}
	s1.show();
	s1.pop();
	s1.show();
	cout<<s1.top()<<endl;
	cout<<s1.top()<<endl;
	s1.show();
	return 0;
}