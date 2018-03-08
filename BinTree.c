#include "dataAndStructure.h"
//�Ͷ������йصĲ���

/*
	@�������ƣ�BinTree_preorder
	@��ڲ�����Ҫ�����Ķ�������BinTree�������ڼ�¼���ڵ�ı���˳��ļ�¼���У�BinTree[]�� 
	@���ڲ����������˵����ڵ�ĸ�����int�� 
	@�������ܣ�ʵ�ֶ�������ǰ����� 
*/
int BinTree_preorder(BinTree t,BinTree * queue)
{
	int queueRear = 0; //ָʾ��¼���еĶ�β 
	
	BinTree stack[100];//����һ��ջ
	int top=0;//ջ�����α�
	BinTree p;
	
	if(t == NULL) return 0;//��Ϊ��
	stack[top++] = t;//�����ĸ���ջ
	
	//ջ��Ϊ�գ����Ľڵ��û�б�����
	while(top != 0)
	{
		p = stack[--top];//���ڵ��ջ
		//��¼���м�¼�����Ľڵ�
		queue[queueRear++] = p; 
		 
		//�ҽڵ��Ƚ�ջ����ڵ���ջ���Դ˿����������ڵ�
		if(p->rchild != NULL)
		  	stack[top++] = p->rchild;
		if(p->lchild != NULL)
			stack[top++] = p->lchild;
	}
	return queueRear; //���ر������нڵ�ĸ��� 
}

/*
	@�������ƣ�BinTree_inorder
	@��ڲ�����Ҫ�����Ķ�������BinTree�������ڼ�¼���ڵ�ı���˳��ļ�¼���У�BinTree[]�� 
	@���ڲ����������˵����ڵ�ĸ�����int�� 
	@�������ܣ�ʵ�ֶ�������������� 
*/
int BinTree_inorder(BinTree t,BinTree * queue)
{
	int queueRear = 0; //ָʾ��¼���еĶ�β 
	
	BinTree stack[100];//����һ��ջ
	int top=0;//ջ�����α�
	int isVisited[100]; //��¼һ���ڵ��Ƿ񱻷����ˣ���һ���ڵ�Ķ����ǲ��Ǳ�ѹ��ջ�� 
	BinTree p;
	
	if(t == NULL) return 0;//��Ϊ��
	stack[top] = t;//�����ĸ���ջ
	isVisited[top++] = 0; 
	
	//ջ��Ϊ�գ����Ľڵ��û�б�����
	while(top != 0)
	{
		p = stack[--top];//һ���ڵ��ջ
		//����Ѿ������ʹ�һ�Σ����¼���м�¼�����Ľڵ�
		if(isVisited[top])
		{
			queue[queueRear++] = p;
		}
		else //���Ҷ��ӣ��Լ��������������ջ 
		{ 
			if(p->rchild != NULL)
			{
				isVisited[top] = 0; 
			  	stack[top++] = p->rchild;
			}
			
			isVisited[top] = 1;
			stack[top++] = p;
			
			if(p->lchild != NULL)
			{
				isVisited[top] = 0;
				stack[top++] = p->lchild;
			}	
		} 
	}
	return queueRear; //���ر������нڵ�ĸ���
} 

/*
	@�������ƣ�BinTree_postorder
	@��ڲ�����Ҫ�����Ķ�������BinTree�������ڼ�¼���ڵ�ı���˳��ļ�¼���У�BinTree[]�� 
	@���ڲ����������˵����ڵ�ĸ�����int�� 
	@�������ܣ�ʵ�ֶ������ĺ������ 
*/
int BinTree_postorder(BinTree t,BinTree * queue)
{
	int queueRear = 0; //ָʾ��¼���еĶ�β 
	
	BinTree stack[100];//����һ��ջ
	int top=0;//ջ�����α�
	int isVisited[100]; //��¼һ���ڵ��Ƿ񱻷����ˣ���һ���ڵ�Ķ����ǲ��Ǳ�ѹ��ջ�� 
	BinTree p;
	
	if(t == NULL) return 0;//��Ϊ��
	stack[top] = t;//�����ĸ���ջ
	isVisited[top++] = 0; 
	
	//ջ��Ϊ�գ����Ľڵ��û�б�����
	while(top != 0)
	{
		p = stack[--top];//һ���ڵ��ջ
		//����Ѿ������ʹ�һ�Σ����¼���м�¼�����Ľڵ�
		if(isVisited[top])
		{
			queue[queueRear++] = p;
		}
		else //���Լ����Ҷ��ӣ������������ջ 
		{ 
			isVisited[top] = 1;
			stack[top++] = p;
			
			if(p->rchild != NULL)
			{
				isVisited[top] = 0; 
			  	stack[top++] = p->rchild;
			}
			
			if(p->lchild != NULL)
			{
				isVisited[top] = 0;
				stack[top++] = p->lchild;
			}	
		} 
	}
	return queueRear; //���ر������нڵ�ĸ���
} 

