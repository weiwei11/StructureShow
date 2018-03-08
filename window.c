#include "dataAndStructure.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
/*与窗口有关的函数*/

 
void structureSelectWindow()
{
	clearAll(); //清理窗口中的所有的图形，按钮，输入框等 
	
	beginPaint();
	paintButtonGroup(structureSelectMenu,MENU_SIZE);
	endPaint();
}


void clearAll()
{
	beginPaint();
	clearDevice();
	clearButtonGroup(structureSelectMenu,MENU_SIZE);
	clearButton(&backButton);
	clearInputBox(&userInputBox);
	endPaint();
} 

//由于有些.c文件现在还没有，先暂时在这里定义，以后再剪切到对应的.c文件 
void sequList()
{
	beginPaint();
	//对窗口进行一个清理 
	clearButtonGroup(structureSelectMenu,MENU_SIZE); 
	clearDevice();
	//显示初始的界面 
	paintButton(&backButton);
	paintInputBox(&userInputBox);
	
//	registerTimerEvent(timerEvent);
	startTimer(0,1000); 
	endPaint(); 
} 

void linkList()
{
	clearDevice();
} 

void tree()
{
	clearDevice();
}

void binaryTree()
{
	clearDevice();
}

void map()
{
	clearDevice();
}
