#include<stdio.h>
#include<vector>
#include <iostream>

using namespace std;


void main()
{
	int i = 0;
	vector<int> v;

	for( i = 0; i < 10; i++ )
	{
		v.push_back( i );//把元素一个一个存入到vector中
	}

	//对存入的数据清空
	for( i = 0; i < v.size(); i++ )//v.size() 表示vector存入元素的个数
	{
		cout << v[ i ] << " "; //把每个元素显示出来
	}
	cont << endl;
}