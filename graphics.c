#include "dataAndStructure.h"

extern g_penColor;
extern g_brushColor;


////////////////////////////////////////////////////////////////////////////////////////////////////// 
/*ͨ�õ����ͼ�йصĺ���*/ 


/*
	@�������ƣ�getPenColor 
	@��ڲ������� 
	@���ڲ�������ǰ���ʵ���ɫ��ACL_Color�� 
	@�������ܣ��õ���ǰ���ʵ���ɫ 
*/
ACL_Color getPenColor()
{
	return g_penColor;
}

/*
	@�������ƣ�getBrushColor 
	@��ڲ������� 
	@���ڲ�������ǰ��ˢ����ɫ��ACL_Color�� 
	@�������ܣ��õ���ǰ��ˢ����ɫ 
*/
ACL_Color getBrushColor()
{
	return g_brushColor;
}

/*
	@�������ƣ�createRadioButton
	@��ڲ�������ѡ��ť���ָ�루RadioButton *����������꣨int���ͳ���int����
				�ڵ�ѡ��ť����ʾ��һ���ı���string []������ѡ��ť�ĸ�����int����
				�������ʱִ�е���Ϊ��void (*perfrom)(void)�� 
	@���ڲ������� 
	@�������ܣ�����һ�鵥ѡ��ť 
*/
void createRadioButton(RadioButton * radioButton,int X,int Y,int width,int height,
						char ** text,int n,void (*perform)(void))
{
	int i;
	
	radioButton->X = X;
	radioButton->Y = Y;
	radioButton->width = width;
	radioButton->height = height;
	radioButton->n = n;
	for(i=0;i<n && i<10;i++)
		strcpy(radioButton->text[i],text[i]);
	radioButton->perform = perform;
	radioButton->select = 0; 
} 

/*
	@�������ƣ�paintRadioButton
	@��ڲ�������ѡ��ť���ָ�루RadioButton *�� 
	@���ڲ������� 
	@�������ܣ�������ѡ��ť�� 
*/
void paintRadioButton(RadioButton * radioButton)
{
	int x = radioButton->X,y = radioButton->Y; //ÿ��ѡ�����ʼ�� 
	int h = radioButton->height / radioButton->n; //ÿ��ѡ����ռ�ĸ߶�
	int x1 = x + WORLD_HEIGHT / 2,y1 = y + WORLD_HEIGHT / 2; //��ͼʱԲ��Բ������ 
	int radius = 5; //Բ�İ뾶 
	int i;
	
	setTextSize(WORLD_HEIGHT);
	setBrushColor(EMPTY);
	setPenColor(BLACK); 
	for(i=0;i<radioButton->n;i++)
	{
		//����ѡ�� 
		ellipse(x1 - radius,y1 - radius,x1 + radius,y1 + radius);
		paintText(x + WORLD_HEIGHT + 1,y,radioButton->text[i]);
		//�Ա�ѡ�е�ѡ�����⴦�� 
		if(i == radioButton->select)
		{
			setBrushColor(BLACK);
			ellipse(x1 - (radius - 3),y1 - (radius - 3),
					x1 + (radius - 3),y1 + (radius - 3));
			setBrushColor(EMPTY);
		}
		
		y += h; //��һ��ѡ������
		y1 += h; 
	}
	
	radioButton->isPainted = 1; 
}

/*
	@�������ƣ�whichIsSelected 
	@��ڲ�������ѡ��ť���ָ�루RadioButton *��������������꣨int�� 
	@���ڲ�����ѡ�е�ѡ��ı�ţ�int�� 
	@�������ܣ��ж�ѡ�����ĸ�ѡ�� 
*/
int whichIsSelected(RadioButton * radioButton,int x,int y)
{
	int h = radioButton->height / radioButton->n; //ÿ��ѡ����ռ�ĸ߶� 
	int X1 = radioButton->X + radioButton->width; //ÿ��ѡ�������½ǵı߽� 
	int Y1 = radioButton->Y + h; //ÿ��ѡ�������½ǵı߽�
	int i;
	for(i=0;i<radioButton->n;i++)
	{
		if((x > radioButton->X && y > radioButton->Y) && (x < X1 && y < Y1))
		{
			radioButton->select = i;
			return i;
		}
		Y1 += h; //��һ��ѡ������½ǵı߽� 
	}
	 	
} 

