#include "dataAndStructure.h"

//全局变量，要在头文件中做申明 
Button structureSelectMenu[MENU_SIZE]; //一组选择让用户数据结构的按钮
Button backButton; //返回到数据结构选择菜单的按钮 


int Setup()
{
	//数据 
	char * structureName[] = {"顺序表","链表","树","二叉树","图"};
	void (*structureSystem[])(void) = {sequList,linkList,tree,binaryTree,map}; 
	//初始化 
	initWindow("数据结构",DEFAULT,DEFAULT,WIDTH,HEIGHT);
	initConsole(); 
	//数据结构的选择按钮的创建 
	createButtonGroup(structureSelectMenu,structureName,MENU_SIZE,400,50,200,50,20);
	addButtonGroupPerform(structureSelectMenu,MENU_SIZE,structureSystem);
	 
	beginPaint();
		setBrushColor(EMPTY);
		//paintButton(&menuButton);
		paintButtonGroup(structureSelectMenu,MENU_SIZE);
	endPaint(); 
	
//	registerCharEvent(inputBoxEvent);
	registerMouseEvent(buttonEvent);
//	registerTimerEvent();
//	startTimer(0,100);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
/*注册的事件*/

 
/*
	@函数名称：buttonEvnet
	@入口参数：鼠标点击的坐标（int），鼠标按钮的哪个按钮（int）以及做的事情（int）， 
	@出口参数：无 
	@函数功能：当鼠标点击屏幕后，引发该函数。其会判断鼠标是对哪个按钮进行了
				点击，并执行该按钮被点击后要执行的操作 
*/
void buttonEvent(int x,int y,int button,int event)
{	 
	if(button == LEFT_BUTTON)
	{
		if(event == BUTTON_DOWN)
		{
			//判断点击的是不是数据结构选择菜单中的按钮
			int n = whichIsPressed(structureSelectMenu,MENU_SIZE,x,y);//被点击的按钮的索引 
			if(n != -1 && structureSelectMenu[n].perform != NULL) 
				structureSelectMenu[n].perform(); 
			
			//判断点击的是不是返回按钮 
			if(isPressed(&backButton,x,y) && backButton.perform != NULL)
				backButton.perform(); 
		}
	}
} 

/*
	@函数名称：inputBoxEvent 
	@入口参数：键盘输入的一个字符 
	@出口参数：无 
	@函数功能：当键盘输入字符到窗口上的输入框时，该函数会被调用。
				让输入框接受这个字符，并做出相应的处理 
*/
//void inputBoxEvent(char c) 
//{
//	int maxLength = 100; //输入字符的最大长度
//	
//	if(userInputBox.length >= maxLength) userInputBox.length = 0;
//	
//	if(c == 8) //如果输入的字符为退格，则删除一个字符 
//	{
//		//如果字符串的长度是大于零的 
//		if(userInputBox.length > 0) 
//		{
//			//如果将删除的字符是ASCII码（0~127）（为正数） 
//			if(userInputBox.inputString[userInputBox.length-1] >= 0)
//			{
//				userInputBox.inputString[--userInputBox.length] = 0;
//			}
//			else//如果将删除的字符是Unicode（为负数） 
//			{
//				userInputBox.inputString[--userInputBox.length] = 0;
//				userInputBox.inputString[--userInputBox.length] = 0;
//			}
//		}	
//	} 
//	else//增加一个字符 
//	{
//		userInputBox.inputString[userInputBox.length++] = c;
//		userInputBox.inputString[userInputBox.length] = 0; 
//	}
//	
//	//重画输入框 
//	beginPaint();
//	clearInputBox(&userInputBox);
//	paintInputBox(&userInputBox); 
//	endPaint();
//} 

/*
	@函数名称：
	@入口参数：
	@出口参数：
	@函数功能：
*/


