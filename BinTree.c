#include "dataAndStructure.h"
//和二叉树有关的操作

/*
	@函数名称：BinTree_preorder
	@入口参数：要遍历的二叉树（BinTree），用于记录树节点的遍历顺序的记录队列（BinTree[]） 
	@出口参数：遍历了的树节点的个数（int） 
	@函数功能：实现二叉树的前序遍历 
*/
int BinTree_preorder(BinTree t,BinTree * queue)
{
	int queueRear = 0; //指示记录队列的队尾 
	
	BinTree stack[100];//建立一个栈
	int top=0;//栈顶的游标
	BinTree p;
	
	if(t == NULL) return 0;//树为空
	stack[top++] = t;//将树的根进栈
	
	//栈不为空，树的节点就没有遍历完
	while(top != 0)
	{
		p = stack[--top];//父节点出栈
		//记录队列记录遍历的节点
		queue[queueRear++] = p; 
		 
		//右节点先进栈，左节点后进栈，以此可以先输出左节点
		if(p->rchild != NULL)
		  	stack[top++] = p->rchild;
		if(p->lchild != NULL)
			stack[top++] = p->lchild;
	}
	return queueRear; //返回遍历树中节点的个数 
}

/*
	@函数名称：BinTree_inorder
	@入口参数：要遍历的二叉树（BinTree），用于记录树节点的遍历顺序的记录队列（BinTree[]） 
	@出口参数：遍历了的树节点的个数（int） 
	@函数功能：实现二叉树的中序遍历 
*/
int BinTree_inorder(BinTree t,BinTree * queue)
{
	int queueRear = 0; //指示记录队列的队尾 
	
	BinTree stack[100];//建立一个栈
	int top=0;//栈顶的游标
	int isVisited[100]; //记录一个节点是否被访问了，即一个节点的儿子是不是被压入栈了 
	BinTree p;
	
	if(t == NULL) return 0;//树为空
	stack[top] = t;//将树的根进栈
	isVisited[top++] = 0; 
	
	//栈不为空，树的节点就没有遍历完
	while(top != 0)
	{
		p = stack[--top];//一个节点出栈
		//如果已经被访问过一次，则记录队列记录遍历的节点
		if(isVisited[top])
		{
			queue[queueRear++] = p;
		}
		else //将右儿子，自己和左儿子依次入栈 
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
	return queueRear; //返回遍历树中节点的个数
} 

/*
	@函数名称：BinTree_postorder
	@入口参数：要遍历的二叉树（BinTree），用于记录树节点的遍历顺序的记录队列（BinTree[]） 
	@出口参数：遍历了的树节点的个数（int） 
	@函数功能：实现二叉树的后序遍历 
*/
int BinTree_postorder(BinTree t,BinTree * queue)
{
	int queueRear = 0; //指示记录队列的队尾 
	
	BinTree stack[100];//建立一个栈
	int top=0;//栈顶的游标
	int isVisited[100]; //记录一个节点是否被访问了，即一个节点的儿子是不是被压入栈了 
	BinTree p;
	
	if(t == NULL) return 0;//树为空
	stack[top] = t;//将树的根进栈
	isVisited[top++] = 0; 
	
	//栈不为空，树的节点就没有遍历完
	while(top != 0)
	{
		p = stack[--top];//一个节点出栈
		//如果已经被访问过一次，则记录队列记录遍历的节点
		if(isVisited[top])
		{
			queue[queueRear++] = p;
		}
		else //将自己和右儿子，左儿子依次入栈 
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
	return queueRear; //返回遍历树中节点的个数
} 

/*
	@函数名称：BinTree_levelorder
	@入口参数：要遍历的二叉树（BinTree），用于记录树节点的遍历顺序的记录队列（BinTree[]） 
	@出口参数：遍历了的树节点的个数（int） 
	@函数功能：实现二叉树的层次遍历 
*/
int BinTree_levelorder(BinTree t,BinTree * queue) 
{
	int queueFront = 0; //指示队列的队首 
	int queueRear = 0; //指示队列的队尾
	BinTree p;
	
	if(t == NULL) return 0; //树为空 
	queue[queueRear++] = t; //将根节点入队 
	
	//队列不为空，则树中节点没有完全遍历完 
	while(queueRear > queueFront) 
	{
		p = queue[queueFront++]; //出队 
		//将左右儿子入队 
		if(p->lchild != NULL) 
			queue[queueRear++] = p->lchild;
		if(p->rchild != NULL)
			queue[queueRear++] = p->rchild;
	} 
	
	//由于队列中的数据并没有被覆盖，所以队列其实记录了遍历的节点的顺序
	return queueRear; 
}

/*
	@函数名称：BinTree_insert 
	@入口参数：二叉排序树的指针（BinTree *），要插入的关键字（int） 
	@出口参数：无 
	@函数功能：在一棵二叉排序树中插入一个节点 
*/
void BinTree_insert(BinTree * t,int key)
{
	BinTree parent=NULL,p,temp;
  	p = *t;
	
	//一直到叶子节点 
  	while(p != NULL)
  	{
	    if(key == p->data) return ; //如果关键字已经存在了
		//向下查找 
		parent = p; 
		if(key < p->data) p = p->lchild;
		else p = p->rchild;
  	}
	
	//创建一个节点 
	temp = (BinTree)malloc(sizeof(BinTreeNode));
	temp->data = key;
	temp->lchild = temp->rchild = NULL;
	
	//如果二叉排序树为空，则插入到根节点，否则插入到一个节点成为儿子节点 
	if(*t == NULL) *t = temp; 
	else if(key < parent->data) parent->lchild = temp;
	else parent->rchild = temp;
}

/*
	@函数名称：BinTree_free 
	@入口参数：二叉树（BinTree） 
	@出口参数：无 
	@函数功能：将一棵二叉树释放掉 
*/
void BinTree_free(BinTree t)
{
	if(t == NULL) return ; //树为空 
	
	//先释放左子树和右子数，在释放根节点 
	BinTree_free(t->lchild);
	BinTree_free(t->rchild);
	free(t);
} 

/*
	@函数名称：BinTree_create 
	@入口参数：一棵二叉树的前序遍历的字符串（string）（节点为空处以字符'#'表示）
				和指示下一个节点的指示器的地址（int *）， 
	@出口参数：二叉树的根节点（BinTree） 
	@函数功能：通过前序遍历的字符串创建一棵二叉树 
*/
BinTree BinTree_create(char * preorderStr,int * n)
{
    BinTree t;
    char ch = preorderStr[*n]; //取出一个节点的信息 
    (*n)++; //指示下一个节点位置的指示器后移 
    
    if(ch == 0) t = NULL;
    if(ch == '#')  t = NULL;
    else
    { 
		t = (BinTree)malloc(sizeof(BinTreeNode));
		t->data = ch;
		//创建子树 
		t->lchild = BinTree_create(preorderStr,n);
		t->rchild = BinTree_create(preorderStr,n);
    }
    return t;
} 
