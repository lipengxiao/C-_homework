#ifndef _SQSTACK_H_
#define _SQSTACK_H_

#include "MazeNode.h"

class SqStack
{
public:
	SqStack(int size=100)
		:_size(size)
		,_top(0)
	{
		_pStack = new MazeNode[_size];
	}
	~SqStack()
	{
		delete []_pStack;
		_pStack = NULL;
	}
	void push(MazeNode &node)
	{
		if(full())
			resize();
		_pStack[_top++] = node;
	}
	void pop()
	{
		if(empty())
			return;
		_top--;
	}

	MazeNode& gettop()
	{
		return _pStack[_top-1];
	}
	
	bool full(){return _top == _size;}
	bool empty(){return _top == 0;}
private:
	MazeNode *_pStack;
	int _top;
	int _size;

	void resize()
	{
		MazeNode *ptmp = new MazeNode[_size*2];
		memcpy(ptmp, _pStack, sizeof(MazeNode)*_size);
		_size *= 2;
		delete []_pStack;
		_pStack = ptmp;
	}
};


#endif