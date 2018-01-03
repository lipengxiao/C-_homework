#include<iostream>
using namespace std;
/*
vector
*/
template<typename T>
class vector
{
public:
	
	vector(int size=10):_size(size),_cur(-1)
	{
		_pvec=new T[_size];
	}

	~vector()
	{
		delete []_pvec;
		_pvec=NULL;
	}

	vector(const vector<T> &src):_size(src._size),_cur(src._cur)
	{
		_pvec=new T[_size];
		for(int i=0;i<=_cur;i++)
		{
			_pvec[i]=src._pvec[i];
		}
	}

	vector<T>& operator=(const vector<T> &src)
	{
		if(this==&src)
		{
			return *this;
		}
		delete []_pvec;
		_size=src._size;
		_cur=src._cur;
		_pvec=new T[_size];
		for(int i=0;i<=_cur;i++)
		{
			_pvec[i]=src._pvec[i];
		}
		return *this;
	}
	

	void push_back(const T &n)
	{
		if(isfull())
		{
			resize();
		}
		_pvec[++_cur]=n;
	}

	void pop_back()
	{
		if(isempty())
		{
			return ;
		}
		_cur--;
	}

	bool isempty()
	{
		return _cur==-1;
	}

	bool isfull()
	{
		return _size==_cur+1;
	} 

	int getcur()
	{
		return _cur;
	}
	
	class iterator
	{
	public:
		typedef T value_type;
		iterator(T* _pvec):tmp(_pvec){}
		bool operator!=(const iterator &it)
		{
			return tmp!=it.tmp;
		}
		void operator++()
		{
			tmp++;
		}
		bool operator>(const iterator &it)
		{
			return tmp > it.tmp;
		}

		T& operator*()
		{
			return *tmp;
		}
		T& operator+(const iterator &it)
		{
			return *tmp + it.tmp;
		}
		iterator operator+(const int index)
		{
			return iterator(tmp+index);
		}
		int operator-(const iterator &it)
		{
			return tmp - it.tmp;
		}
	private:
		T *tmp;
	};

	iterator begin()
	{
		return iterator(_pvec);
	}

	iterator end()
	{
		return iterator(_pvec+_cur+1);
	}

	T& operator[](int index)
	{
		return _pvec[index];
	}
	const T& operator[](int index)const
	{
		return _pvec[index];
	}
	int size()const
	{
		return _cur+1;
	}
private:
	T *_pvec;
	int _size;
	int _cur;
	void resize()
	{
		T *ptmp=new T[_size*2];
		int i;
		for(i=0;i<=_cur;i++)
		{
			ptmp[i]=_pvec[i];
		}
		_size*=2;
		_cur=i-1;
		delete []_pvec;
		_pvec=ptmp;
	}
};

template<typename Container>
void showContainer(Container &con)
{
	Container::iterator it=con.begin();
	for(;it!=con.end();++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}



template<typename T>
class compare_greater
{
public:
	typedef T value_type;
	bool operator()(const T&src,const T&des)
	{
		return src > des;
	}
};

template<typename T>
class compare_less
{
public:
	typedef T value_type;
	bool operator()(T&src,T&des)
	{
		return src < des;
	}
};

template<typename Iterator,typename Compare>
void mysort(Iterator first, Iterator last,Compare &comp)
{
	Iterator::value_type tmp;
	int size = last-first;
	for(int i=0; i<size-1; ++i)
	{
		for(int j=0; j<size-1-i; ++j)
		{
			if(comp(*(first+j) , *(first+j+1)))
			{
				tmp = *(first+j);
				*(first+j) = *(first+j+1);
				*(first+j+1) = tmp;
			}
		}
	}
}

//泛型算法
template<typename T>
bool _greater(T src,T des)
{
	return src > des;
}

template<typename T>
bool _less(T src,T des)
{
	return src < des;
}
////////////////////////////带函数指针的泛型算法
template<typename Iterator>
void mysort(Iterator first, Iterator last, 
			bool (*pfunc)(typename Iterator::value_type, 
			typename Iterator::value_type))
{
	Iterator::value_type tmp;
	int size = last-first;
	for(int i=0; i<size-1; ++i)
	{
		for(int j=0; j<size-1-i; ++j)
		{
			if(pfunc(*(first+j) , *(first+j+1)))
			{
				tmp = *(first+j);
				*(first+j) = *(first+j+1);
				*(first+j+1) = tmp;
			}
		}
	}
}


//函数对象 仿函数

template<typename Iterator, typename T>
Iterator myfind(Iterator first, Iterator last, const T &val)
{
	for (;first != last;++first)
	{
		if (*first == val)
		{
			return first;
		}
	}
	return last;
}


template<typename Iterator,typename Compare>
Iterator myfind_if(Iterator first,Iterator last,Compare &comp)
{
	for (;first != last;++first)
	{
		if (comp(*first))
		{
			return first;
		}
	}
	return last;
}


template<typename Compare,typename T>
class _mybind1st
{
public:
	typedef T value_type;
	_mybind1st(Compare &comp,const T &val)
		:_comp(comp),_val(val){}
	bool operator()(const T&val)
	{
		return _comp(_val,val);
	}
private:
	Compare &_comp;
	T _val;
};

template<typename Compare, typename T>
_mybind1st<Compare,T> mybind1st(Compare &comp, const T &val)
{
	return _mybind1st<Compare,T>(comp, val);
}

int main()
{
	vector<int> vec1;
	for(int i=0;i<20;i++)
	{
		vec1.push_back(rand()%100);
	}
	showContainer(vec1);

	int size = vec1.size();
	for(int i=0; i<size; ++i)
	{
		cout<<vec1[i]<<" ";
	}
	cout<<endl;

	mysort(vec1.begin(), vec1.end(),_greater<int>);
	showContainer(vec1);
	mysort(vec1.begin(), vec1.end(),_less<int>);
	showContainer(vec1);
	compare_greater<int> comp;
	mysort(vec1.begin(), vec1.end(),comp);
	showContainer(vec1);
	
	compare_less<int>com_less;
	mysort(vec1.begin(), vec1.end(),com_less);
	showContainer(vec1);
	vector<int>::iterator it =  myfind(vec1.begin(),vec1.end(),41);
	if (it != vec1.end())
	{
		cout<<"ok"<<endl;
	}
	vector<int>::iterator it2 = myfind_if(vec1.begin(),vec1.end(),mybind1st(compare_greater<int>(),50));
	if (it2 != vec1.end())
	{
		cout<<"第一个小于50的数是:"<<*it2<<endl;
	}
	return 0;
}