/*
	@�������ƣ�clearRadioButton 
	@��ڲ�������ѡ��ť���ָ�루RadioButton *�� 
	@���ڲ������� 
	@�������ܣ����һ����ѡ��ť�� 
*/
void clearRadioButton(RadioButton * radioButton)
{
	ACL_Color g_oldPenColor = getPenColor();
	ACL_Color g_oldBrushColor = getBrushColor();
	//���� 
	setPenColor(WHITE);
	setBrushColor(WHITE);
	rectangle(radioButton->X,radioButton->Y,
				radioButton->X + radioButton->width,
				radioButton->Y + radioButton->height);
	radioButton->isPainted = 0; //�����ť��״̬ 
	//�ָ���ǰ������ 
	setPenColor(g_oldPenColor);
	setBrushColor(g_oldBrushColor);			 
}

/*
	@�������ƣ�paintCaret 
	@��ڲ�����������㣨int������Ⱥ͸߶ȣ�int�� 
	@���ڲ������� 
	@�������ܣ�������� 
*/
void paintCaret(int X,int Y,int width,int height)
{
	hideCaret(); //���ع�� 
	setCaretPos(X,Y); //���ù���λ�� 
	setCaretSize(width,height); //���ù��Ĵ�С 
	showCaret(); //��ʾ��� 
}

/*
	@�������ƣ�paintInputBox 
	@��ڲ�����Ҫ�����������InputBox�� 
	@���ڲ������� 
	@�������ܣ���������� 
*/
void paintInputBox(InputBox * inputBox)
{ 
	//��������� 
	rectangle(inputBox->X,inputBox->Y,
				inputBox->X + inputBox->width,
				inputBox->Y + inputBox->height);
	rectangle(inputBox->X + 2,inputBox->Y + 2,
				inputBox->X + inputBox->width - 2,
				inputBox->Y + inputBox->height - 2);
	
	//��ʾ���������� 
	if(inputBox->cols > inputBox->length) //���Ҫ��ʾ���ַ���������������ʾ���ַ�֮�� 
	{
		//��ʾ������е�����
		setTextSize(WORLD_HEIGHT);
		setTextColor(EMPTY);
		paintText(inputBox->X + 4,inputBox->Y + 4,inputBox->inputString);
		//�����������ʾ���
		int caretPosX = (inputBox->X + 4) + WORLD_WIDTH * inputBox->length;
		int caretPosY = (inputBox->Y + 4);
		paintCaret(caretPosX,caretPosY,2,WORLD_HEIGHT);
	}
	else //���Ҫ��ʾ���ַ���������������ʾ���ַ�֮�⣬��Ҫʡ��һЩ�ַ� 
	{
		//��ʾ������е�����
		setTextSize(WORLD_HEIGHT);
		setTextColor(EMPTY);
		int index = inputBox->length - inputBox->cols; //�������ʾ���ַ���������ַ��ĺδ���ʼ��ʾ
		paintText(inputBox->X + 4,inputBox->Y + 4,inputBox->inputString + index);
		//�����������ʾ���
		int caretPosX = (inputBox->X + 4) + WORLD_WIDTH * inputBox->cols;
		int caretPosY = (inputBox->Y + 4);
		paintCaret(caretPosX,caretPosY,2,WORLD_HEIGHT);
	}
}

/*
	@�������ƣ�clearInputBoxContent
	@��ڲ��������������ĵ�ַ��InputBox�� 
	@���ڲ������� 
	@�������ܣ������������ʾ������ 
*/
void clearInputBoxContent(InputBox * inputBox)
{
	inputBox->inputString[0] = 0;
	inputBox->length = 0;
} 

