#include <iostream>
using namespace std;

#if 0
template<typename T>
class CComplex
{
public:
	CComplex(T r = T(), T i = T())
		:mreal(r),mimage(i){}

private:
	T mreal;
	T mimage;

	friend CComplex<T>  operator+<T>( CComplex<T> const&first, CComplex<T> const&second);


	friend ostream& operator<<<T>(ostream &out, CComplex<T> const&src);
};
//提供全局的operator+
template<typename T>
CComplex<T> operator+<T>(CComplex<T> const&first, CComplex<T> const&second)
{
	return CComplex<T>(first.mreal+second.mreal,first.mimage+second.mimage);
}
//提供全局的operator<<

template<typename T>
ostream& operator<<<T>(ostream &out, CComplex<T> const&src)
{
	out<<"mreal:"<<src.mreal<<"mimige:"<<src.mimage;
	return &out;
}

int main()
{
//http://www.lnmpweb.cn/archives/1049 

//https://teddysun.com/486.html 


	return 0;
}

#endif


class CComplex
{
public:
	CComplex(int r=10, int i=10)
		:mreal(r), mimage(i){}
	CComplex(const CComplex &src)
		:mreal(src.mreal), mimage(src.mimage){}
	CComplex& operator=(const CComplex &src)
	{
		mreal = src.mreal;
		mimage = src.mimage;
		return *this;
	}
	void show()
	{
		cout<<"real:"<<mreal<<" image:"<<mimage<<endl;
	}
	//comp3 = comp2++;
	CComplex operator++(int)//后置++
	{
		return CComplex(mreal++,mimage++);
	}
	CComplex& operator++()//前置++
	{
		++mreal;
		++mimage;
		return *this;
	}
//	comp3 += comp2;
	CComplex& operator+=(const CComplex &src)
	{
		mreal += src.mreal;
		mimage += src.mimage;
		return *this;
	}
private:
	int mreal;
	int mimage;
	friend CComplex operator+(const CComplex &lhs, const CComplex &rhs);
	friend ostream& operator<<(ostream &out,const CComplex &src);
	friend istream& operator>>(istream &in, CComplex &src);
};
//全局运算符重载函数
CComplex operator+(const CComplex &lhs, const CComplex &rhs)
{
	return CComplex(lhs.mreal+rhs.mreal,lhs.mimage+rhs.mimage);
}

ostream& operator<<(ostream &out,const CComplex &src)
{
	out<<"real:"<<src.mreal<<"image:"<<src.mimage;
	return out;
}
//cin>>comp4>>comp3;
istream& operator>>(istream &in, CComplex &src)
{
	in>>src.mreal>>src.mimage;
	return in;
}

int main(int argc, char* argv[])
{
	CComplex comp1(10, 10);
	CComplex comp2(20, 20);
	CComplex comp3 = comp2;  // CComplex comp3(comp2);

	comp3.operator=(comp2);
	comp2.operator=(comp1);
	comp3.operator=(comp2.operator=(comp1));
	comp3 = comp2 = comp1;

	//comp2.operator+(comp1)  CComplex  operator+(const CComplex &src)
	CComplex comp4 = comp2 + comp1; 
	comp4.show();

	      //comp2.operator+(10)   =>    ::operator+(comp2, 10)
	comp4 = comp2+10;
	comp4.show();

	comp4 = 20 + comp2; // (int)comp2 => comp2.operator int()
	comp4.show();
	cout<<comp4<<endl;
	
	cout<<"请输入2个实部和2个虚部:"<<endl;
	cin>>comp4>>comp3;
	cout<<comp4<<" "<<comp3<<endl;
	cout<<"*****************"<<endl;
	comp3 = comp2++;
	cout<<comp3<<endl;
	cout<<comp2<<endl;
	comp3 = ++comp2;
	cout<<comp3<<endl;
	cout<<comp2<<endl;
	cout<<"++++++"<<endl;
	comp3 += comp2 += comp1;
	cout<<comp3<<endl;
	cout<<"###########"<<endl;

	return 0;
}