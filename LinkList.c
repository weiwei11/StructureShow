#include "dataAndStructure.h"
//和链表有关的操作 

/*
	@函数名称：LinkList_search
	@入口参数：链表（LinkList），要查找的关键字（int），是否带头节点（int） 
	@出口参数：所查找到的节点的前驱节点（LinkList） 
	@函数功能：查找第一个与关键字匹配的节点，并返回其前驱节点 
*/
LinkList LinkList_search(LinkList head,int key,int withHeadNode)
{
    LinkList p,pre;

    if(withHeadNode)//是否带头节点 
    {
        p = head->next;
        pre = head;
    }
    else
    {
        p = head;
        pre = NULL;
    }

    while(p != NULL)//遍历链表 
    {
        if(p->data == key) return pre;//查找成功 
        pre = p;
        p = p->next;
    }
    if(p == NULL)return NULL;//查找失败 
}

/*
	@函数名称：LinkList_createNode 
	@入口参数：节点所要保存的数据（int） 
	@出口参数：一个节点（LinkList） 
	@函数功能：创建一个节点 
*/
LinkList LinkList_createNode(int data)
{
	LinkList p = (LinkList)malloc(sizeof(LinkNode));
	p->data = data;
	return p;
} 

/*
	@函数名称：LinkList_insert 
	@入口参数：插入的位置（此节点之后）（LinkList），要插入的节点（LinkList） 
	@出口参数：无 
	@函数功能：将一个节点插入到一个节点的后面 
*/
void LinkList_insert(LinkList pre,LinkList p)
{
	if(pre == NULL || p == NULL) return ; 
    p->next = pre->next;
    pre->next = p;
}

/*
	@函数名称：LinkList_insertHead
	@入口参数：链表（LinkList），要插入的节点（LinkList） 
	@出口参数：新链表的头头节点（LinkList） 
	@函数功能：将一个节点插入到链表的头部 
*/
LinkList LinkList_insertHead(LinkList head,LinkList p)
{	
	if(head == NULL || p == NULL) return head;	
    p->next = head;
    head = p;
    return head;
}

/*
	@函数名称：LinkList_delete 
	@入口参数：要删除的节点的前驱节点（LinkList）
	@出口参数：无 
	@函数功能：将一个节点删除 
*/
void LinkList_delete(LinkList pre)
{
    LinkList p;
    
    if(pre == NULL) return ; 
    p = pre->next;

    if(p == NULL) return ;
    pre->next = p->next;
    free(p);
}

/*
	@函数名称：LinkList_deleteHead 
	@入口参数：要删除的头节点（LinkList）
	@出口参数：无 
	@函数功能：将头节点删除，并返回新链表的头节点 
*/
LinkList LinkList_deleteHead(LinkList head)
{
    LinkList p;
    
    if(head == NULL) return NULL; 
    
    p = head;
    head = head->next;

    free(p);
    return head;
}

/*
	@函数名称：LinkList_free 
	@入口参数：要删除的链表（LinkList） 
	@出口参数：无 
	@函数功能：将一个链表删除 
*/
void LinkList_free(LinkList head)
{
    LinkList p;

    while(head != NULL)
    {
        p = head;
        head = head->next;

        free(p);
    }
}

/*
	@函数名称：LinkList_create 
	@入口参数：是否带头节点（int） 
	@出口参数：无 
	@函数功能：创建一个链表 
*/
LinkList LinkList_create(int withHeadNode)
{
    if(withHeadNode) return (LinkList)malloc(sizeof(LinkNode));
    else return NULL;
}


