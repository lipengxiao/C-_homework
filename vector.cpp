#include<iostream>
//#include<vector>
using namespace std;

template<typename T>
class vector
{
public:
	vector(int size=10):_size(size),_cur(0)
	{
		_pvec = new T[_size];
	}
	//拷贝构造
	vector(const vector<T> &src)
	{
		_pvec = new T[src._size];
		for (int i=0;i<_cur;i++)
		{
			_pvec[i] = src._pvec[i];
		}
	}
	//operator=
	vector<T>& operator=(const vector<T> &src)
	{
		if (this == &src)
		{
			return *this;
		}
		delete []_pvec;
		_pvec = new T[src._cur];
		_size = src._cur;
		for (int i=0;i<_size;i++)
		{
			_pvec[i] = src._pvec[i];
		}
		return *this;
	}
	~vector()
	{
		delete []_pvec;
		_pvec = NULL;
	}

	//从末尾添加元素  参数自己填
	void push_back(const T &val)   
	{
		int tmp = _cur+1;
		if (tmp>=_size)
		{
			resize();
		}
		_pvec[_cur++] = val;
	}
	void pop_back()
	{
		_cur--;
	}
	class iterator
	{
	public:
		iterator(T *ptr = NULL):_ptr(ptr){}
		bool operator!=(const iterator&it)
		{
			return _ptr != it._ptr;
		}
		void operator++()
		{
			_ptr++;
		}
		T& operator*()
		{
			return *_ptr;
		}
	private:
		T *_ptr;
	};

	iterator begin()
	{
		return iterator(_pvec);
	}
	iterator end()
	{
		return iterator(_pvec + _cur);
	}
private:
	T *_pvec;
	int _size;
	int _cur;
	void resize()
	{
		T *pcur = new T[_size*2];
		for (int i=0;i<_size;i++)
		{
			pcur[i] = _pvec[i];
		}
		_size *= 2;
		delete []_pvec;
		_pvec = pcur;
	}
};


int main()
{
	vector<int> intvec;
	for (int i=0;i<21;i++)
	{
		intvec.push_back(rand()%100);
	}
	intvec.pop_back();

	vector<int>::iterator it = intvec.begin();
	for (;it != intvec.end();++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
	return 0;
}
#if 0
#endif