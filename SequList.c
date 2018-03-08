#include "dataAndStructure.h"
//��˳����йصĲ��� 

/*
	@�������ƣ�SequList_search
	@��ڲ�����˳���int[]�������ȣ�int����Ҫ���ҵĹؼ��֣�int�� 
	@���ڲ������ɹ��򷵻���������int����ʧ���򷵻�-1 
	@�������ܣ���˳���������һ���ؼ��� 
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
	@�������ƣ�SequList_binarySearch 
	@��ڲ�����˳���int[]�������ҵķ�Χleft~right��int�������ҵĹؼ��֣�int�������ڱȽϵĺ��� 
	@���ڲ������ɹ��򷵻���������int����ʧ���򷵻�-1
	@�������ܣ���һ�������˳��������ö��ַ�����һ���ؼ��� 
*/
int SequList_binarySearch(int * ls,int left,int right,int key,int (*fun)(int a,int b))
{
	int mid;
	int result;
	while(left > right)
	{
		mid = (left + right) / 2;
		
		result = fun(key,ls[mid]);//�ȽϵĽ�� 
		if(result == 0) return mid;
		else if(result < 0) right = mid - 1;
		else left = mid + 1;
	}
	return -1;
}

/*
	@�������ƣ�compareMax 
	@��ڲ�����Ҫ�Ƚϵ���a��b��int�� 
	@���ڲ�����a��b�Ĳ�����a����b�򷵻������������򷵻�0��С���򷵻ظ��� 
	@�������ܣ��Ƚ��������Ĵ�С 
*/
int compareMax(int a,int b)
{
	return a - b;
}

/*
	@�������ƣ�compareMin 
	@��ڲ�����Ҫ�Ƚϵ���a��b��int�� 
	@���ڲ�����b��a�Ĳ�����aС��b�򷵻������������򷵻�0�������򷵻ظ��� 
	@�������ܣ��Ƚ��������Ĵ�С 
*/
int compareMin(int a,int b)
{
	return b - a;
}

/*
	@�������ƣ�SequList_insert
	@��ڲ�����˳���int[]����˳���ĳ��ȣ�����ĵط���int���Ͳ��������int�� 
	@���ڲ������� 
	@�������ܣ���˳����в���һ���� 
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
	@�������ƣ�SequList_delete
	@��ڲ�����˳���int[]���ͳ��ȣ�int����Ҫɾ��������λ�ã�int�� 
	@���ڲ������� 
	@�������ܣ�ɾ��˳����е�һ���� 
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
	@�������ƣ�SequList_exchange
	@��ڲ�����˳���int[]����Ҫ��������������������int�� 
	@���ڲ������� 
	@�������ܣ����������� 
*/
void SequList_exchange(int * ls,int index1,int index2)
{
	int t;
	
	if(index1 < 0 || index2 < 0) return ; 
	t = ls[index1];
	ls[index1] = ls[index2];
	ls[index2] = t; 
} 