/*
	@�������ƣ�clearInputBox
	@��ڲ��������������ĵ�ַ��InputBox�� 
	@���ڲ������� 
	@�������ܣ��ڰ�ɫ�����½�һ���������� 
*/
void clearInputBox(InputBox * inputBox)
{
	//��¼֮ǰ����ɫ 
	ACL_Color g_oldPenColor = getPenColor();
	ACL_Color g_oldBrushColor = getBrushColor(); 
	
	//����ɫ����Ϊ�ף������»�һ�μ��ǲ��� 
	setBrushColor(WHITE);
	setPenColor(WHITE);
	rectangle(inputBox->X,inputBox->Y,
				inputBox->X + inputBox->width,
				inputBox->Y + inputBox->height);
	hideCaret();
	//�ָ�֮ǰ�����õ���ɫ
	setBrushColor(g_oldBrushColor);
	setPenColor(g_oldPenColor); 
} 

/*
	@�������ƣ�createInputBox 
	@��ڲ�����һ�����������ĵ�ַ����ʼ���꣨int���������������ʾ�ַ��ĸ�����int�� 
	@���ڲ������� 
	@�������ܣ�����һ������� 
*/
void createInputBox(InputBox * inputBox,int X,int Y,int cols)
{
	//�����Ŀ�Ⱥ͸߶�  
	int width = WORLD_WIDTH * cols + 10;
	int height = WORLD_HEIGHT + 8;
	
	inputBox->X = X;
	inputBox->Y = Y;
	inputBox->width = width;
	inputBox->height = height;
	inputBox->cols = cols; 
	inputBox->inputString[0] = 0; 
	inputBox->length = 0; 
} 

/*
	@�������ƣ�whichIsPressed 
	@��ڲ�����һ�鰴ť��Button�����������int����������������꣨int�� 
	@���ڲ�����������İ�ť��������int�� 
	@�������ܣ��ж�һ�鰴ť�����ĸ�������� 
*/
int whichIsPressed(Button * button,int size,int x,int y)
{
	int i;
	for(i=0;i<size;i++)
	{
		if((button[i].isPainted) && isPressed(&button[i],x,y))//�ж��Ƿ��ڰ�ť�ķ�Χ�� 
			return i;
	}
	return -1; 
}

/*
	@�������ƣ�createButtonGroup 
	@��ڲ�������ť�飨Button[]����Ҫ��ʾ�ڰ�ť�ϵ�һ���ַ�����string[]����������int����
				��ť�����ʼ�㣨int����ÿ����ť�Ŀ�Ⱥͳ��ȣ�int����������ť�ļ����int�� 
	@���ڲ������� 
	@�������ܣ�����һ�鰴ť 
*/
void createButtonGroup(Button * button,char ** text,int n,int x,int y,int width,int height,int distance)
{	
	int i;
	for(i=0;i<n;i++,button++)
	{
		createButton(button,x,y,width,height,text[i],20);
		
		y += (height + distance);
	}
}

/*
	@�������ƣ�addButtonGroupPerform
	@��ڲ�����һ�鰴ť��Button[]����������int����һ��Ҫ��ӵ���Ϊ��void (*perform)(void)[]�� 
	@���ڲ������� 
	@�������ܣ���һ�鰴ť�����Ϊ 
*/
void addButtonGroupPerform(Button * button,int size,void (*perform[])(void))
{
	int i;
	for(i=0;i<size;i++)
	{
		button[i].perform = perform[i];
	}
}

/*
	@�������ƣ�clearButtonGroup
	@��ڲ�����һ�鰴ť��Button[]�������� 
	@���ڲ������� 
	@�������ܣ��ڰ�ɫ�����½�һ�鰴ť��� 
*/
void clearButtonGroup(Button * button,int size) 
{
	int i;
	for(i=0;i<size;i++,button++)
	{
		clearButton(button);
	} 
} 

/*
	@�������ƣ�paintButtonGroup
	@��ڲ�������ť�飨Button[]���͸�����int�� 
	@���ڲ������� 
	@�������ܣ�����һ�鰴ť
*/
void paintButtonGroup(Button * button,int size)
{
	int i;	
	
	for(i=0;i<size;i++,button++)
	{
		paintButton(button);
	} 
} 

