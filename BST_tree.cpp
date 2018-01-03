#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <deque>
#include <stack>
#include <queue>
#include <functional>
#include <algorithm>
#include <time.h>
#include<set>
using namespace std;
template<typename T>
class BSTree
{
public:
	//构造，不带头结点
	BSTree():_proot(NULL){}
	//BST树的插入操作
	void insert(const T &val)
	{
		BSNode *pcur = _proot;
		BSNode *slow = _proot;
		if (pcur == NULL)//树是空的
		{
			_proot = new BSNode(val);
			return;
		}
		while (pcur != NULL)
		{
			slow = pcur;
			if (val > pcur->_data)
			{
				pcur = pcur->_pright;
			}
			else
			{
				pcur = pcur->_pleft;
			}
		}
		if (slow->_data == val)
		{
			return;
		}
		else if (slow->_data > val)
		{
			slow->_pleft = new BSNode(val);
		}
		else
		{
			slow->_pright = new BSNode(val);
		}
	}
	//BST树的查询操作
	bool query(const T &val)
	{
		BSNode*pcur = _proot;
		while (pcur != NULL)
		{
			if (val == pcur->_data)
			{
				return true;
			}
			else if (val > pcur->_data)
			{
				pcur = pcur->_pright;
			}
			else
			{
				pcur = pcur->_pleft;
			}
		}
		return false;
	}
	//BST树当然删除操作
	
/*bst树删除的三种情况:1.叶子节点
					 2.只有一颗子树
					 3.有两颗子树:①用当前节点的前驱或者后继节点，和当前的值互换
*/	
	void remove(const T &val)
	{
		bool mark = false;
		BSNode *p = _proot;
		BSNode *parent = NULL;
		while (p != NULL)//查找要删除的节点
		{
			if (val == p->_data)
			{
				mark = true;
				break;
			}
			else
			{
				parent = p;                      //记录val节点的父节点
				if (val > p->_data)
				{
					p = p->_pright;
				}
				else
				{
					p = p->_pleft;
				}
			}
		}                
		if (mark)                          //如果找到了
		{ 
			if (parent == NULL)                     //当只有一个根节点的时候，删除直接将_proot置NULL
			{
				_proot = NULL;
				delete p;
				return;
			}

			if ((p->_pleft == NULL) && (p->_pright == NULL))//第一种情况：该节点是叶子节点。直接将父节点指向空并且删除掉节点
			{ 
				if (parent->_pleft == p)
				{
					parent->_pleft = NULL;
				}
				else
				{
					parent->_pright = NULL;
				}
				delete p;
				return;
			}
			else if ((p->_pleft != NULL) && (p->_pright != NULL))  //第二种情况：该节点有左右节点，找到左或者右孩子中最小或者最大的节点的值与该节点的值交换，然后删除叶子
			{
				BSNode *tmp = p->_pleft;                      //tmp用于寻找左右孩子最小或者最大的节点
				while (tmp->_pright != NULL)
				{
					parent = tmp;                    //记录tmp节点的父节点
					tmp = tmp->_pright;                   
				}
				tmp->_data = p->_data;                //交换该节点和找到的tmp节点的数据
				if (parent->_pleft == tmp)
				{
					parent->_pleft = NULL;
				}
				else
				{
					parent->_pright = NULL;
				}
				delete tmp;
				return;
			}
			else                                                 //第三种情况：该节点只有左孩子或者右孩子，只需要将该节点父节点指向其子节点
			{ 
				if (p->_pleft != NULL)                    //只有左孩子
				{
					if (parent->_pleft == p)                     //将其父节点指向其左孩子
					{ 
						parent->_pleft = p->_pleft;               
						delete p;
						return;
					}
					else
					{
						parent->_pright = p->_pleft;
						delete p;
						return;
					}
				}
				if (p->_pright != NULL)                    //只有右孩子
				{
					if (parent->_pleft == p)                //将其父节点指向其右孩子
					{
						parent->_pleft = p->_pright;
						delete p;
						return;
					}
					else
					{
						parent->_pright = p->_pright;
						delete p;
						return;
					}
				}
			}
		}
		else                            //如果没找到
		{
			cout << "没有这个元素!" << endl;
			return;
		}
	}
	bool empty()const
	{
		return _proot == NULL;
	}
	//返回BST树元素的个数
	int size()const
	{
		int sum = 0;
		stack<BSNode*> _stack;
		BSNode *pcur = _proot;
		sum++;
		_stack.push(pcur);
		while (!_stack.empty())
		{
			while (pcur->_pleft != NULL)
			{
				pcur = pcur->_pleft;
				sum++;
				_stack.push(pcur);
			}
			pcur = _stack.top();
			_stack.pop();

			if(pcur->_pright != NULL)
			{
				pcur =pcur->_pright;
				sum++;
				_stack.push(pcur);
			}
		}
		return sum;
	}
	void middle_show()//中序遍历
	{
		stack<BSNode*> _stack;
		BSNode *pcur = _proot;
		_stack.push(pcur);
		while (!_stack.empty())
		{
			while (pcur->_pleft != NULL)
			{
				pcur = pcur->_pleft;
				_stack.push(pcur);
			}
			cout<<_stack.top()->_data<<" ";
			pcur = _stack.top();
			_stack.pop();
			
			if(pcur->_pright != NULL)
			{
				pcur =pcur->_pright;
				_stack.push(pcur);
			}
		}
		cout<<endl;
	}
	void level_show()//层序遍历
	{
		queue<BSNode*>que;
		BSNode*pcur = _proot;
		while (pcur != NULL || !que.empty())
		{
			cout<<pcur->_data<<" ";
			if (pcur->_pleft != NULL)
			{
				que.push(pcur->_pleft);
			}
			if (pcur->_pright != NULL)
			{
				que.push(pcur->_pright);
			}
			if (!que.empty())
			{
				pcur = que.front();
				que.pop();
			}
			else
			{
				pcur = NULL;
			}
		}
		cout<<endl;
	}
private:
	struct BSNode
	{
		BSNode(T data = T()):_data(data),_pleft(NULL),_pright(NULL){}
		T _data;
		BSNode *_pleft;
		BSNode *_pright;
	};

	BSNode *_proot;
	//LVR
	void middle_show(BSNode *proot)
	{
		if(proot != NULL)
		{
			middle_show(proot->_pleft);
			cout<<proot->_data<<" ";
			middle_show(proot->_pright);
		}
	}
};

int main()
{
	BSTree<int> tree;
	tree.insert(29);
	tree.insert(14);
	tree.insert(47);
	tree.insert(4);
	tree.insert(18);
	tree.insert(35);
	tree.insert(69);
	tree.insert(9);
	tree.insert(23);
	tree.insert(52);
	tree.insert(73);
	tree.middle_show();
	tree.level_show();
	cout<<tree.size()<<endl;
	if (tree.query(29))
	{
		cout<<"find"<<endl;
	}
	return 0;
}
