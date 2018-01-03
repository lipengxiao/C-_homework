#include<iostream>
#include<string.h>
#include<stdlib.h>
#include <vld.h>//检查是否有内存泄漏
using namespace std;

//A.单链表
class Link
{
public:
	Link()
	{
		_phead = new Node;
		cout<<"Link()"<<endl;
	}

	Link(const Link &src)
	{
		_phead = new Node;

		Node *tmp = src._phead->_pnext;
		Node *p = _phead;
		while (tmp != NULL)
		{
			p->_pnext = new Node(tmp->_data);
			p = p->_pnext;
			tmp = tmp->_pnext;
		}
		cout<<"Link(const Link &src)"<<endl;
	}

	Link& operator=(const Link &src)
	{
		cout<<"operator="<<endl;
		if (this == &src)
		{
			return *this;
		}

		delete _phead;

		_phead = new Node;
		Node *tmp = src._phead->_pnext;
		Node *p = _phead;
		while (tmp != NULL)
		{
			p->_pnext = new Node;
			p->_pnext->_data = tmp->_data;
			p = p->_pnext;
			tmp = tmp->_pnext;
		}

		return *this;
	}

	~Link()
	{
		if (_phead == NULL)
		{
			return;
		}

		Node *tmp = _phead->_pnext;
		while (tmp != NULL)
		{
			Node*p = tmp;
			tmp = tmp->_pnext;
			delete p;
		}
		delete _phead;
		cout<<"~Link()"<<endl;
	}
	void insertHead(int val)
	{
		Node *p = new Node(val);
		p->_pnext = _phead->_pnext;
		_phead->_pnext = p;
	}

	void insertTail(int val)
	{
		Node *tmp = _phead;
		while (tmp->_pnext != NULL)
		{
			tmp = tmp->_pnext;
		}
		tmp->_pnext = new Node(val);
	}

	void deleteNode(int val)
	{
		Node *p = _phead->_pnext;
		Node *q = _phead;
		while (p != NULL)
		{
			if (p->_data == val)
			{
				q->_pnext = p->_pnext;
				delete p;
				return;
			}
			q = p;
			p = p->_pnext;
		}
	}
	void showLink()
	{
		Node *p = _phead->_pnext;
		while (p != NULL)
		{
			cout<<p->_data<<" ";
			p = p->_pnext;
		}
		cout<<endl;
	}

private:
	class Node
	{
	public:
		Node(int data = 0):_data(data),_pnext(NULL)
		{}
		int _data;
		Node *_pnext;
	};

	Node *_phead;
};

int main()
{
	Link L;
	for (int i=0;i<5;i++)
	{
		L.insertHead(rand()%10);
	}
	L.insertTail(20);
	L.showLink();
	L.deleteNode(9);
	L.showLink();

	Link L1= L;
	L1.showLink();

	Link L2;
	L2 = L;
	L2.showLink();
	return 0;
}