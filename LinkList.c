#include "dataAndStructure.h"
//�������йصĲ��� 

/*
	@�������ƣ�LinkList_search
	@��ڲ���������LinkList����Ҫ���ҵĹؼ��֣�int�����Ƿ��ͷ�ڵ㣨int�� 
	@���ڲ����������ҵ��Ľڵ��ǰ���ڵ㣨LinkList�� 
	@�������ܣ����ҵ�һ����ؼ���ƥ��Ľڵ㣬��������ǰ���ڵ� 
*/
LinkList LinkList_search(LinkList head,int key,int withHeadNode)
{
    LinkList p,pre;

    if(withHeadNode)//�Ƿ��ͷ�ڵ� 
    {
        p = head->next;
        pre = head;
    }
    else
    {
        p = head;
        pre = NULL;
    }

    while(p != NULL)//�������� 
    {
        if(p->data == key) return pre;//���ҳɹ� 
        pre = p;
        p = p->next;
    }
    if(p == NULL)return NULL;//����ʧ�� 
}

/*
	@�������ƣ�LinkList_createNode 
	@��ڲ������ڵ���Ҫ��������ݣ�int�� 
	@���ڲ�����һ���ڵ㣨LinkList�� 
	@�������ܣ�����һ���ڵ� 
*/
LinkList LinkList_createNode(int data)
{
	LinkList p = (LinkList)malloc(sizeof(LinkNode));
	p->data = data;
	return p;
} 

/*
	@�������ƣ�LinkList_insert 
	@��ڲ����������λ�ã��˽ڵ�֮�󣩣�LinkList����Ҫ����Ľڵ㣨LinkList�� 
	@���ڲ������� 
	@�������ܣ���һ���ڵ���뵽һ���ڵ�ĺ��� 
*/
void LinkList_insert(LinkList pre,LinkList p)
{
	if(pre == NULL || p == NULL) return ; 
    p->next = pre->next;
    pre->next = p;
}

/*
	@�������ƣ�LinkList_insertHead
	@��ڲ���������LinkList����Ҫ����Ľڵ㣨LinkList�� 
	@���ڲ������������ͷͷ�ڵ㣨LinkList�� 
	@�������ܣ���һ���ڵ���뵽�����ͷ�� 
*/
LinkList LinkList_insertHead(LinkList head,LinkList p)
{	
	if(head == NULL || p == NULL) return head;	
    p->next = head;
    head = p;
    return head;
}

/*
	@�������ƣ�LinkList_delete 
	@��ڲ�����Ҫɾ���Ľڵ��ǰ���ڵ㣨LinkList��
	@���ڲ������� 
	@�������ܣ���һ���ڵ�ɾ�� 
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
	@�������ƣ�LinkList_deleteHead 
	@��ڲ�����Ҫɾ����ͷ�ڵ㣨LinkList��
	@���ڲ������� 
	@�������ܣ���ͷ�ڵ�ɾ�����������������ͷ�ڵ� 
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
	@�������ƣ�LinkList_free 
	@��ڲ�����Ҫɾ��������LinkList�� 
	@���ڲ������� 
	@�������ܣ���һ������ɾ�� 
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
	@�������ƣ�LinkList_create 
	@��ڲ������Ƿ��ͷ�ڵ㣨int�� 
	@���ڲ������� 
	@�������ܣ�����һ������ 
*/
LinkList LinkList_create(int withHeadNode)
{
    if(withHeadNode) return (LinkList)malloc(sizeof(LinkNode));
    else return NULL;
}


