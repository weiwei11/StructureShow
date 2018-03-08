#include "dataAndStructure.h"

int b[10]={0};
int cx=0;
int cy=0;
LinkNode* jd;


LinkList LinkList_createNode(int x, int y);
void jdPaint(int x,int y)
{
	
	line(x-30,y-18,x+30,y-18);
    line(x-30,y+18,x+30,y+18);
    line(x+30,y-18,x+30,y+18);
    line(x-30,y-18,x-30,y+18);
    line(x+14,y-18,x+14,y+18);
    line(x+22,y-4,x+26,y+4);
    line(x+22,y-4,x+18,y+4);
    
}
 
void jdDel(int x,int y)
{
	line(x-20,y-20,x+20,y+20);
	line(x+20,y-20,x-20,y+20);
}

jdBack(int x,int y)
{
	line(x-50,y,x-25,y-25);
	line(x-25,y-25,x+25,y-25);
	line(x+25,y-25,x+25,y+25);
	line(x+25,y+25,x-25,y+25);
	line(x-25,y+25,x-50,y);
}

void jdMove(int bt,int b[])
{
	LinkList p,q,r;
	r=q=jd;
    beginPaint();
	
    clearDevice();
    line(0,100,1000,100);
    jdBack(75,50);
    line(125,0,125,100);
    jdPaint(225,50); 
    line(325,0,325,100);
    jdDel(425,50);
    
    line(525,0,525,100);
//    setPenWidth(1); 
//    setPenColor(RED);
	
	if(b[1])
	{
		jdPaint(cx,cy);
	}
    if(bt==LEFT_BUTTON && cy>=100)
    {
    	
    	p = LinkList_createNode(cx,cy); 
    	q = p;
		p->next = NULL;
		b[1]=0; 
		
    } 
	while(r)
	{
		//jdPaint(r->x,r->y);
		r=r->next;
	}
    endPaint();
}

void buttonClick(int x,int y,int bt,int event)
{
	
	if(event==MOUSEMOVE)
    {
        cx = x;
        cy = y;
    }
//	if(event!=BUTTON_DOWN)
//        return;
    if(bt==LEFT_BUTTON && x>=0 && x<125 && y>0 && y<100)
    {
    	b[0]=1;
    }
    else if(bt==LEFT_BUTTON && x>=125 && x<325 && y>0 && y<100)
    {
    	b[1]=1;
    }
    else if(bt==LEFT_BUTTON && x>=325 && x<525 && y>0 && y<100)
    {
    	b[2]=1;
    }
	
    jdMove(bt,b);
}