/*
	@�������ƣ�isPressed
	@��ڲ�����Ҫ���İ�ť��Button��������������꣨int�� 
	@���ڲ����������ť��������򷵻�1�����򣬷���0 
	@�������ܣ��ж�һ����ť�Ƿ񱻵�� 
*/
int isPressed(Button * button,int x,int y)
{
	return (x > button->X) && (x < button->X + button->width) &&
			(y > button->Y) && (y < button->Y + button->height);
}

/*
	@�������ƣ�createButton
	@��ڲ�������ť�ĵ�ַ��Button����������꣨int������Ⱥ͸߶ȣ�int����Ҫ��ʾ�����֣�string�������ֵĴ�С��int�� 
	@���ڲ������� 
	@�������ܣ�����һ����ť 
*/
void createButton(Button * button,int x,int y,int width,int height,char * text,int textSize)
{
	button->X = x;
	button->Y = y;
	button->width = width;
	button->height = height;
	strcpy(button->text,text);
	button->textSize = textSize;
	button->isPainted = 0;
	button->perform = NULL; 
}

/*
	@�������ƣ�addButtonPerform
	@��ڲ�������ť�����ĵ�ַ��Button����Ҫ��Ӱ�ť�ı����ʱ����Ϊ��void (*perform)(void)�� 
	@���ڲ������� 
	@�������ܣ���һ����ť���һ������ť�����ʱ����ִ�еĶ��� 
*/
void addButtonPerform(Button * button,void (*perform)(void))
{
	button->perform = perform;
}

/*
	@�������ƣ�clearButton
	@��ڲ�������ť�����ĵ�ַ��Button�� 
	@���ڲ������� 
	@�������ܣ��ڰ�ɫ�����½�һ����ť��� 
*/
void clearButton(Button * button)
{
	//��¼֮ǰ����ɫ 
	ACL_Color g_oldPenColor = getPenColor();
	ACL_Color g_oldBrushColor = getBrushColor(); 
	
	//����ɫ����Ϊ�ף������»�һ�μ��ǲ��� 
	setBrushColor(WHITE);
	setPenColor(WHITE);
	rectangle(button->X,button->Y,
				button->X + button->width,
				button->Y + button->height);
	//����ť�����Ը�ԭ
	button->isPainted = 0; 
	//�ָ�֮ǰ�����õ���ɫ
	setBrushColor(g_oldBrushColor);
	setPenColor(g_oldPenColor); 
} 

/*
	@�������ƣ�paintButton
	@��ڲ�������ť�ĵ�ַ��Button���������С��int�� 
	@���ڲ������� 
	@�������ܣ�����һ����ť 
*/
void paintButton(Button * button)
{
	int textLen = strlen(button->text);
	
	//��ʾ��ť��״ 
	rectangle(button->X + 2,button->Y + 2,
				button->X + button->width - 2,
				button->Y + button->height - 2);
	setBrushColor(EMPTY);
	rectangle(button->X,button->Y,
				button->X + button->width,
				button->Y + button->height);
	//��ʾ���� 
	setTextSize(button->textSize);//���������С 
	setTextBkColor(EMPTY);//��������ı�����ɫΪ��
	paintText(button->X + button->width / 2 - textLen * button->textSize / 4,
				(button->Y + button->height / 2) - button->textSize / 2,
				button->text);
	button->isPainted = 1;
}

///*
//	@�������ƣ�wait 
//	@��ڲ������ȴ���ʱ��second��int�� 
//	@���ڲ������� 
//	@�������ܣ��ȴ�һ��ʱ������ִ�� 
//*/
//void wait(int second)
//{
//    time_t t1,t2;
//    time(&t1);
//    time(&t2);
//
//    while(t2 - t1 < second)
//        time(&t2);
//}

