#include<iostream>
using namespace std;

template<typename T>
class CGrid
{
public:
	CGrid(int w=10, int h=10) 
		:mWidth(w),mHeight(h)
	{
		mpCells = new T *[mWidth];
		for (int i=0;i<mWidth;i++)
		{
			mpCells[i] = new T[mHeight];
			for (int j=0;j<mHeight;j++)
			{
				mpCells[i][j] = T();
			}
		}
	}

	~CGrid() //析构函数
	{
		for (int i=0;i<mWidth;i++)
		{
			delete []mpCells[i];
		}
		delete []mpCells;
	}
	CGrid(const CGrid<T> &src)	//普通拷贝构造函数
		:mWidth(src.mWidth),mHeight(src.mHeight)
	{
		mpCells = new T*[mWidth];
		for(int i=0;i<mWidth;i++)
		{
			mpCells[i] = new T[mHeight];
		}
		for(int i=0;i<mWidth;i++)
		{
			for(int j=0;j<mHeight;j++)
			{
				mpCells[i][j] = src.mpCells[i][j];
			}
		}
	}
	template<typename E>
	CGrid(const CGrid<E> &src)  //拷贝构造函数的模板
	{
		mWidth = src.mWidth;
		mHeight = src.mHeight;
		mpCells = new T*[mWidth];
		for(int i=0;i<mWidth;i++)
		{
			mpCells[i] = new T[mHeight];
		}
		for(int i=0;i<mWidth;i++)
		{
			for(int j=0;j<mHeight;j++)
			{
				mpCells[i][j] = src.mpCells[i][j];
			}
		}
	}
	void operator=(const CGrid<T> &src)    //赋值运算符的重载函数 
	{
		if (this == &src)
		{
			return;
		}
		
		for (int i=0;i<mWidth)
		{
			delete []mpCells[i];
		}
		delete []mpCells;
		mpCells = NULL;
		
		mpCells = new T*[mWidth];
		for(int i=0;i<mWidth;i++)
		{
			mpCells[i] = new T[mHeight];
		}
		for(int i=0;i<mWidth;i++)
		{
			for(int j=0;j<mHeight;j++)
			{
				mpCells[i][j] = src.mpCells[i][j];
			}
		}
	}
	template<typename E>
	void operator=(const CGrid<E> &src)    //赋值运算符的重载函数模板
	{
		for (int i=0;i<mWidth;i++)
		{
			delete []mpCells[i];
		}
		delete []mpCells;
		mpCells = NULL;
		mWidth = src.mWidth;
		mHeight = src.mHeight;
		mpCells = new T*[mWidth];
		for(int i=0;i<mWidth;i++)
		{
			mpCells[i] = new T[mHeight];
		}
		for(int i=0;i<mWidth;i++)
		{
			for(int j=0;j<mHeight;j++)
			{
				mpCells[i][j] = src.mpCells[i][j];
			}
		}
	}
	int getHeight()const
	{
		return mHeight;
	}
	int getWidth()const
	{
		return mWidth;
	}
	T getElement(int x, int y)const
	{
		if (x<0||y<0)
		{
			throw "";
		}
		return mpCells[x][y];
	}
	void setElement(int x, int y, const T &val)
	{
		if (x<0||y<0)
		{
			return;
		}
		mpCells[x][y] = val;
	}
	template<typename T>
	friend class CGrid;
private:
	T **mpCells;
	int mWidth;
	int mHeight;
};
//int main()
//{
//	CGrid<int> intGrid1;
//	CGrid<int> intGrid2(intGrid1);
//
//	CGrid<long> longGrid1(intGrid1);
//
//	longGrid1 = intGrid1;  // CGrid<int>
//	cout<<intGrid1.getElement(0,0)<<endl;
//	intGrid1.setElement(0,0,10);
//	cout<<intGrid1.getElement(0,0)<<endl;
//	return 0;
//}