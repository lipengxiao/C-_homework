#include <iostream>
using namespace std;

#include "public.h"
#include "SqStack.h"
#include "MazeNode.h"

class Maze
{
public:
	Maze(int row, int col)
		:_row(row)
		,_col(col)
	{
		_pMazePath = new MazeNode*[_row];
		for(int i=0; i<_row; ++i)
		{
			_pMazePath[i] = new MazeNode[_col];
		}
	}
	void setPath(int data, int i, int j)
	{
		_pMazePath[i][j].setNode(data, i, j);
	}
	void adjustPath()
	{
		for(int i=0; i<_row; ++i)
		{
			for(int j=0; j<_col; ++j)
			{
				if(_pMazePath[i][j].getValue() == 0)
				{
					//��
					if(j<_col-1 &&
						_pMazePath[i][j+1].getValue() == 0)
					{
						_pMazePath[i][j].setPathState(WAY_EAST, WAY_ENABLE);
					}
					//��
					if(i<_row-1 &&
						_pMazePath[i+1][j].getValue() == 0)
					{
						_pMazePath[i][j].setPathState(WAY_SOUTH, WAY_ENABLE);
					}
					//��
					if(j>0 &&
						_pMazePath[i][j-1].getValue() == 0)
					{
						_pMazePath[i][j].setPathState(WAY_WEST, WAY_ENABLE);
					}
					//��
					if(i>0 &&
						_pMazePath[i-1][j].getValue() == 0)
					{
						_pMazePath[i][j].setPathState(WAY_NORTH, WAY_ENABLE);
					}
				}
			}
		}
	}
	void findMazePath()
	{
		int i=0,j=0;
		_stack.push(_pMazePath[i][j]);
		while (!_stack.empty())
		{
			MazeNode top = _stack.gettop();
			i = top.getrow();
			j = top.getcol();
			if (i == _row-1 && j==_col-1)
			{
				break;
			}
			if (j!= _row-1&&_pMazePath[i][j+1].getValue()==0 && _pMazePath[i][j].getstate(WAY_EAST)==WAY_ENABLE)
			{
				_pMazePath[i][j].setPathState(WAY_EAST,WAY_DISABLE);
				_pMazePath[i][j+1].setPathState(WAY_WEST,WAY_DISABLE);
				_stack.push(_pMazePath[i][j+1]);
				continue;
			}
			if (i != _col-1 && _pMazePath[i+1][j].getValue() == 0 && _pMazePath[i][j].getstate(WAY_SOUTH)==WAY_ENABLE)
			{
				_pMazePath[i][j].setPathState(WAY_SOUTH,WAY_DISABLE);
				_pMazePath[i+1][j].setPathState(WAY_NORTH,WAY_DISABLE);
				_stack.push(_pMazePath[i+1][j]);
				continue;
			}
			if (j!=0 && _pMazePath[i][j-1].getValue() == 0 && _pMazePath[i][j].getstate(WAY_WEST) == WAY_ENABLE)
			{
				_pMazePath[i][j-1].setPathState(WAY_WEST,WAY_DISABLE);
				_pMazePath[i][j].setPathState(WAY_EAST,WAY_DISABLE);
				_stack.push(_pMazePath[i][j-1]);
				continue;
			}
			if (i != 0 && _pMazePath[i-1][j].getValue() == 0 && _pMazePath[i][j].getstate(WAY_NORTH) == WAY_ENABLE)
			{
				_pMazePath[i][j].setPathState(WAY_NORTH,WAY_DISABLE);
				_pMazePath[i-1][j].setPathState(WAY_SOUTH,WAY_DISABLE);
				_stack.push(_pMazePath[i-1][j]);
				continue;
			}
			_stack.pop();
		}
	}
	
