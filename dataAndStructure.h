#include <stdio.h>
#include <math.h>
#include <time.h>
#include "acllib.h" 

////////////////////////////////////////////////////////////////////////////////////////////////////// 
//常量
#define WIDTH 1000 //窗口的宽度 
#define HEIGHT 700 //窗口的高度 
#define SEQULIST_LENGTH 100 //顺序表的总长度 
#define WORLD_WIDTH 9 //一个char的默认宽度 （像素点） 
#define WORLD_HEIGHT 16 //一个char的默认高度（像素点） 
#define POINTER_WIDTH  20 //指针框的宽度（像素点）
#define ARROW_HEAD_LENGTH 10 //箭头双翼的长度（像素点） 
#define NOT_DIRECTION 0 //无方向的边 
#define NOT_WEIGHT 0xFFFFFFFF //无权重的边 
#define MENU_SIZE 5 //菜单的按钮的个数 
#define MAP_MAX_SIZE 50 //图最多能容纳的节点个数 
#define FINITY 0x7FFFFFFF //无穷大 

//////////////////////////////////////////////////////////////////////////////////////////////////////
/*结构*/ 

/*与控件有关的结构*/  

//输入框控件 
typedef struct InputBox
{
	int X,Y;
	int width,height; 
	int cols; //输入框最多能显示的字符个数 
	char inputString[101]; //记录一次输入的字符串 
	int length; //已存字符的个数 
}InputBox;

//按钮控件 
typedef struct Button
{
	char text[21];
	int textSize;
	int X,Y,width,height;
	int isPainted; //标记一个按钮是否被画在了窗口上 
	void (*perform)(void); //按钮被点击后将执行的操作 
}Button;

//单选按钮 
typedef struct RadioButton
{
	char text[10][21]; //每个单选按钮要显示的文本 
	int X,Y,width,height; //坐标 
	int n; //单选按钮的个数 
	int isPainted; //标记一个按钮是否被画在了窗口上 
	void (*perform)(void); //按钮被点击后将执行的操作 
	int select; //用于记录选择的选项 
}RadioButton;

//控制工具控件 
typedef struct ControlTool
{
	int X,Y,width,height; //坐标，长宽 
	int isPainted; //是否被画在了窗口上 
	void (*paint)(struct ControlTool * itself); //控制显示的样子 
}ControlTool;

/*与图形有关的结构*/ 

//方形 
typedef struct Square
{
	int x,y;
	int width,height;
}Square;

//圆形 
typedef struct Round
{
	int x,y;
	int radius;
}Round;

/*与数据有关的结构*/

//链表 
typedef struct LinkNode
{
	int data;
	struct LinkNode * next;
}LinkNode;
typedef LinkNode * LinkList;

//顺序表 
typedef struct SequList
{
	int data[SEQULIST_LENGTH]; 
	int dataSize; //顺序表已存的元素个数 
}SequList;

//队列
typedef struct Queue
{
	int * data;
	int front;
	int rear;
}Queue; 

//堆栈 
typedef struct Stack
{
	int * data;
	int top;
}Stack;

//二叉树 
typedef struct BinTreeNode
{
	int data;
	struct BinTreeNode * lchild;
	struct BinTreeNode * rchild;
}BinTreeNode;
typedef BinTreeNode * BinTree;

//树的节点 
typedef struct TreeNode
{
	int data;
	struct TreeNode ** child; 
}TreeNode; 
typedef TreeNode * Tree; //树
 
//树 
typedef struct TreeWithDegree
{
	int degree;//度 
	Tree root;	
}TreeWithDegree;

//以邻接矩阵表示的图 
typedef struct MatrixMap
{
	char vertices[MAP_MAX_SIZE]; //图的节点 
	int edges[MAP_MAX_SIZE][MAP_MAX_SIZE]; //图的边 
	int n; //图节点的个数 
	int e; //图边的条数 
}MatrixMap;

//以邻接表表示的图
typedef struct Node
{
	int adjvex; //邻接点 
	int length; //长度 
	struct Node * next; //下一个邻接点 
}EdgeNode;
 
typedef struct LinkedMap
{
	char vertices[MAP_MAX_SIZE]; //图节点 
	EdgeNode * edges[MAP_MAX_SIZE]; //边的邻接表 
	int n; //图节点的个数 
	int e; //图边的条数 
}LinkedMap;
//图的边，用于最小生成树的算法中 
typedef struct Edge
{
	int begin; //起始图节点 
	int end; //终止图节点 
	int length; //边的长度 
}Edge;
//用于记录单源最短路径 
typedef struct Path
{
	int path[MAP_MAX_SIZE]; //路径中该点（索引值）的前一个点 
	int distance[MAP_MAX_SIZE]; //路径中源点到该点（索引值）的距离 
}Path; 

//////////////////////////////////////////////////////////////////////////////////////////////////////
/*全局变量的申明，定义在其他的地方*/
extern Button structureSelectMenu[]; //一组选择让用户数据结构的按钮
extern Button backButton; //返回到数据结构选择菜单的按钮 
extern InputBox userInputBox; //用户输入字符的输入框

//////////////////////////////////////////////////////////////////////////////////////////////////////
/*函数*/

//用于显示窗口界面的函数 
void structureSelectWindow();

//用于按钮事件的函数 
void sequList();
void linkList();
void tree();
void binaryTree();
void map(); 

//事件函数 
void buttonEvent(int x,int y,int button,int event); 
void inputBoxEvent(char c);
