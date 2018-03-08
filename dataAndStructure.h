#include <stdio.h>
#include <math.h>
#include <time.h>
#include "acllib.h" 

////////////////////////////////////////////////////////////////////////////////////////////////////// 
//����
#define WIDTH 1000 //���ڵĿ�� 
#define HEIGHT 700 //���ڵĸ߶� 
#define SEQULIST_LENGTH 100 //˳�����ܳ��� 
#define WORLD_WIDTH 9 //һ��char��Ĭ�Ͽ�� �����ص㣩 
#define WORLD_HEIGHT 16 //һ��char��Ĭ�ϸ߶ȣ����ص㣩 
#define POINTER_WIDTH  20 //ָ���Ŀ�ȣ����ص㣩
#define ARROW_HEAD_LENGTH 10 //��ͷ˫��ĳ��ȣ����ص㣩 
#define NOT_DIRECTION 0 //�޷���ı� 
#define NOT_WEIGHT 0xFFFFFFFF //��Ȩ�صı� 
#define MENU_SIZE 5 //�˵��İ�ť�ĸ��� 
#define MAP_MAX_SIZE 50 //ͼ��������ɵĽڵ���� 
#define FINITY 0x7FFFFFFF //����� 

//////////////////////////////////////////////////////////////////////////////////////////////////////
/*�ṹ*/ 

/*��ؼ��йصĽṹ*/  

//�����ؼ� 
typedef struct InputBox
{
	int X,Y;
	int width,height; 
	int cols; //������������ʾ���ַ����� 
	char inputString[101]; //��¼һ��������ַ��� 
	int length; //�Ѵ��ַ��ĸ��� 
}InputBox;

//��ť�ؼ� 
typedef struct Button
{
	char text[21];
	int textSize;
	int X,Y,width,height;
	int isPainted; //���һ����ť�Ƿ񱻻����˴����� 
	void (*perform)(void); //��ť�������ִ�еĲ��� 
}Button;

//��ѡ��ť 
typedef struct RadioButton
{
	char text[10][21]; //ÿ����ѡ��ťҪ��ʾ���ı� 
	int X,Y,width,height; //���� 
	int n; //��ѡ��ť�ĸ��� 
	int isPainted; //���һ����ť�Ƿ񱻻����˴����� 
	void (*perform)(void); //��ť�������ִ�еĲ��� 
	int select; //���ڼ�¼ѡ���ѡ�� 
}RadioButton;

//���ƹ��߿ؼ� 
typedef struct ControlTool
{
	int X,Y,width,height; //���꣬���� 
	int isPainted; //�Ƿ񱻻����˴����� 
	void (*paint)(struct ControlTool * itself); //������ʾ������ 
}ControlTool;

/*��ͼ���йصĽṹ*/ 

//���� 
typedef struct Square
{
	int x,y;
	int width,height;
}Square;

//Բ�� 
typedef struct Round
{
	int x,y;
	int radius;
}Round;

/*�������йصĽṹ*/

//���� 
typedef struct LinkNode
{
	int data;
	struct LinkNode * next;
}LinkNode;
typedef LinkNode * LinkList;

//˳��� 
typedef struct SequList
{
	int data[SEQULIST_LENGTH]; 
	int dataSize; //˳����Ѵ��Ԫ�ظ��� 
}SequList;

//����
typedef struct Queue
{
	int * data;
	int front;
	int rear;
}Queue; 

//��ջ 
typedef struct Stack
{
	int * data;
	int top;
}Stack;

//������ 
typedef struct BinTreeNode
{
	int data;
	struct BinTreeNode * lchild;
	struct BinTreeNode * rchild;
}BinTreeNode;
typedef BinTreeNode * BinTree;

//���Ľڵ� 
typedef struct TreeNode
{
	int data;
	struct TreeNode ** child; 
}TreeNode; 
typedef TreeNode * Tree; //��
 
//�� 
typedef struct TreeWithDegree
{
	int degree;//�� 
	Tree root;	
}TreeWithDegree;

//���ڽӾ����ʾ��ͼ 
typedef struct MatrixMap
{
	char vertices[MAP_MAX_SIZE]; //ͼ�Ľڵ� 
	int edges[MAP_MAX_SIZE][MAP_MAX_SIZE]; //ͼ�ı� 
	int n; //ͼ�ڵ�ĸ��� 
	int e; //ͼ�ߵ����� 
}MatrixMap;

//���ڽӱ��ʾ��ͼ
typedef struct Node
{
	int adjvex; //�ڽӵ� 
	int length; //���� 
	struct Node * next; //��һ���ڽӵ� 
}EdgeNode;
 
typedef struct LinkedMap
{
	char vertices[MAP_MAX_SIZE]; //ͼ�ڵ� 
	EdgeNode * edges[MAP_MAX_SIZE]; //�ߵ��ڽӱ� 
	int n; //ͼ�ڵ�ĸ��� 
	int e; //ͼ�ߵ����� 
}LinkedMap;
//ͼ�ıߣ�������С���������㷨�� 
typedef struct Edge
{
	int begin; //��ʼͼ�ڵ� 
	int end; //��ֹͼ�ڵ� 
	int length; //�ߵĳ��� 
}Edge;
//���ڼ�¼��Դ���·�� 
typedef struct Path
{
	int path[MAP_MAX_SIZE]; //·���иõ㣨����ֵ����ǰһ���� 
	int distance[MAP_MAX_SIZE]; //·����Դ�㵽�õ㣨����ֵ���ľ��� 
}Path; 

//////////////////////////////////////////////////////////////////////////////////////////////////////
/*ȫ�ֱ����������������������ĵط�*/
extern Button structureSelectMenu[]; //һ��ѡ�����û����ݽṹ�İ�ť
extern Button backButton; //���ص����ݽṹѡ��˵��İ�ť 
extern InputBox userInputBox; //�û������ַ��������

//////////////////////////////////////////////////////////////////////////////////////////////////////
/*����*/

//������ʾ���ڽ���ĺ��� 
void structureSelectWindow();

//���ڰ�ť�¼��ĺ��� 
void sequList();
void linkList();
void tree();
void binaryTree();
void map(); 

//�¼����� 
void buttonEvent(int x,int y,int button,int event); 
void inputBoxEvent(char c);