	void showMazePath()
	{
		if (_stack.empty())
		{
			cout<<"���Թ���·������!"<<endl;
			return;
		}
		changePathInfo();
		cout<<"�Թ�·������"<<endl;
		for (int i=0;i<_row;i++)
		{
			for (int j=0;j<_col;j++)
			{
				cout<<_pMazePath[i][j].getValue()<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
	}
private:
	int _row;
	int _col;
	MazeNode **_pMazePath;
	SqStack _stack;
	void changePathInfo()
	{
		if (_stack.empty())
		{
			return;
		}
		int i=0,j=0;
		while (!_stack.empty())
		{
			MazeNode top = _stack.gettop();
			i = top.getrow();
			j = top.getcol();
			_pMazePath[i][j].setValue(2);
			_stack.pop();
		}
	}
};

int main()
{
	int row, col, data;

	cout<<"�������Թ�������:";
	cin>>row>>col;

	Maze maze(row, col);

	cout<<"�������Թ�·��:"<<endl;

	for(int i=0; i<row; ++i)
	{
		for(int j=0; j<col; ++j)
		{
			cin>>data;
			maze.setPath(data, i, j);
		}
	}

	//�����Թ�·��
	maze.adjustPath();
	//��ʼѰ��·��
	maze.findMazePath();
	//��ӡ���
	maze.showMazePath();
	return 0;
}






















#if 0
class Test
{
public:  // Test t1;  Test t2(20);   Test t3(20, 20);
	Test(int a=10, int b=10)
		:ma(a), mb(b)
	{
		cout<<"Test(int, int)"<<endl;
	}
	Test(const Test &src)
		:ma(src.ma), mb(src.mb)
	{
		cout<<"Test(const Test&)"<<endl;
	}
	void operator=(const Test &src)
	{
		ma = src.ma;
		mb = src.mb;
		cout<<"operator="<<endl;
	}
	~Test()
	{
		cout<<"~Test()"<<endl;
	}
private:
	int ma;
	int mb;
};
int main()
{
	Test t1(20, 20);
	Test t2(t1);
	Test t3 = t1;
	//Test(30, 30)  ������ʱ����  ֻ�������ڵ�������  ;  ,  ?
	//Test t4(30, 30); 
	//����ʱ������ͬ���͵��¶�����ʱ����ͱ�C++���������Ż���
	//ֱ�ӹ����¶���Ϳ���
	Test t4 = Test(30, 30);
	t4 = Test(30, 30);
	/*
	other   =>   ������   ������(other)
	������   =>    other    operator other
	*/
	t4 = (Test)(30, 30);  //(Test)30;  <=> Test(30)
	//
	t4 = 40;
	//��ʱ�������ú��������ھͱ�����ñ�������������
	Test &p2 = Test(50, 50);
	Test *p1 = &Test(50, 50);
	
	return 0;
}




class Date
{
public:
	Date(int y, int m, int d)
	{
		this->y = y;
		this->m = m;
		this->d = d;
	}
private:
	int y;
	int m;
	int d;
};
class Test
{
public:
	Test(int data=10):mb(data), ma(data)
	{

	}
	void show()
	{
		cout<<ma<<" "<<mb<<endl;
	}
// 	void operator=(const Test &src)
// 	{
// 		ma = src.ma;
// 		mb = src.mb;
// 	}
private:
	int ma;
	int &mb;
	const int mc;
	//Date date;  1.��Ա����
};
int main()
{
	Test t1;
	t1.show();

	Test t2(t1);
	//Test t3 = t1;

	//��operator =�������ڡ�Test���в�����
	t2 = t1;

	return 0;
}


class CGoods
{
public:
	CGoods()
	{
	}
	CGoods(char *n, int a, double p)
	{
	}
	~CGoods()
	{
	}
private:
	char *_pname;
	int _amount;
	double _price;
};
CGoods good4; // 6
int main(int argc, char* argv[])
{
	CGoods good1;  // 1 
	CGoods good2("xxx", 20, 8.5); // 2

	CGoods *p1 = new CGoods(); // 3
	CGoods *p2 = new CGoods; // 4
	CGoods *p3 = new CGoods("xxx", 20, 8.5); // 5

	//free(p1);
	delete p1;  // 
	delete p2;
	delete p3;

	return 0;
}
CGoods good5("xxx", 20, 8.5);  // 7
#endif

