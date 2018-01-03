#include<iostream>
#include<vector>
#include<list>
#define  NONE -1
using namespace std;

/*
CMYSTRING
vector �ռ�������
hash_map
*/


//ģ��Boost�������hash_map
template<typename K, typename V>
struct mypair
{
	mypair(const K &key, const V &value)
		:first(key), second(value){}
	K first;
	V second;
};
template<typename K, typename V>
mypair<K,V> mymake_pair(const K &key, const V &value)
{
	return mypair<K,V>(key,value);
}
//3   2n+1
template<typename K, typename V>
class HashMap
{
public:
	typedef mypair<K,V> value_type;
	typedef typename list<value_type>::iterator iterator;
	HashMap(int size=3, double threshold=0.75)
		:_threshold(threshold)
	{
		used_size = 0;//��ʹ��Ͱ�ĸ���
		_buckets.resize(size);
		vector<bucket_type>::iterator it = _buckets.begin();
		for(; it != _buckets.end(); ++it)
		{
			it->first = it->last = _values.end();
		}
	}
	//���ϣ�����Ԫ�� ���key�Ѿ����ڣ��µ�value�滻�ɵ�value
	void insert(const value_type &val)
	{
		if (used_size/_buckets.size() > _threshold)//����
		{
			resize();
		}
		int index = val.first % (_buckets.size());
		if (_buckets[index].first == _values.end())//index��Ӧ��Ͱ��û��Ԫ��
		{
			_buckets[index].first = _values.insert(_buckets[index].first,val);
			used_size++;
			return;
		}
		list<value_type>::iterator it = _buckets[index].first;
		for (;it != _values.end();++it)
		{
			if (it->first == val.first)//��ͬ��key���滻
			{
				it->second = val.second;
				return;
			}
		}
		_values.insert(_values.begin(),val);//map��û�к�val��keyһ����Ԫ��
	}
	
	//�ӹ�ϣ��ɾ��Ԫ�� ���key�����ڣ�ֱ�ӷ���
	void erase(const K &key)
	{
		int index = key % _buckets.size();
		list<value_type>::iterator it = _buckets[index].first;
		for (;it != _buckets[index].last;++it)
		{
			if (it->first == key)//��ͬ��key���滻
			{
				_values.erase(it);
				used_size--;
				return;
			}
		}
	}
	//��ѯ��ϣ�����key�����ڣ��׳��쳣
	V find(const K &key)
	{
		int index = key % _buckets.size();
		list<value_type>::iterator it = _buckets[index].first;
		for (;it != _buckets[index].last;++it)
		{
			if (it->first == key)//��ͬ��key,����value
			{
				return it->second;	
			}
		}
		throw "";
	}
	//hashmap[10001] = "xxxxx";
	//1.10001���key�����ڣ� ���ʾ�²���һ���ֵ��
	//2.10001���key������ڣ��µ�value�滻�ɵ�value
	//3.V val = hashmap[10001]����find�Ĺ���
	V& operator[](const K &key)
	{
		int index = key % _buckets.size();
		int tmp = _buckets.size();
		list<value_type>::iterator it = _buckets[index].first;
		if (it == _buckets[index].last)
		{
			it =  _values.insert(it,mymake_pair(key,NONE));//index��Ӧ��Ͱû��Ԫ�أ� ���ʾ�²���һ���ֵ��
			used_size++;
			return it->second;
		}
		for (;it != _buckets[index].last;++it)
		{
			if (it->first == key)//V val = hashmap[10001]����find�Ĺ���
			{
				return it->second;	
			}
		}
		it = _buckets[index].last;
		it = _values.insert(it,mymake_pair(key,NONE));//10001���key�����ڣ� ���ʾ�²���һ���ֵ��
		return it->second;
	}
	void show_list()
	{
		list<value_type>::iterator it  = _values.begin();
		for (;it != _values.end();++it)
		{
			cout<<"key:"<<(*it).first<<" "<<"val:"<<(*it).second<<endl;
		}
	}
private:
	// The type for a bucket in the hash table.
	struct bucket_type
	{
		iterator first;
		iterator last;
	};
	// The list of all values in the hash map.
	list<value_type> _values;
	// The buckets in the hash.
	//bucket_type* buckets_;
	vector<bucket_type> _buckets;
	//��ϣͰ�ĸ�������  0.75
	double _threshold;
	int used_size;
	//��ϣ����������� ��2n+1�ķ�ʽ��������
	void resize()
	{
		size_t bucket_size = _buckets.size();
		_buckets.clear();
		_buckets.resize(bucket_size*2+1);
		for (size_t i=0;i<_buckets.size();++i)
		{
			_buckets[i].first = _buckets[i].last = _values.end();
		}

		list<value_type>::iterator it = _values.begin();
		while (it != _values.end())
		{
			 size_t index = it->first%_buckets.size();
			 if (_buckets[index].first == _buckets[index].last)
			 {
				  _buckets[index].first = _buckets[index].last = it;
				  it++;
			 }
			 else
			 {
				 _values.splice(_buckets[index].last,_values,it++);  
			 }
		}
	}
}; 

int main()
{
	HashMap<int,int> myhash;
	/*insert*/
	for (int i=0;i<5;++i)
	{
		myhash.insert(mymake_pair((i+1),(i+1)*10));
	}
//	myhash.show_list();
	cout<<"************"<<endl;
	myhash.insert(mymake_pair(2,11));
	myhash.show_list();

//	myhash.erase(2);
//	myhash.show_list();

	//cout<<"key��Ӧ��value:"<<myhash.find(3)<<endl;
	myhash[10] = 10;
	myhash.show_list();
	cout<<"myhash[]="<<endl;
	cout<<myhash[2]<<endl;
	myhash[10] = 20;
	//myhash.show_list();
	return 0;
}
#if 0
#endif