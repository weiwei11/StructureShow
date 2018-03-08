#include "dataAndStructure.h"

//ȫ�ֱ�����Ҫ��ͷ�ļ��������� 
Button structureSelectMenu[MENU_SIZE]; //һ��ѡ�����û����ݽṹ�İ�ť
Button backButton; //���ص����ݽṹѡ��˵��İ�ť 


int Setup()
{
	//���� 
	char * structureName[] = {"˳���","����","��","������","ͼ"};
	void (*structureSystem[])(void) = {sequList,linkList,tree,binaryTree,map}; 
	//��ʼ�� 
	initWindow("���ݽṹ",DEFAULT,DEFAULT,WIDTH,HEIGHT);
	initConsole(); 
	//���ݽṹ��ѡ��ť�Ĵ��� 
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
/*ע����¼�*/

 
/*
	@�������ƣ�buttonEvnet
	@��ڲ���������������꣨int������갴ť���ĸ���ť��int���Լ��������飨int���� 
	@���ڲ������� 
	@�������ܣ����������Ļ�������ú���������ж�����Ƕ��ĸ���ť������
				�������ִ�иð�ť�������Ҫִ�еĲ��� 
*/
void buttonEvent(int x,int y,int button,int event)
{	 
	if(button == LEFT_BUTTON)
	{
		if(event == BUTTON_DOWN)
		{
			//�жϵ�����ǲ������ݽṹѡ��˵��еİ�ť
			int n = whichIsPressed(structureSelectMenu,MENU_SIZE,x,y);//������İ�ť������ 
			if(n != -1 && structureSelectMenu[n].perform != NULL) 
				structureSelectMenu[n].perform(); 
			
			//�жϵ�����ǲ��Ƿ��ذ�ť 
			if(isPressed(&backButton,x,y) && backButton.perform != NULL)
				backButton.perform(); 
		}
	}
} 

/*
	@�������ƣ�inputBoxEvent 
	@��ڲ��������������һ���ַ� 
	@���ڲ������� 
	@�������ܣ������������ַ��������ϵ������ʱ���ú����ᱻ���á�
				��������������ַ�����������Ӧ�Ĵ��� 
*/
//void inputBoxEvent(char c) 
//{
//	int maxLength = 100; //�����ַ�����󳤶�
//	
//	if(userInputBox.length >= maxLength) userInputBox.length = 0;
//	
//	if(c == 8) //���������ַ�Ϊ�˸���ɾ��һ���ַ� 
//	{
//		//����ַ����ĳ����Ǵ������ 
//		if(userInputBox.length > 0) 
//		{
//			//�����ɾ�����ַ���ASCII�루0~127����Ϊ������ 
//			if(userInputBox.inputString[userInputBox.length-1] >= 0)
//			{
//				userInputBox.inputString[--userInputBox.length] = 0;
//			}
//			else//�����ɾ�����ַ���Unicode��Ϊ������ 
//			{
//				userInputBox.inputString[--userInputBox.length] = 0;
//				userInputBox.inputString[--userInputBox.length] = 0;
//			}
//		}	
//	} 
//	else//����һ���ַ� 
//	{
//		userInputBox.inputString[userInputBox.length++] = c;
//		userInputBox.inputString[userInputBox.length] = 0; 
//	}
//	
//	//�ػ������ 
//	beginPaint();
//	clearInputBox(&userInputBox);
//	paintInputBox(&userInputBox); 
//	endPaint();
//} 

/*
	@�������ƣ�
	@��ڲ�����
	@���ڲ�����
	@�������ܣ�
*/