/*
	@�������ƣ�int2str 
	@��ڲ������ַ���str��Ҫת�������֣�int�� 
	@���ڲ������� 
	@�������ܣ���һ������ת����һ���ַ��� 
*/
void int2str(char * str,int number)
{
	char s[11];
	int reminder;
	int len = 0;
	int i;
	int isNegative = 0;
	//���Ҫת��������Ϊ�� 
	if(number == 0) 
	{
		str[0] = '0';
		str[1] = 0;
		return ;
	}
	
	//���Ϊ��
	if(number < 0)
	{
		number = -number;
		isNegative = 1;
	} 
	
	//��һ�����ֵ�ÿλת�����ַ��������� 
	while(number != 0)
	{
		reminder = number % 10;
		number = number / 10;
		
		s[len++] = reminder + '0'; 
	}
	
	if(isNegative) s[len++] = '-';//������һ������ 
	
	//�õ�һ���ַ��� 
	for(i=0;len>0;i++,len--)
	{
		str[i] = s[len-1];
	} 
	str[i] = 0;
}

/*
	@�������ƣ�str2int 
	@��ڲ�����Ҫת�����ַ�����string�� 
	@���ڲ�����ת����õ������֣�int�� 
	@�������ܣ���һ���ַ���ת��Ϊ�������� 
*/
int str2int(char * str)
{
	int n = 0;
	int isNegative = 0;
	while(str != 0)
	{
		if(*str == '-') isNegative = 1;
 
		if(*str >= '0' && *str <= '9') 
			n = n * 10 + *str - '0';
		str++;
	}
	
	if(isNegative) n = -n; //����Ǹ��� 
	
	return n;
}

/*
	@�������ƣ�lineDegree
	@��ڲ������߶ε�����������꣨int�� 
	@���ڲ������߶���x��ļнǶ�����double�� 
	@�������ܣ������ԣ�X��Y����Ϊԭ�㣬����X��ļн� 
*/
double lineDegree(int X,int Y,int X1,int Y1)
{
	double tan = (double)(Y1 - Y) / (X1 - X);//��ͷ������ֵ����ͷ��ͷΪԭ�� 
	double degree = atan(tan);//���ߺ�x��ļнǵĶ��� 
	//��ʼ��degree��-PI/2~PI/2֮�䣬������Ҫ���н���
	//����ͨ������ֵ������֪����Ҳ���Լ�ΪbeginX - endX; 
	if(X1 - X >= 0) degree = degree + 0;
	else degree = degree + M_PI;
	return degree;
} 

/*���»�ͼ�ĺ�������Ҫ������beginPaint��endPaint�м�ִ��*/

/*
	@�������ƣ�arrow 
	@��ڲ�������ʼ���꣨int������ֹ���꣨int������ͷ��˫����arrowHeadLength��int�� 
	@���ڲ������� 
	@�������ܣ�����һ����ͷ ��ע���������û�ˢ�����ֵ��������ı���ʾ��Ч��  
*/
void arrow(int beginX,int beginY,int endX,int endY,int arrowHeadLength)
{
	double degree = lineDegree(endX,endY,beginX,beginY);
	//��ͷһ֧�����ʼ����  //0.5Ϊ������ߵļн� 
	int arrowHeadX1 = (int)(endX + cos(degree + 0.5) * arrowHeadLength); 
	int arrowHeadY1 = (int)(endY + sin(degree + 0.5) * arrowHeadLength);
	//��ͷ��һ֧�����ʼ���� //0.5Ϊ������ߵļн� 
	int arrowHeadX2 = (int)(endX + cos(degree - 0.5) * arrowHeadLength);
	int arrowHeadY2 = (int)(endY + sin(degree - 0.5) * arrowHeadLength);
	//��ͼ 
	line(beginX,beginY,endX,endY);
	line(arrowHeadX1,arrowHeadY1,endX,endY);
	line(arrowHeadX2,arrowHeadY2,endX,endY);
}

/*
	@�������ƣ�treeLine
	@��ڲ���������Բ��Բ������Ͱ뾶��int�� 
	@���ڲ������� 
	@�������ܣ�������Բ��Բ����һ����̵��߶����ӣ���Բ�ĵ����߳�ȥ�뾶����߶� 
				ע���������û�ˢ�����ֵ��������ı���ʾ��Ч�� 
*/
void treeLine(int roundX1,int roundY1,int roundX2,int roundY2,int radius1,int radius2)
{
	double degree = lineDegree(roundX2,roundY2,roundX1,roundY1);
	//�߶ε���� 
	int beginX = (int)(roundX2 + radius2 * cos(degree));
	int beginY = (int)(roundY2 + radius2 * sin(degree));
	//�߶ε��յ� 
	int endX = (int)(roundX1 - radius1 * cos(degree));
	int endY = (int)(roundY1 - radius2 * sin(degree));
	//���� 
	line(beginX,beginY,endX,endY);
}

