#include "dataAndStructure.h"
//�����йصĲ���

/*
	@�������ƣ�Tree_preorder
	@��ڲ�����Ҫ����������Tree�������Ķȣ�int�������ڼ�¼���ڵ�ı���˳��ļ�¼���У�BinTree[]�� 
	@���ڲ����������˵����ڵ�ĸ�����int�� 
	@�������ܣ�ʵ������ǰ����� 
*/
int Tree_preorder(Tree tree,int degree,Tree * queue)
{
	int queueRear = 0; //ָʾ��¼���еĶ�β
	
    Tree stack[100];//����һ��ջ
	int top = 0;//ջ��
    Tree p;
    int i;

    if(tree == NULL) return 0;//��Ϊ��

    stack[top++] = tree;//���ڵ����ջ��
    while(top != 0)
    {
        p = stack[--top];//һ���ڵ��ջ
        queue[queueRear] = p;

        for(i=degree-1;i>=0;i--)//���亢�ӽ�ջ
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
	@�������ƣ�Tree_postorder
	@��ڲ�����Ҫ����������Tree�������Ķȣ�int�������ڼ�¼���ڵ�ı���˳��ļ�¼���У�BinTree[]�� 
	@���ڲ����������˵����ڵ�ĸ�����int�� 
	@�������ܣ�ʵ�����ĺ������ 
*/
int Tree_postorder(Tree tree,int degree,Tree * queue)
{
	int queueRear = 0; //ָʾ��¼���еĶ�β 
	
	Tree stack[100];//����һ��ջ
	int top=0;//ջ�����α�
	int isVisited[100]; //��¼һ���ڵ��Ƿ񱻷����ˣ���һ���ڵ�Ķ����ǲ��Ǳ�ѹ��ջ�� 
	Tree p;
	int i;
	
	if(tree == NULL) return 0;//��Ϊ��
	stack[top] = tree;//�����ĸ���ջ
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
		else //���Լ��Ͷ���������ջ 
		{ 
			isVisited[top] = 1;
			stack[top++] = p;
			
			for(i=degree-1;i>=0;i--)//���亢�ӽ�ջ
	        {
	            if(p->child[i] != NULL)
	            {
	                isVisited[top] = 0;
	                stack[top++] = p->child[i];
	            }
	        }
		} 
	}
	return queueRear; //���ر������нڵ�ĸ���
} 

/*
	@�������ƣ�Tree_levelorder 
	@��ڲ�����Ҫ����������Tree�������Ķȣ�int�������ڼ�¼���ڵ�ı���˳��ļ�¼���У�BinTree[]�� 
	@���ڲ����������˵����ڵ�ĸ�����int�� 
	@�������ܣ�ʵ�����Ĳ�α��� 
*/
int Tree_levelorder(Tree tree,int degree,Tree * queue)    /* tΪָ����������ָ��*/
{
	int queueRear = 0; //ָʾ��¼���еĶ�β
	int queueFront = 0; //ָʾ��¼���еĶ��� 
	
	Tree p;
	int i;
	
	if(tree == NULL) return 0;//��Ϊ�գ������б���
	queue[queueRear++] = tree;//���ĸ��ڵ�������
	//���в�Ϊ�գ�˵����û��ȫ��������
	while(queueFront != queueRear)
	{
		p = queue[queueFront++];//�Ӷ�����ȡ��һ���ڵ�
		for(i=0;i<degree;i++)//�������ӽڵ�������
		{
			if(p->child[i] == NULL) continue;
			else queue[queueRear++] = p->child[i];
		}
	}
	
	//���ڶ����е����ݲ�û�б����ǣ����Զ�����ʵ��¼�˱����Ľڵ��˳��
	return queueRear;
}

/*
	@�������ƣ�Tree_free 
	@��ڲ���������Tree�������Ķȣ�int�� 
	@���ڲ������� 
	@�������ܣ���һ�����ͷŵ� 
*/
void Tree_free(Tree tree,int degree)
{
	if(tree == NULL) return ; //��Ϊ�� 
	
	//���ͷ������������ͷŸ��ڵ�
	int i;
	for(i=0;i<degree;i++)
		 Tree_free(tree->child[i],degree);
		 
	free(tree->child); //�ͷ����ڴ�����ӵĿռ� 
	free(tree);
} 

/*
	@�������ƣ�Tree_create 
	@��ڲ�����һ������ǰ��������ַ�����string�����ڵ�Ϊ�մ����ַ�'#'��ʾ��
				��ָʾ��һ���ڵ��ָʾ���ĵ�ַ��int *����Ҫ���������Ķȣ�int�� 
	@���ڲ��������ĸ��ڵ㣨Tree�� 
	@�������ܣ�ͨ��ǰ��������ַ�������һ���� 
*/
Tree Tree_create(char * preorderStr,int * n,int degree)
{
    Tree t;
    int i; 
    char ch = preorderStr[*n]; //ȡ��һ���ڵ����Ϣ 
    (*n)++; //ָʾ��һ���ڵ�λ�õ�ָʾ������ 
    
    if(ch == 0) t = NULL;
    if(ch=='#')  t = NULL;
    else
    { 
		t=(Tree)malloc(sizeof(TreeNode));
		t->data = ch;
		t->child = (Tree *)malloc(sizeof(Tree) * degree);
		//�������� 
		for(i=0;i<degree;i++)
			t->child[i] = Tree_create(preorderStr,n,degree);
    }
    return t;
} 

/*
	@�������ƣ�Tree_create2 
	@��ڲ�����һ�����������ű�ʾ���ַ�����string�������磬��Ҫ��������Ӧ����A��B��E��F��,C,D��G��I��J��K��,H��������
				Ҫ���������Ķȣ�int�� 
	@���ڲ��������ĸ��ڵ㣨Tree�� 
	@�������ܣ�ͨ�������ű�ʾ���ַ�������һ���� 
*/
Tree Tree_create2(char * s,int degree)
{
  Tree stack[100];//����ջ
  int top = 0;//ջ��
  Tree parent = NULL,child=NULL;//���ڵ�ͺ��ӽڵ�
  int n=0,i,done=0;//doneΪ���Ƿ��������

  if(s[0] == '\0') return NULL;

  while(done == 0 && s[n]!='\0')
  {
    //�ӽڵ��к��ӣ���Ϊ���ڵ㲢��ջ
    if(s[n] == '(')
    {
      parent = child;
      stack[top++] = parent;
    }
    else if(s[n] == ',') {}//Ϊ��������
    else if(s[n] == ')')//ջ���ĸ��ڵ�ĺ����ռ����
    {
      parent = stack[--top];//�ռ��꺢�ӵĸ��ڵ��ջ
      if(top == 0)//���ջ��û�и��ڵ�
        done = 1;
      else parent = stack[top-1];//����һ�����ڵ��ռ�����
    }
    else
    {
      //����һ���ӽڵ㲢��ʼ��
      child = (Tree)malloc(sizeof(TreeNode));
      child->data = s[n];
      for(i=0;i<degree;i++) child->child[i] = NULL;
      //���һ���ӽڵ��и��ڵ㣬�ͱ����ڵ��ռ�
      if(parent != NULL)
      {
        for(i=0;i<degree;i++)//�ҵ����ڵ��ռ����Ŀ�λ
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
