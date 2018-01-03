#include <iostream>
using namespace std;

template<typename T>
class myallocator
{
public:
	typedef T* pointer;

	pointer allocate(size_t _N)
	{
		return (pointer)operator new(_N*sizeof(T)); 
	}
	void construct(pointer _P, const T& _V)
	{
		new (_P) T(_V);
	}

	void destroy(pointer _P)
	{
		_P->~T();
	}
	void deallocate(void  *p)
	{
		operator delete(p);
	}
};

template<typename T, typename A = myallocator<T>>
class vector
{
public:
	vector(int size)
	{
		_first._ptr = _allocator.allocate(size);
		//_Ufill(_first, size, val);
		_last = _first;
		_end = _first + size;
	}
	//拷贝构造
	vector(const vector<T> &src)
	{
		int size = src._last._ptr - src._first._ptr;
		_first._ptr = _allocator.allocate(size);
		_Ucopy(src._first, src._last, _first);
		_last = _first +  size;
		_end = _last;
	}
	//operator=
	vector<T>& operator=(const vector<T> &_X)
	{
		if (this == &_X)
			return *this;

		int size = _X._last._ptr - _X._first._ptr;

		_Destroy(_first, _last);
		_allocator.deallocate(_first._ptr);
		_first._ptr = _allocator.allocate(size);
		_last = _Ucopy(_X._first, _X._last,
			_first);
		_end = _last; 
		return *this;
	}
	~vector()
	{
		_Destroy(_first, _last);
		_allocator.deallocate(_first._ptr);
		_first._ptr = _last._ptr = _end._ptr = NULL;
	}
	//从末尾添加元素  参数自己填
	void push_back(const T &val)   
	{
		if(full())
			resize();
		_Ufill(_last, 1, val);
		++_last;
	}
	bool full()const
	{
		return _last._ptr == _end._ptr;
	}
	bool empty()const
	{
		return _first._ptr == _last._ptr;
	}
	void pop_back()
	{
		if(empty())
			return;
		_Destroy(_last-1, _last);
		--_last;
	}
	size_t size()
	{
		return _last - _first;
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
		void operator--()
		{
			_ptr--;
		}
		T& operator*()
		{
			return *_ptr;
		}
		iterator operator+(size_t size)
		{
			return iterator(_ptr + size);
		}
		iterator operator-(int size)
		{
			return iterator(_ptr - size);
		}
		int operator-(const iterator &it)
		{
			return _ptr - it._ptr;
		}

		T *_ptr;
	};

	iterator begin()
	{
		return iterator(_first);
	}
	iterator end()
	{
		return iterator(_last);
	}
private:
	iterator _first, _last, _end;
	A _allocator;

	void resize()
	{
		T *ptmp = _allocator.allocate(size()*2);
		iterator last = _Ucopy(_first, _last,  ptmp);

		_Destroy(_first, _last);
		_allocator.deallocate(_first._ptr);

		_first = ptmp;
		_last = last;
		_end = _first + size()*2;
	}

	void _Ufill(iterator _F, size_t _N, const T &_X)
	{
		for (; 0 < _N; --_N, ++_F)
			_allocator.construct(_F._ptr, _X);   // operator void*()
	}
	void _Destroy(iterator _F, iterator _L)
	{
		for (; _F != _L; ++_F)
			_allocator.destroy(_F._ptr); 
	}
	iterator _Ucopy(iterator _F, iterator _L,
		iterator _P)
	{
		for (; _F != _L; ++_P, ++_F)
			_allocator.construct(_P._ptr, *_F);
		return (_P); 
	}
};

int main()
{
	vector<int> vec1(100);
	vector<int> vec2(vec1);
	for (int i=0;i<10;++i)
	{
		vec2.push_back(rand()%10);
	}
	vec1.push_back(10);
	vec1.pop_back();
	vec2 = vec1;
	return 0;
}