/*
	@�������ƣ�paintTreeNode
	@��ڲ�����Բ�ĺͰ뾶��int��������text��string�� 
	@���ڲ������� 
	@�������ܣ�����һ�����Ľڵ㣬�Լ������ݣ�ע���������û�ˢ�����ֵ��������ı���ʾ��Ч�� 
*/
void paintTreeNode(int roundX,int roundY,int radius,char * text)
{
	int textLen = strlen(text); 
	//��ͼ 
	setTextBkColor(EMPTY);//���ֵı���Ϊ͸��
	ellipse(roundX - radius,roundY - radius,roundX + radius,roundY + radius);//��Բ 
	paintText(roundX - textLen * WORLD_WIDTH / 2,roundY - WORLD_HEIGHT / 2,text);//��ʾ���� 
}

/*
	@�������ƣ�paintSeqNode 
	@��ڲ������ڵ������ͳ���int�������֣�string�� 
	@���ڲ������� 
	@�������ܣ�����һ��˳���ĵ㣬ע���������û�ˢ�����ֵ��������ı���ʾ��Ч�� 
*/
void paintSeqNode(int X,int Y,int width,int height,char * text)
{
	int textLen = strlen(text);
	//��ͼ 
	setTextBkColor(EMPTY);//���ֵı���Ϊ͸��
	//�������ݿ� 
	rectangle(X,Y,X + width,Y + height);
	paintText(X + width / 2 - textLen * WORLD_WIDTH / 2,Y + height / 2 - WORLD_HEIGHT / 2,text);
}

/*
	@�������ƣ�paintLinkNode 
	@��ڲ������ڵ������ͳ���int�������֣�string�� 
	@���ڲ������� 
	@�������ܣ�����һ��������Ľڵ㣬ע���������û�ˢ�����ֵ��������ı���ʾ��Ч�� 
*/
void paintLinkNode(int X,int Y,int width,int height,char * text)
{
	int textLen = strlen(text);
	
	//��ͼ 
	setTextBkColor(EMPTY);//���ֵı���Ϊ͸��
	//�������ݿ� 
	rectangle(X,Y,X + width - POINTER_WIDTH,Y + height);
	paintText(X + width / 2 - textLen * WORLD_WIDTH / 2,Y + height / 2 - WORLD_HEIGHT / 2,text);
	//����ָ��� 
	rectangle(X + width - POINTER_WIDTH,Y,X + width,Y + height);
} 

/*
	@�������ƣ�paintDoubleLinkNode 
	@��ڲ������ڵ������ͳ���int�������֣�string�� 
	@���ڲ������� 
	@�������ܣ�����һ��˫����Ľڵ㣬ע���������û�ˢ�����ֵ��������ı���ʾ��Ч�� 
*/
void paintDoubleLinkNode(int X,int Y,int width,int height,char * text)
{
	int textLen = strlen(text);

	//��ͼ 
	setTextBkColor(EMPTY);//���ֵı���Ϊ͸��
	//�������ݿ� 
	rectangle(X - POINTER_WIDTH,Y,X + width - POINTER_WIDTH,Y + height);
	paintText(X - POINTER_WIDTH + width / 2 - textLen * WORLD_WIDTH / 2,Y + width / 2 - WORLD_HEIGHT / 2,text);
	//����ָ��� 
	rectangle(X,Y,X + POINTER_WIDTH,Y + height);
	rectangle(X + width - POINTER_WIDTH,Y,X + width,Y + height);
}

