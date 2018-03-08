#include "dataAndStructure.h"

extern g_penColor;
extern g_brushColor;


////////////////////////////////////////////////////////////////////////////////////////////////////// 
/*通用的与绘图有关的函数*/ 


/*
	@函数名称：getPenColor 
	@入口参数：无 
	@出口参数：当前画笔的颜色（ACL_Color） 
	@函数功能：得到当前画笔的颜色 
*/
ACL_Color getPenColor()
{
	return g_penColor;
}

/*
	@函数名称：getBrushColor 
	@入口参数：无 
	@出口参数：当前画刷的颜色（ACL_Color） 
	@函数功能：得到当前画刷的颜色 
*/
ACL_Color getBrushColor()
{
	return g_brushColor;
}

/*
	@函数名称：createRadioButton
	@入口参数：单选按钮组的指针（RadioButton *），起点坐标（int）和长宽（int），
				在单选按钮上显示的一组文本（string []），单选按钮的个数（int），
				当鼠标点击时执行的行为（void (*perfrom)(void)） 
	@出口参数：无 
	@函数功能：创建一组单选按钮 
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
	@函数名称：paintRadioButton
	@入口参数：单选按钮组的指针（RadioButton *） 
	@出口参数：无 
	@函数功能：画出单选按钮组 
*/
void paintRadioButton(RadioButton * radioButton)
{
	int x = radioButton->X,y = radioButton->Y; //每个选项的起始点 
	int h = radioButton->height / radioButton->n; //每个选项所占的高度
	int x1 = x + WORLD_HEIGHT / 2,y1 = y + WORLD_HEIGHT / 2; //绘图时圆的圆心坐标 
	int radius = 5; //圆的半径 
	int i;
	
	setTextSize(WORLD_HEIGHT);
	setBrushColor(EMPTY);
	setPenColor(BLACK); 
	for(i=0;i<radioButton->n;i++)
	{
		//画出选项 
		ellipse(x1 - radius,y1 - radius,x1 + radius,y1 + radius);
		paintText(x + WORLD_HEIGHT + 1,y,radioButton->text[i]);
		//对被选中的选项特殊处理 
		if(i == radioButton->select)
		{
			setBrushColor(BLACK);
			ellipse(x1 - (radius - 3),y1 - (radius - 3),
					x1 + (radius - 3),y1 + (radius - 3));
			setBrushColor(EMPTY);
		}
		
		y += h; //下一个选项的起点
		y1 += h; 
	}
	
	radioButton->isPainted = 1; 
}

/*
	@函数名称：whichIsSelected 
	@入口参数：单选按钮组的指针（RadioButton *），鼠标点击的坐标（int） 
	@出口参数：选中的选项的编号（int） 
	@函数功能：判断选择了哪个选择 
*/
int whichIsSelected(RadioButton * radioButton,int x,int y)
{
	int h = radioButton->height / radioButton->n; //每个选项所占的高度 
	int X1 = radioButton->X + radioButton->width; //每个选项最右下角的边界 
	int Y1 = radioButton->Y + h; //每个选项最右下角的边界
	int i;
	for(i=0;i<radioButton->n;i++)
	{
		if((x > radioButton->X && y > radioButton->Y) && (x < X1 && y < Y1))
		{
			radioButton->select = i;
			return i;
		}
		Y1 += h; //下一个选项的右下角的边界 
	}
	 	
} 

/*
	@函数名称：clearRadioButton 
	@入口参数：单选按钮组的指针（RadioButton *） 
	@出口参数：无 
	@函数功能：清除一个单选按钮组 
*/
void clearRadioButton(RadioButton * radioButton)
{
	ACL_Color g_oldPenColor = getPenColor();
	ACL_Color g_oldBrushColor = getBrushColor();
	//擦除 
	setPenColor(WHITE);
	setBrushColor(WHITE);
	rectangle(radioButton->X,radioButton->Y,
				radioButton->X + radioButton->width,
				radioButton->Y + radioButton->height);
	radioButton->isPainted = 0; //清除按钮的状态 
	//恢复以前的设置 
	setPenColor(g_oldPenColor);
	setBrushColor(g_oldBrushColor);			 
}