/*
	@�������ƣ�BinTree_levelorder
	@��ڲ�����Ҫ�����Ķ�������BinTree�������ڼ�¼���ڵ�ı���˳��ļ�¼���У�BinTree[]�� 
	@���ڲ����������˵����ڵ�ĸ�����int�� 
	@�������ܣ�ʵ�ֶ������Ĳ�α��� 
*/
int BinTree_levelorder(BinTree t,BinTree * queue) 
{
	int queueFront = 0; //ָʾ���еĶ��� 
	int queueRear = 0; //ָʾ���еĶ�β
	BinTree p;
	
	if(t == NULL) return 0; //��Ϊ�� 
	queue[queueRear++] = t; //�����ڵ���� 
	
	//���в�Ϊ�գ������нڵ�û����ȫ������ 
	while(queueRear > queueFront) 
	{
		p = queue[queueFront++]; //���� 
		//�����Ҷ������ 
		if(p->lchild != NULL) 
			queue[queueRear++] = p->lchild;
		if(p->rchild != NULL)
			queue[queueRear++] = p->rchild;
	} 
	
	//���ڶ����е����ݲ�û�б����ǣ����Զ�����ʵ��¼�˱����Ľڵ��˳��
	return queueRear; 
}

/*
	@�������ƣ�BinTree_insert 
	@��ڲ�����������������ָ�루BinTree *����Ҫ����Ĺؼ��֣�int�� 
	@���ڲ������� 
	@�������ܣ���һ�ö����������в���һ���ڵ� 
*/
void BinTree_insert(BinTree * t,int key)
{
	BinTree parent=NULL,p,temp;
  	p = *t;
	
	//һֱ��Ҷ�ӽڵ� 
  	while(p != NULL)
  	{
	    if(key == p->data) return ; //����ؼ����Ѿ�������
		//���²��� 
		parent = p; 
		if(key < p->data) p = p->lchild;
		else p = p->rchild;
  	}
	
	//����һ���ڵ� 
	temp = (BinTree)malloc(sizeof(BinTreeNode));
	temp->data = key;
	temp->lchild = temp->rchild = NULL;
	
	//�������������Ϊ�գ�����뵽���ڵ㣬������뵽һ���ڵ��Ϊ���ӽڵ� 
	if(*t == NULL) *t = temp; 
	else if(key < parent->data) parent->lchild = temp;
	else parent->rchild = temp;
}

/*
	@�������ƣ�BinTree_free 
	@��ڲ�������������BinTree�� 
	@���ڲ������� 
	@�������ܣ���һ�ö������ͷŵ� 
*/
void BinTree_free(BinTree t)
{
	if(t == NULL) return ; //��Ϊ�� 
	
	//���ͷ��������������������ͷŸ��ڵ� 
	BinTree_free(t->lchild);
	BinTree_free(t->rchild);
	free(t);
} 

/*
	@�������ƣ�BinTree_create 
	@��ڲ�����һ�ö�������ǰ��������ַ�����string�����ڵ�Ϊ�մ����ַ�'#'��ʾ��
				��ָʾ��һ���ڵ��ָʾ���ĵ�ַ��int *���� 
	@���ڲ������������ĸ��ڵ㣨BinTree�� 
	@�������ܣ�ͨ��ǰ��������ַ�������һ�ö����� 
*/
BinTree BinTree_create(char * preorderStr,int * n)
{
    BinTree t;
    char ch = preorderStr[*n]; //ȡ��һ���ڵ����Ϣ 
    (*n)++; //ָʾ��һ���ڵ�λ�õ�ָʾ������ 
    
    if(ch == 0) t = NULL;
    if(ch == '#')  t = NULL;
    else
    { 
		t = (BinTree)malloc(sizeof(BinTreeNode));
		t->data = ch;
		//�������� 
		t->lchild = BinTree_create(preorderStr,n);
		t->rchild = BinTree_create(preorderStr,n);
    }
    return t;
} 