/*
	@�������ƣ�paintEdgeWithWeightDirection
	@��ڲ����������յ㼰�յ�İ뾶��int����Ȩ�أ�int�� 
	@���ڲ������� 
	@�������ܣ�������Ȩ�غ��з���ıߣ�����޷��������endRadius�д���NOT_DIRECTION��
				���û��Ȩ�أ�������weight�д���NOT_WEIGHT 
				ע���������û�ˢ�����ֵ��������ı���ʾ��Ч��  
*/
void paintEdgeWithWeightDirection(int beginX,int beginY,int endX,int endY,int endRadius,int weight)
{
	int textX,textY;
	char text[11];
	
	if(endRadius != NOT_DIRECTION)//�з��� 
	{
		double degree = lineDegree(beginX,beginY,endX,endY);//�Ƕ� 
		//�յ� 
		endX = (int)(endX - endRadius * cos(degree));
		endY = (int)(endY - endRadius * sin(degree));
	} 
	
	if(weight != NOT_WEIGHT)//��Ȩ�� 
	{
		int2str(text,weight);//��Ȩ��ת��������ʾ������ 
		double tan = (double)(beginY - endY) / (beginX - endX);//����ֵ 
		if(tan >= 0)//����������ʾ��λ�� 
		{
			//��ʾ�ڱߵ����·� 
			textX = (beginX + endX) / 2 + 1;
			textY = (beginY + endY) / 2 - 4 - WORLD_HEIGHT;
		}
		else 
		{
			//��ʾ�ڱߵ����Ϸ� 
			textX = (beginX + endX) / 2 + 1;
			textY = (beginY + endY) / 2; 
		}
	}
	
	//��ͼ 
	if(endRadius == NOT_DIRECTION) line(beginX,beginY,endX,endY);//����� 
	else arrow(beginX,beginY,endX,endY,ARROW_HEAD_LENGTH);//����� 
	setTextBkColor(EMPTY);//���ֵı���Ϊ͸��
	if(weight != NOT_WEIGHT) paintText(textX,textY,text);//��ʾȨ�� 
}

/*
	@�������ƣ�paintMapNode 
	@��ڲ�����Բ�ĺͰ뾶��int�������֣�string�� 
	@���ڲ������� 
	@�������ܣ�����һ��ͼ�Ľڵ㣬ע���������û�ˢ�����ֵ��������ı���ʾ��Ч�� 
*/
void paintMapNode(int roundX,int roundY,int radius,char * text)
{
	int textLen = strlen(text); 
	
	//��ͼ 
	setTextBkColor(EMPTY);//���ֵı���Ϊ͸�� 
	ellipse(roundX - radius,roundY - radius,roundX + radius,roundY + radius);//��Բ 
	paintText(roundX + radius,roundY,text);//��ʾ���� 
}

/*
	@�������ƣ�paintIndicator 
	@��ڲ�������ͷ�������յ㣨int�������֣�string�� 
	@���ڲ������� 
	@�������ܣ�����һ��ָʾ����ʵ�ֶ������Ķ������б�ע��˵���� 
				ע���������û�ˢ�����ֵ��������ı���ʾ��Ч��
*/
void paintIndicator(int arrowBeginX,int arrowBeginY,int arrowEndX,int arrowEndY,char * text)
{
	int textLen = strlen(text);
	int textX,textY;
	
	if(arrowEndX == arrowBeginX) 
	{
		textX = arrowBeginX - (textLen * WORLD_WIDTH / 2 + 1);
		if(arrowEndY >= arrowBeginY)//���ַ������Ϸ� 
			textY = arrowBeginY - (WORLD_HEIGHT + 4);
		else //���ַ������·� 
			textY = arrowBeginY + 2; 
	}
	else 
	{
		textY = arrowBeginY - (WORLD_HEIGHT + 2) / 2;
		if(arrowEndX >= arrowBeginX)//���ַ������� 
			textX = arrowBeginX - (textLen * WORLD_WIDTH + 2);
		else//���ַ������ҷ� 
			textX = arrowBeginX + 1; 
	}
	
	//��ͼ 
	setTextBkColor(EMPTY);//���ֵı���Ϊ͸�� 
	arrow(arrowBeginX,arrowBeginY,arrowEndX,arrowEndY,ARROW_HEAD_LENGTH);
	paintText(textX,textY,text);
}