/*
	@函数名称：paintCaret 
	@入口参数：光标的起点（int），宽度和高度（int） 
	@出口参数：无 
	@函数功能：画出光标 
*/
void paintCaret(int X,int Y,int width,int height)
{
	hideCaret(); //隐藏光标 
	setCaretPos(X,Y); //设置光标的位置 
	setCaretSize(width,height); //设置光标的大小 
	showCaret(); //显示光标 
}

/*
	@函数名称：paintInputBox 
	@入口参数：要画出的输入框（InputBox） 
	@出口参数：无 
	@函数功能：画出输入框 
*/
void paintInputBox(InputBox * inputBox)
{ 
	//画出输入框 
	rectangle(inputBox->X,inputBox->Y,
				inputBox->X + inputBox->width,
				inputBox->Y + inputBox->height);
	rectangle(inputBox->X + 2,inputBox->Y + 2,
				inputBox->X + inputBox->width - 2,
				inputBox->Y + inputBox->height - 2);
	
	//显示输入框的内容 
	if(inputBox->cols > inputBox->length) //如果要显示的字符在输入框最大能显示的字符之内 
	{
		//显示输入框中的文字
		setTextSize(WORLD_HEIGHT);
		setTextColor(EMPTY);
		paintText(inputBox->X + 4,inputBox->Y + 4,inputBox->inputString);
		//在输入框中显示光标
		int caretPosX = (inputBox->X + 4) + WORLD_WIDTH * inputBox->length;
		int caretPosY = (inputBox->Y + 4);
		paintCaret(caretPosX,caretPosY,2,WORLD_HEIGHT);
	}
	else //如果要显示的字符在输入框最大能显示的字符之外，则要省略一些字符 
	{
		//显示输入框中的文字
		setTextSize(WORLD_HEIGHT);
		setTextColor(EMPTY);
		int index = inputBox->length - inputBox->cols; //输入框显示的字符从输入的字符的何处开始显示
		paintText(inputBox->X + 4,inputBox->Y + 4,inputBox->inputString + index);
		//在输入框中显示光标
		int caretPosX = (inputBox->X + 4) + WORLD_WIDTH * inputBox->cols;
		int caretPosY = (inputBox->Y + 4);
		paintCaret(caretPosX,caretPosY,2,WORLD_HEIGHT);
	}
}

/*
	@函数名称：clearInputBoxContent
	@入口参数：输入框变量的地址（InputBox） 
	@出口参数：无 
	@函数功能：清理输入框显示的内容 
*/
void clearInputBoxContent(InputBox * inputBox)
{
	inputBox->inputString[0] = 0;
	inputBox->length = 0;
} 

/*
	@函数名称：clearInputBox
	@入口参数：输入框变量的地址（InputBox） 
	@出口参数：无 
	@函数功能：在白色背景下将一个输入框清除 
*/
void clearInputBox(InputBox * inputBox)
{
	//记录之前的颜色 
	ACL_Color g_oldPenColor = getPenColor();
	ACL_Color g_oldBrushColor = getBrushColor(); 
	
	//将颜色设置为白，再重新画一次即是擦除 
	setBrushColor(WHITE);
	setPenColor(WHITE);
	rectangle(inputBox->X,inputBox->Y,
				inputBox->X + inputBox->width,
				inputBox->Y + inputBox->height);
	hideCaret();
	//恢复之前的设置的颜色
	setBrushColor(g_oldBrushColor);
	setPenColor(g_oldPenColor); 
} 

