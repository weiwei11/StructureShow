#include "dataAndStructure.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
/*�봰���йصĺ���*/

 
void structureSelectWindow()
{
	clearAll(); //�������е����е�ͼ�Σ���ť�������� 
	
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

//������Щ.c�ļ����ڻ�û�У�����ʱ�����ﶨ�壬�Ժ��ټ��е���Ӧ��.c�ļ� 
void sequList()
{
	beginPaint();
	//�Դ��ڽ���һ������ 
	clearButtonGroup(structureSelectMenu,MENU_SIZE); 
	clearDevice();
	//��ʾ��ʼ�Ľ��� 
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
