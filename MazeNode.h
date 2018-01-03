#ifndef _MAZENODE_H_
#define _MAZENODE_H_

#include "public.h"

class MazeNode
{
public:
	MazeNode()
	{
		for(int i=0; i<WAY_NUMBER; ++i)
		{
			_pathState[i] = WAY_DISABLE;
		}
	}
	void setNode(int value, int i, int j)
	{
		_value = value;
		_i = i;
		_j = j;
	}
	int getValue()
	{
		return _value;
	}
	void setPathState(int path, int state)
	{
		_pathState[path] = state;
	}
	int getstate(int FANGX)
	{
		return _pathState[FANGX];
	}
	int getrow()
	{
		return _i;
	}
	int getcol()
	{
		return _j;
	}
	void setValue(int num)
	{
		_value = num;
	}
private:
	int _value;
	int _i;
	int _j;
	int _pathState[WAY_NUMBER];
};


#endif