/*
	@函数名称：createInputBox 
	@入口参数：一个输入框变量的地址，起始坐标（int），列数即最多显示字符的个数（int） 
	@出口参数：无 
	@函数功能：创建一个输入框 
*/
void createInputBox(InputBox * inputBox,int X,int Y,int cols)
{
	//输入框的宽度和高度  
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
	@函数名称：whichIsPressed 
	@入口参数：一组按钮（Button）及其个数（int），被鼠标点击的坐标（int） 
	@出口参数：被点击的按钮的索引（int） 
	@函数功能：判断一组按钮中是哪个被点击了 
*/
int whichIsPressed(Button * button,int size,int x,int y)
{
	int i;
	for(i=0;i<size;i++)
	{
		if((button[i].isPainted) && isPressed(&button[i],x,y))//判断是否在按钮的范围内 
			return i;
	}
	return -1; 
}

/*
	@函数名称：createButtonGroup 
	@入口参数：按钮组（Button[]），要显示在按钮上的一组字符串（string[]），个数（int），
				按钮组的起始点（int），每个按钮的宽度和长度（int），两个按钮的间隔（int） 
	@出口参数：无 
	@函数功能：创建一组按钮 
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
	@函数名称：addButtonGroupPerform
	@入口参数：一组按钮（Button[]）及个数（int），一组要添加的行为（void (*perform)(void)[]） 
	@出口参数：无 
	@函数功能：给一组按钮添加行为 
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
	@函数名称：clearButtonGroup
	@入口参数：一组按钮（Button[]）及个数 
	@出口参数：无 
	@函数功能：在白色背景下将一组按钮清除 
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
	@函数名称：paintButtonGroup
	@入口参数：按钮组（Button[]）和个数（int） 
	@出口参数：无 
	@函数功能：画出一组按钮
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
	@函数名称：isPressed
	@入口参数：要检测的按钮（Button），鼠标点击的坐标（int） 
	@出口参数：如果按钮被点击，则返回1，否则，返回0 
	@函数功能：判断一个按钮是否被点击 
*/
int isPressed(Button * button,int x,int y)
{
	return (x > button->X) && (x < button->X + button->width) &&
			(y > button->Y) && (y < button->Y + button->height);
}

/*
	@函数名称：createButton
	@入口参数：按钮的地址（Button），起点坐标（int），宽度和高度（int），要显示的文字（string）及文字的大小（int） 
	@出口参数：无 
	@函数功能：创建一个按钮 
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
	@函数名称：addButtonPerform
	@入口参数：按钮变量的地址（Button），要添加按钮的被点击时的行为（void (*perform)(void)） 
	@出口参数：无 
	@函数功能：给一个按钮添加一个当按钮被点击时所置执行的动作 
*/
void addButtonPerform(Button * button,void (*perform)(void))
{
	button->perform = perform;
}

/*
	@函数名称：clearButton
	@入口参数：按钮变量的地址（Button） 
	@出口参数：无 
	@函数功能：在白色背景下将一个按钮清除 
*/
void clearButton(Button * button)
{
	//记录之前的颜色 
	ACL_Color g_oldPenColor = getPenColor();
	ACL_Color g_oldBrushColor = getBrushColor(); 
	
	//将颜色设置为白，再重新画一次即是擦除 
	setBrushColor(WHITE);
	setPenColor(WHITE);
	rectangle(button->X,button->Y,
				button->X + button->width,
				button->Y + button->height);
	//将按钮的属性复原
	button->isPainted = 0; 
	//恢复之前的设置的颜色
	setBrushColor(g_oldBrushColor);
	setPenColor(g_oldPenColor); 
} 

/*
	@函数名称：paintButton
	@入口参数：按钮的地址（Button），字体大小（int） 
	@出口参数：无 
	@函数功能：画出一个按钮 
*/
void paintButton(Button * button)
{
	int textLen = strlen(button->text);
	
	//显示按钮形状 
	rectangle(button->X + 2,button->Y + 2,
				button->X + button->width - 2,
				button->Y + button->height - 2);
	setBrushColor(EMPTY);
	rectangle(button->X,button->Y,
				button->X + button->width,
				button->Y + button->height);
	//显示文字 
	setTextSize(button->textSize);//设置字体大小 
	setTextBkColor(EMPTY);//设置字体的背景颜色为空
	paintText(button->X + button->width / 2 - textLen * button->textSize / 4,
				(button->Y + button->height / 2) - button->textSize / 2,
				button->text);
	button->isPainted = 1;
}

///*
//	@函数名称：wait 
//	@入口参数：等待的时间second（int） 
//	@出口参数：无 
//	@函数功能：等待一段时间后继续执行 
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
	@函数名称：int2str 
	@入口参数：字符串str，要转换的数字（int） 
	@出口参数：无 
	@函数功能：将一个数字转换成一个字符串 
*/
void int2str(char * str,int number)
{
	char s[11];
	int reminder;
	int len = 0;
	int i;
	int isNegative = 0;
	//如果要转换的数字为零 
	if(number == 0) 
	{
		str[0] = '0';
		str[1] = 0;
		return ;
	}
	
	//如果为负
	if(number < 0)
	{
		number = -number;
		isNegative = 1;
	} 
	
	//将一个数字的每位转换成字符并数组中 
	while(number != 0)
	{
		reminder = number % 10;
		number = number / 10;
		
		s[len++] = reminder + '0'; 
	}
	
	if(isNegative) s[len++] = '-';//负数加一个负号 
	
	//得到一个字符串 
	for(i=0;len>0;i++,len--)
	{
		str[i] = s[len-1];
	} 
	str[i] = 0;
}

/*
	@函数名称：str2int 
	@入口参数：要转化的字符串（string） 
	@出口参数：转化后得到的数字（int） 
	@函数功能：将一个字符串转化为整形数字 
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
	
	if(isNegative) n = -n; //如果是负数 
	
	return n;
}

/*
	@函数名称：lineDegree
	@入口参数：线段的两个点的坐标（int） 
	@出口参数：线段与x轴的夹角度数（double） 
	@函数功能：计算以（X，Y）点为原点，线与X轴的夹角 
*/
double lineDegree(int X,int Y,int X1,int Y1)
{
	double tan = (double)(Y1 - Y) / (X1 - X);//箭头的正切值，箭头的头为原点 
	double degree = atan(tan);//主线和x轴的夹角的度数 
	//初始的degree在-PI/2~PI/2之间，下面需要进行矫正
	//可以通过余弦值的正负知道，也可以简化为beginX - endX; 
	if(X1 - X >= 0) degree = degree + 0;
	else degree = degree + M_PI;
	return degree;
} 

/*以下绘图的函数，需要包含在beginPaint和endPaint中间执行*/

/*
	@函数名称：arrow 
	@入口参数：起始坐标（int），终止坐标（int），箭头的双翼长度arrowHeadLength（int） 
	@出口参数：无 
	@函数功能：画出一个箭头 ，注：可以设置画刷和文字的属性来改变显示的效果  
*/
void arrow(int beginX,int beginY,int endX,int endY,int arrowHeadLength)
{
	double degree = lineDegree(endX,endY,beginX,beginY);
	//箭头一支翼的起始坐标  //0.5为翼和主线的夹角 
	int arrowHeadX1 = (int)(endX + cos(degree + 0.5) * arrowHeadLength); 
	int arrowHeadY1 = (int)(endY + sin(degree + 0.5) * arrowHeadLength);
	//箭头另一支翼的起始坐标 //0.5为翼和主线的夹角 
	int arrowHeadX2 = (int)(endX + cos(degree - 0.5) * arrowHeadLength);
	int arrowHeadY2 = (int)(endY + sin(degree - 0.5) * arrowHeadLength);
	//画图 
	line(beginX,beginY,endX,endY);
	line(arrowHeadX1,arrowHeadY1,endX,endY);
	line(arrowHeadX2,arrowHeadY2,endX,endY);
}

/*
	@函数名称：treeLine
	@入口参数：两个圆的圆心坐标和半径（int） 
	@出口参数：无 
	@函数功能：将两个圆的圆周用一条最短的线段连接，即圆心的连线除去半径后的线段 
				注：可以设置画刷和文字的属性来改变显示的效果 
*/
void treeLine(int roundX1,int roundY1,int roundX2,int roundY2,int radius1,int radius2)
{
	double degree = lineDegree(roundX2,roundY2,roundX1,roundY1);
	//线段的起点 
	int beginX = (int)(roundX2 + radius2 * cos(degree));
	int beginY = (int)(roundY2 + radius2 * sin(degree));
	//线段的终点 
	int endX = (int)(roundX1 - radius1 * cos(degree));
	int endY = (int)(roundY1 - radius2 * sin(degree));
	//画线 
	line(beginX,beginY,endX,endY);
}

/*
	@函数名称：paintTreeNode
	@入口参数：圆心和半径（int），文字text（string） 
	@出口参数：无 
	@函数功能：画出一个树的节点，以及其数据，注：可以设置画刷和文字的属性来改变显示的效果 
*/
void paintTreeNode(int roundX,int roundY,int radius,char * text)
{
	int textLen = strlen(text); 
	//画图 
	setTextBkColor(EMPTY);//文字的背景为透明
	ellipse(roundX - radius,roundY - radius,roundX + radius,roundY + radius);//画圆 
	paintText(roundX - textLen * WORLD_WIDTH / 2,roundY - WORLD_HEIGHT / 2,text);//显示文字 
}

/*
	@函数名称：paintSeqNode 
	@入口参数：节点的坐标和长宽（int），文字（string） 
	@出口参数：无 
	@函数功能：画出一个顺序表的点，注：可以设置画刷和文字的属性来改变显示的效果 
*/
void paintSeqNode(int X,int Y,int width,int height,char * text)
{
	int textLen = strlen(text);
	//画图 
	setTextBkColor(EMPTY);//文字的背景为透明
	//画出数据框 
	rectangle(X,Y,X + width,Y + height);
	paintText(X + width / 2 - textLen * WORLD_WIDTH / 2,Y + height / 2 - WORLD_HEIGHT / 2,text);
}

/*
	@函数名称：paintLinkNode 
	@入口参数：节点的坐标和长宽（int），文字（string） 
	@出口参数：无 
	@函数功能：画出一个单链表的节点，注：可以设置画刷和文字的属性来改变显示的效果 
*/
void paintLinkNode(int X,int Y,int width,int height,char * text)
{
	int textLen = strlen(text);
	
	//画图 
	setTextBkColor(EMPTY);//文字的背景为透明
	//画出数据框 
	rectangle(X,Y,X + width - POINTER_WIDTH,Y + height);
	paintText(X + width / 2 - textLen * WORLD_WIDTH / 2,Y + height / 2 - WORLD_HEIGHT / 2,text);
	//画出指针框 
	rectangle(X + width - POINTER_WIDTH,Y,X + width,Y + height);
} 

/*
	@函数名称：paintDoubleLinkNode 
	@入口参数：节点的坐标和长宽（int），文字（string） 
	@出口参数：无 
	@函数功能：画出一个双链表的节点，注：可以设置画刷和文字的属性来改变显示的效果 
*/
void paintDoubleLinkNode(int X,int Y,int width,int height,char * text)
{
	int textLen = strlen(text);

	//画图 
	setTextBkColor(EMPTY);//文字的背景为透明
	//画出数据框 
	rectangle(X - POINTER_WIDTH,Y,X + width - POINTER_WIDTH,Y + height);
	paintText(X - POINTER_WIDTH + width / 2 - textLen * WORLD_WIDTH / 2,Y + width / 2 - WORLD_HEIGHT / 2,text);
	//画出指针框 
	rectangle(X,Y,X + POINTER_WIDTH,Y + height);
	rectangle(X + width - POINTER_WIDTH,Y,X + width,Y + height);
}

/*
	@函数名称：paintEdgeWithWeightDirection
	@入口参数：起点和终点及终点的半径（int），权重（int） 
	@出口参数：无 
	@函数功能：画出带权重和有方向的边，如果无方向可以在endRadius中传入NOT_DIRECTION，
				如果没有权重，可以在weight中传入NOT_WEIGHT 
				注：可以设置画刷和文字的属性来改变显示的效果  
*/
void paintEdgeWithWeightDirection(int beginX,int beginY,int endX,int endY,int endRadius,int weight)
{
	int textX,textY;
	char text[11];
	
	if(endRadius != NOT_DIRECTION)//有方向 
	{
		double degree = lineDegree(beginX,beginY,endX,endY);//角度 
		//终点 
		endX = (int)(endX - endRadius * cos(degree));
		endY = (int)(endY - endRadius * sin(degree));
	} 
	
	if(weight != NOT_WEIGHT)//有权重 
	{
		int2str(text,weight);//将权重转换成能显示的文字 
		double tan = (double)(beginY - endY) / (beginX - endX);//正切值 
		if(tan >= 0)//计算文字显示的位置 
		{
			//显示在边的右下方 
			textX = (beginX + endX) / 2 + 1;
			textY = (beginY + endY) / 2 - 4 - WORLD_HEIGHT;
		}
		else 
		{
			//显示在边的右上方 
			textX = (beginX + endX) / 2 + 1;
			textY = (beginY + endY) / 2; 
		}
	}
	
	//画图 
	if(endRadius == NOT_DIRECTION) line(beginX,beginY,endX,endY);//无向边 
	else arrow(beginX,beginY,endX,endY,ARROW_HEAD_LENGTH);//有向边 
	setTextBkColor(EMPTY);//文字的背景为透明
	if(weight != NOT_WEIGHT) paintText(textX,textY,text);//显示权重 
}

/*
	@函数名称：paintMapNode 
	@入口参数：圆心和半径（int），文字（string） 
	@出口参数：无 
	@函数功能：画出一个图的节点，注：可以设置画刷和文字的属性来改变显示的效果 
*/
void paintMapNode(int roundX,int roundY,int radius,char * text)
{
	int textLen = strlen(text); 
	
	//画图 
	setTextBkColor(EMPTY);//文字的背景为透明 
	ellipse(roundX - radius,roundY - radius,roundX + radius,roundY + radius);//画圆 
	paintText(roundX + radius,roundY,text);//显示文字 
}

/*
	@函数名称：paintIndicator 
	@入口参数：箭头的起点和终点（int），文字（string） 
	@出口参数：无 
	@函数功能：画出一个指示器，实现对其他的东西进行标注或说明等 
				注：可以设置画刷和文字的属性来改变显示的效果
*/
void paintIndicator(int arrowBeginX,int arrowBeginY,int arrowEndX,int arrowEndY,char * text)
{
	int textLen = strlen(text);
	int textX,textY;
	
	if(arrowEndX == arrowBeginX) 
	{
		textX = arrowBeginX - (textLen * WORLD_WIDTH / 2 + 1);
		if(arrowEndY >= arrowBeginY)//文字放起点的上方 
			textY = arrowBeginY - (WORLD_HEIGHT + 4);
		else //文字放起点的下方 
			textY = arrowBeginY + 2; 
	}
	else 
	{
		textY = arrowBeginY - (WORLD_HEIGHT + 2) / 2;
		if(arrowEndX >= arrowBeginX)//文字放起点的左方 
			textX = arrowBeginX - (textLen * WORLD_WIDTH + 2);
		else//文字放起点的右方 
			textX = arrowBeginX + 1; 
	}
	
	//画图 
	setTextBkColor(EMPTY);//文字的背景为透明 
	arrow(arrowBeginX,arrowBeginY,arrowEndX,arrowEndY,ARROW_HEAD_LENGTH);
	paintText(textX,textY,text);
}

