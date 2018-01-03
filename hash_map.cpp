#include<iostream>
#include<vector>
#include<list>
#define  NONE -1
using namespace std;

/*
CMYSTRING
vector 空间配置器
hash_map
*/


//模拟Boost库的容器hash_map
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
		used_size = 0;//已使用桶的个数
		_buckets.resize(size);
		vector<bucket_type>::iterator it = _buckets.begin();
		for(; it != _buckets.end(); ++it)
		{
			it->first = it->last = _values.end();
		}
	}
	//向哈希表插入元素 如果key已经存在，新的value替换旧的value
	void insert(const value_type &val)
	{
		if (used_size/_buckets.size() > _threshold)//扩容
		{
			resize();
		}
		int index = val.first % (_buckets.size());
		if (_buckets[index].first == _values.end())//index对应的桶中没有元素
		{
			_buckets[index].first = _values.insert(_buckets[index].first,val);
			used_size++;
			return;
		}
		list<value_type>::iterator it = _buckets[index].first;
		for (;it != _values.end();++it)
		{
			if (it->first == val.first)//相同的key，替换
			{
				it->second = val.second;
				return;
			}
		}
		_values.insert(_values.begin(),val);//map中没有和val的key一样的元素
	}
	
	//从哈希表删除元素 如果key不存在，直接返回
	void erase(const K &key)
	{
		int index = key % _buckets.size();
		list<value_type>::iterator it = _buckets[index].first;
		for (;it != _buckets[index].last;++it)
		{
			if (it->first == key)//相同的key，替换
			{
				_values.erase(it);
				used_size--;
				return;
			}
		}
	}
	//查询哈希表，如果key不存在，抛出异常
	V find(const K &key)
	{
		int index = key % _buckets.size();
		list<value_type>::iterator it = _buckets[index].first;
		for (;it != _buckets[index].last;++it)
		{
			if (it->first == key)//相同的key,返回value
			{
				return it->second;	
			}
		}
		throw "";
	}
	//hashmap[10001] = "xxxxx";
	//1.10001这个key不存在， 这表示新插入一组键值对
	//2.10001这个key如果存在，新的value替换旧的value
	//3.V val = hashmap[10001]还是find的功能
	V& operator[](const K &key)
	{
		int index = key % _buckets.size();
		int tmp = _buckets.size();
		list<value_type>::iterator it = _buckets[index].first;
		if (it == _buckets[index].last)
		{
			it =  _values.insert(it,mymake_pair(key,NONE));//index对应的桶没有元素， 这表示新插入一组键值对
			used_size++;
			return it->second;
		}
		for (;it != _buckets[index].last;++it)
		{
			if (it->first == key)//V val = hashmap[10001]还是find的功能
			{
				return it->second;	
			}
		}
		it = _buckets[index].last;
		it = _values.insert(it,mymake_pair(key,NONE));//10001这个key不存在， 这表示新插入一组键值对
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
	//哈希桶的负载因子  0.75
	double _threshold;
	int used_size;
	//哈希表的增长函数 以2n+1的方式进行增长
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

	//cout<<"key对应的value:"<<myhash.find(3)<<endl;
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