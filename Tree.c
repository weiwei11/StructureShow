#include "dataAndStructure.h"
//和树有关的操作

/*
	@函数名称：Tree_preorder
	@入口参数：要遍历的树（Tree）和树的度（int），用于记录树节点的遍历顺序的记录队列（BinTree[]） 
	@出口参数：遍历了的树节点的个数（int） 
	@函数功能：实现树的前序遍历 
*/
int Tree_preorder(Tree tree,int degree,Tree * queue)
{
	int queueRear = 0; //指示记录队列的队尾
	
    Tree stack[100];//建立一个栈
	int top = 0;//栈顶
    Tree p;
    int i;

    if(tree == NULL) return 0;//树为空

    stack[top++] = tree;//根节点进入栈中
    while(top != 0)
    {
        p = stack[--top];//一个节点出栈
        queue[queueRear] = p;

        for(i=degree-1;i>=0;i--)//将其孩子进栈
        {
            if(p->child[i] != NULL)
            {
                stack[top++] = p->child[i];
            }
        }
    }
    return queueRear;
} 

/*
	@函数名称：Tree_postorder
	@入口参数：要遍历的树（Tree）和树的度（int），用于记录树节点的遍历顺序的记录队列（BinTree[]） 
	@出口参数：遍历了的树节点的个数（int） 
	@函数功能：实现树的后序遍历 
*/
int Tree_postorder(Tree tree,int degree,Tree * queue)
{
	int queueRear = 0; //指示记录队列的队尾 
	
	Tree stack[100];//建立一个栈
	int top=0;//栈顶的游标
	int isVisited[100]; //记录一个节点是否被访问了，即一个节点的儿子是不是被压入栈了 
	Tree p;
	int i;
	
	if(tree == NULL) return 0;//树为空
	stack[top] = tree;//将树的根进栈
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
		else //将自己和儿子依次入栈 
		{ 
			isVisited[top] = 1;
			stack[top++] = p;
			
			for(i=degree-1;i>=0;i--)//将其孩子进栈
	        {
	            if(p->child[i] != NULL)
	            {
	                isVisited[top] = 0;
	                stack[top++] = p->child[i];
	            }
	        }
		} 
	}
	return queueRear; //返回遍历树中节点的个数
} 

/*
	@函数名称：Tree_levelorder 
	@入口参数：要遍历的树（Tree）和树的度（int），用于记录树节点的遍历顺序的记录队列（BinTree[]） 
	@出口参数：遍历了的树节点的个数（int） 
	@函数功能：实现树的层次遍历 
*/
int Tree_levelorder(Tree tree,int degree,Tree * queue)    /* t为指向树根结点的指针*/
{
	int queueRear = 0; //指示记录队列的队尾
	int queueFront = 0; //指示记录队列的队首 
	
	Tree p;
	int i;
	
	if(tree == NULL) return 0;//树为空，不进行遍历
	queue[queueRear++] = tree;//树的根节点进入队列
	//队列不为空，说明树没有全部变量完
	while(queueFront != queueRear)
	{
		p = queue[queueFront++];//从队列中取出一个节点
		for(i=0;i<degree;i++)//将它的子节点放入队列
		{
			if(p->child[i] == NULL) continue;
			else queue[queueRear++] = p->child[i];
		}
	}
	
	//由于队列中的数据并没有被覆盖，所以队列其实记录了遍历的节点的顺序
	return queueRear;
}

/*
	@函数名称：Tree_free 
	@入口参数：树（Tree）和树的度（int） 
	@出口参数：无 
	@函数功能：将一棵树释放掉 
*/
void Tree_free(Tree tree,int degree)
{
	if(tree == NULL) return ; //树为空 
	
	//先释放子树数，在释放根节点
	int i;
	for(i=0;i<degree;i++)
		 Tree_free(tree->child[i],degree);
		 
	free(tree->child); //释放用于储存儿子的空间 
	free(tree);
} 

/*
	@函数名称：Tree_create 
	@入口参数：一棵树的前序遍历的字符串（string）（节点为空处以字符'#'表示）
				和指示下一个节点的指示器的地址（int *），要创建的树的度（int） 
	@出口参数：树的根节点（Tree） 
	@函数功能：通过前序遍历的字符串创建一棵树 
*/
Tree Tree_create(char * preorderStr,int * n,int degree)
{
    Tree t;
    int i; 
    char ch = preorderStr[*n]; //取出一个节点的信息 
    (*n)++; //指示下一个节点位置的指示器后移 
    
    if(ch == 0) t = NULL;
    if(ch=='#')  t = NULL;
    else
    { 
		t=(Tree)malloc(sizeof(TreeNode));
		t->data = ch;
		t->child = (Tree *)malloc(sizeof(Tree) * degree);
		//创建子树 
		for(i=0;i<degree;i++)
			t->child[i] = Tree_create(preorderStr,n,degree);
    }
    return t;
} 

/*
	@函数名称：Tree_create2 
	@入口参数：一棵树的用括号表示的字符串（string）（例如，若要建立树，应输入A（B（E，F）,C,D（G（I，J，K）,H））。）
				要创建的树的度（int） 
	@出口参数：树的根节点（Tree） 
	@函数功能：通过用括号表示的字符串创建一棵树 
*/
Tree Tree_create2(char * s,int degree)
{
  Tree stack[100];//定义栈
  int top = 0;//栈顶
  Tree parent = NULL,child=NULL;//父节点和孩子节点
  int n=0,i,done=0;//done为树是否建立完成了

  if(s[0] == '\0') return NULL;

  while(done == 0 && s[n]!='\0')
  {
    //子节点有孩子，成为父节点并进栈
    if(s[n] == '(')
    {
      parent = child;
      stack[top++] = parent;
    }
    else if(s[n] == ',') {}//为逗号跳过
    else if(s[n] == ')')//栈顶的父节点的孩子收集完成
    {
      parent = stack[--top];//收集完孩子的父节点出栈
      if(top == 0)//如果栈中没有父节点
        done = 1;
      else parent = stack[top-1];//换另一个父节点收集孩子
    }
    else
    {
      //建立一个子节点并初始化
      child = (Tree)malloc(sizeof(TreeNode));
      child->data = s[n];
      for(i=0;i<degree;i++) child->child[i] = NULL;
      //如果一个子节点有父节点，就被父节点收集
      if(parent != NULL)
      {
        for(i=0;i<degree;i++)//找到父节点收集处的空位
        {
          if(parent->child[i] == NULL)
          {
            parent->child[i] = child;
            break;
          }
        }
      }
    }
    n++;
  }
  return parent;
}
