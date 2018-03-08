#include "dataAndStructure.h"
//和顺序表有关的操作 

/*
	@函数名称：SequList_search
	@入口参数：顺序表（int[]）及长度（int），要查找的关键字（int） 
	@出口参数：成功则返回其索引（int），失败则返回-1 
	@函数功能：在顺序表中搜索一个关键字 
*/
int SequList_search(int * ls,int length,int key)
{
	int i;
	for(i=0;i<length;i++)
	{
		if(ls[i] == key) return i;
	}
	return -1;
}

/*
	@函数名称：SequList_binarySearch 
	@入口参数：顺序表（int[]），查找的范围left~right（int），查找的关键字（int），用于比较的函数 
	@出口参数：成功则返回其索引（int），失败则返回-1
	@函数功能：在一个有序的顺序表中利用二分法查找一个关键字 
*/
int SequList_binarySearch(int * ls,int left,int right,int key,int (*fun)(int a,int b))
{
	int mid;
	int result;
	while(left > right)
	{
		mid = (left + right) / 2;
		
		result = fun(key,ls[mid]);//比较的结果 
		if(result == 0) return mid;
		else if(result < 0) right = mid - 1;
		else left = mid + 1;
	}
	return -1;
}

/*
	@函数名称：compareMax 
	@入口参数：要比较的数a和b（int） 
	@出口参数：a和b的差，即如果a大于b则返回正数，等于则返回0，小于则返回负数 
	@函数功能：比较两个数的大小 
*/
int compareMax(int a,int b)
{
	return a - b;
}

/*
	@函数名称：compareMin 
	@入口参数：要比较的数a和b（int） 
	@出口参数：b和a的差，即如果a小于b则返回正数，等于则返回0，大于则返回负数 
	@函数功能：比较两个数的大小 
*/
int compareMin(int a,int b)
{
	return b - a;
}

/*
	@函数名称：SequList_insert
	@入口参数：顺序表（int[]）和顺序表的长度，插入的地方（int）和插入的数（int） 
	@出口参数：无 
	@函数功能：在顺序表中插入一个数 
*/
void SequList_insert(int * ls,int length,int index,int key)
{
	int i = length;
	if(index < 0) return ;
	
	for(;i>index;i--)
	{
		ls[i] = ls[i-1];
	}
	ls[i] = key;
}

/*
	@函数名称：SequList_delete
	@入口参数：顺序表（int[]）和长度（int），要删除的数的位置（int） 
	@出口参数：无 
	@函数功能：删除顺序表中的一个数 
*/
void SequList_delete(int * ls,int length,int index)
{
	if(index < 0 || index >= length) return ;
	
	int key = ls[index];
	for(;index<length-1;index++)
	{
		ls[index] = ls[index+1];
	}
}

/*
	@函数名称：SequList_exchange
	@入口参数：顺序表（int[]），要交换的两个数的索引（int） 
	@出口参数：无 
	@函数功能：交换两个数 
*/
void SequList_exchange(int * ls,int index1,int index2)
{
	int t;
	
	if(index1 < 0 || index2 < 0) return ; 
	t = ls[index1];
	ls[index1] = ls[index2];
	ls[index2] = t; 
} 


