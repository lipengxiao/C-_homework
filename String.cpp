#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
//#include<string>
using namespace std;

/*
运算符重载

*/

class CMyString
{
public:
	CMyString(char *ptr = NULL)
	{
		if (ptr == NULL)
		{
			mptr = new char[1];
			*mptr = '\0';
			return;
		}
		mptr = new char[strlen(ptr)+1];
		strcpy(mptr,ptr);
	}
	CMyString(const CMyString &src)
	{
		mptr = new char[strlen(src.mptr)+1];
		strcpy(mptr,src.mptr);
	}
	CMyString& operator=(const CMyString &src)
	{
		if (this == &src)
		{
			return *this;
		}
		delete []mptr;
		mptr = new char[strlen(src.mptr)+1];
		strcpy(mptr,src.mptr);
		return *this;
	}
	~CMyString()
	{
		if (mptr == NULL)
		{
			return;
		}
		delete []mptr;
		mptr = NULL;
	}

	bool operator>(const CMyString &src)
	{
		return strcmp(mptr,src.mptr) > 0;
	}
	bool operator<(const CMyString &src)
	{
		return strcmp(mptr,src.mptr) < 0;
	}
	bool operator==(const CMyString &src)
	{
		return strcmp(mptr,src.mptr) == 0;
	}

	int size()const
	{
		return strlen(mptr);
	}
	char& operator[](int index)   // cout<<str6[i];  str6[i] = 'a';
	{
		if (index < 0||index > strlen(mptr))
		{
			throw "";
		}
		return mptr[index];
	}
	const char* c_str()const
	{
		return mptr;
	}

	class iterator
	{
	public:
		iterator(char*ptr ):_ptr(ptr){}
		bool operator!=(const iterator &src)
		{
			return _ptr != src._ptr;
		}
		void operator++()
		{
			++_ptr;
		}
		char& operator*()
		{
			return *_ptr;
		}
	private:
		char*_ptr;
	};
	iterator begin()
	{
		return iterator(mptr);
	}
	iterator end()
	{
		return iterator(mptr+size());
	}
private:
	char *mptr;
	friend CMyString operator+(const CMyString &lhs, const CMyString &rhs);
	friend istream& operator>>(istream &in, CMyString &src);
	friend ostream& operator<<(ostream &out, const CMyString &src);
};
CMyString operator+(const CMyString &lhs, const CMyString &rhs)
{
	int size = lhs.size()+rhs.size()+1;
	char *ptr = new char[size];
	strcpy(ptr,lhs.mptr);
	strcat(ptr,rhs.mptr);
	CMyString tmp(ptr);
	delete []ptr;
	return tmp;
}
ostream& operator<<(ostream &out, const CMyString &src)
{
	out<<src.mptr;
	return out;
}
istream& operator>>(istream &in, CMyString &src)
{
	char buff[1024] = {0};//??注意万一不够，应该扩容
	in>>buff;
	src = buff;
	return in;
}
int main(int argc, char* argv[])
{
	CMyString str1;
	CMyString str2 = "hello world";   // char*   =>   string
	CMyString str3 = str2;
	CMyString str4 = str3 + " ahaha!";
	CMyString str5 = str4 + str3;
	CMyString str6 = "test:" + str5;

	int size = str6.size();
	for(int i=0; i<size; ++i)
	{
		//  char  operator[](int index)
		cout<<str6[i];
	}
	cout<<endl;

	// string   =>   char*     operator char*(){}
	char buffer[1024] = {0};
	strcpy(buffer, str6.c_str());
	cout<<buffer<<endl;
	cout<<str6<<endl;
	cin>>str6;
	cout<<str6<<endl;
	CMyString::iterator it = str2.begin();
	for (;it != str2.end();++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
	
	return 0;
}
