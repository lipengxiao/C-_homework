#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<string>
#include<stack>
#include<algorithm>//泛型算法
#include<functional>
using namespace  std;




class test
{
public:
	test():_val(-1),_num(0){}
	test(int val,int num):_val(val),_num(num){}
	bool operator>(const test &src)const
	{
		return _num > src._num;
	}
	bool operator<(const test &src)const
	{
		return _num < src._num;
	}
	int _val;
	int _num;
};

int main()
{
	/*
	FILE *pf_1 = fopen("data.txt", "w");
	if(pf_1 == NULL)
		return 0;

	//	srand(time(0));
	for(int i=0; i<10000000; ++i)
	{
		fprintf(pf_1, "%d ", rand()%200);
	}
	fclose(pf_1);

	//分成200个小文件   data%200 = file_index
	const int FILE_SIZE = 200;
	FILE *_pf[FILE_SIZE] = {NULL};
	int data = 0;

	//打开FILE_SIZE个小文件
	for(int i=0; i<FILE_SIZE; ++i)
	{
		char fileName[20]="data";
		// data + i
		char buf[4] = {0};
		itoa(i, buf, 10);
		strcat(fileName, buf);
		_pf[i] = fopen(fileName, "w");
	}


	FILE *pf = fopen("data.txt", "r");
	while(!feof(pf))
	{
		fscanf(pf, "%d", &data);
		int fileIndex = data%FILE_SIZE;
		fprintf(_pf[fileIndex], "%d ", data);
	}

	for(int i=0; i<FILE_SIZE; ++i)
	{
		fclose(_pf[i]);
	}

	*/
	map<int,int>mymap;
	int data = 0;
	const int FILE_SIZE = 200;
	FILE *_pf[FILE_SIZE] = {NULL};
	int flag = 0;
	priority_queue<test , vector<test> ,greater<test>> p_que;
	
	for(int i=0; i<FILE_SIZE; ++i)
	{
		char fileName[20]="data";
		// data + i
		char buf[4] = {0};
		itoa(i, buf, 10);//第三个参数，代表10进制
		strcat(fileName, buf);
		_pf[i] = fopen(fileName, "r");
		while (!feof(_pf[i]))
		{
			fscanf(_pf[i],"%d",&data);
			map<int,int>::iterator it1 = mymap.find(data);
			if (it1 != mymap.end())
			{
				it1->second++;
			}
			else
			{
				mymap.insert(make_pair(data,1)); 
			} 
		}
		fclose(_pf[i]);
		flag += 1;
		map<int,int>::iterator it2 = mymap.begin();
		
		for (int i = 0; it2 != mymap.end(); ++it2, ++i)
		{
			if (flag==1)
			{
				if (i < 10)
				{
					p_que.push(test(it2->first,it2->second));
				}
				else
				{
					if (p_que.top()._num < it2->second)
					{
						p_que.pop();
						p_que.push(test(it2->first, it2->second));
					}
				}
			}
			else
			{
				if (p_que.top()._num < it2->second)
				{
					p_que.pop();
					p_que.push(test(it2->first, it2->second));
				}
			}

		}
		mymap.clear();
	}
	cout<<"重复最大的数字及重复次数:"<<endl;
	cout<<p_que.top()._val<<" ";
	cout<<p_que.top()._num<<" ";
	p_que.pop();
	cout<<endl;
	return 0;
}