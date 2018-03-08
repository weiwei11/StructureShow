#include "dataAndStructure.h"
//��ͼ�йصĺ���

int visited[MAP_MAX_SIZE]; //��־���� 

/*
	@�������ƣ�Map_bfs 
	@��ڲ������ڽӱ��ָ�루LinkedMap *���������ʵ���ʼͼ�ڵ㣨int����
				��¼���У�int []���ͼ�¼����ʼλ�ã�int�� 
	@���ڲ������������˵�ͼ�ڵ�ĸ�����int�� 
	@�������ܣ�������ȱ���ͼ�Ĳ��� 
*/
int Map_bfs(LinkedMap * map, int i,int * queue,int queueFront)
{ 
	//queue�������ô���һ�Ǽ�¼ͼ�ڵ㱻���ʵ�˳�򣬶��ǵ���һ��������ʹ��
	//�Ӷ���i����������ȱ���ͼ����ͨ���� 
	int queueRear = queueFront; //��¼���еĶ�β 
	int visitedNum = 0; //��������ͼ�ڵ�ĸ��� 
	int currentVertex = i; //��ǰҪ�����ĵ�
	EdgeNode * p; //�����뵱ǰ�������ĵ������
	
	//��ʼ�����У������
	queue[queueRear++] = i;
	visited[i] = 1;
	visitedNum++;
	
	while(queueFront != queueRear)//���в���
	{
		//һ�������
		currentVertex = queue[queueFront++];
		
		//��¼�����뵱ǰ�������ĵ������
		p = map->edges[currentVertex];
		while(p != NULL)//����
		{
			if(visited[p->adjvex] == 0)//û�н�������У������в����
			{
				queue[queueRear++] = p->adjvex;
				visited[p->adjvex] = 1;
				visitedNum++;
			}
			p = p->next;
		}
	}
	return visitedNum;
}

/*
	@�������ƣ�Map_bfsTraverse
	@��ڲ������ڽӱ��ָ�루LinkedMap *������¼���У�int []�� 
	@���ڲ�����ͼ�е���ͨ�����ĸ���������ͼʱ�� 
	@�������ܣ�ʵ��ͼ�Ĺ�����ȱ��� 
*/
int Map_bfsTraverse(LinkedMap * map,int * queue)
{  
	int queueRear = 0; //��¼���еĶ�β  
	int i,count=0;
	
   	for(i=0;i<map->n;i++)
       	visited[i]=0; //��ʼ����־����

   	for(i=0;i<map->n;i++)
		if (!visited[i]) //ͼ�ڵ�δ���ʹ�
		{ 
			count++; //��ͨ����������1������ͼʱ��
			queueRear += Map_bfs(map,i,queue,queueRear);
		}
		
	for(i=0;i<map->n;i++)
       	visited[i]=0; //��ձ�־����
    
    return count; 
}

/*
	@�������ƣ�Map_dfs 
	@��ڲ������ڽӱ��ָ�루LinkedMap *���������ʵ���ʼͼ�ڵ㣨int����
				��¼���У�int []���ͼ�¼����ʼλ�ã�int�� 
	@���ڲ������������˵�ͼ�ڵ�ĸ�����int�� 
	@�������ܣ�������ȱ���ͼ�Ĳ��� 
*/
int Map_dfs(LinkedMap * map,int i,int * queue,int queueFront)
{   
	//�Ӷ���i��ʼ������ȱ���ͼ����ͨ����
	int queueRear = queueFront; //��¼���еĶ�β 
	int visitedNum = 0; //�����ʵ�ͼ�ڵ�ĸ��� 
    EdgeNode * p;
  	int stack[100];//����ջ
  	int top=0;//ջ��
  	int currentVertex; //��ǰ���ʵĵ�
  	
  	stack[top++] = i; //��ʼ����ջ

  	while(top != 0) //ջ��Ϊ��
    {
		currentVertex = stack[--top]; //һ�����ջ
		
		p = map->edges[currentVertex]; //һ����������ڽӵ�
		while(p != NULL) //���õ������ڽӵ���ջ 
		{
			stack[top++] = p->adjvex;
			p = p->next;
		} 
		
		//��ǰ�ĵ㱻���� 
		queue[queueRear++] = currentVertex;
		visited[currentVertex] = 1; //���
		visitedNum++; //�����ʵĵ�ĸ�����1 
    }
    return visitedNum; 
}

/*
	@�������ƣ�Map_dfsTraverse
	@��ڲ������ڽӱ��ָ�루LinkedMap *������¼���У�int []�� 
	@���ڲ�����ͼ�е���ͨ�����ĸ���������ͼʱ�� 
	@�������ܣ�ʵ��ͼ��������ȱ��� 
*/
int Map_dfsTraverse(LinkedMap * map,int * queue)
{  
	int queueRear = 0; //��¼���еĶ�β 
	int i,count=0;
	
	for(i=0;i<map->n;i++)
		visited[i]=0; //��ʼ����־����
		
	for(i=0;i<map->n;i++)
       	if(!visited[i]) //δ���ʹ�
		{
			count++; //��ͨ����������1������ͼʱ�� 
			queueRear += Map_dfs(map,i,queue,queueRear);
		}
    
    for(i=0;i<map->n;i++)
       	visited[i]=0; //��ձ�־����
    
    return count;
}

/*
	@�������ƣ�Map_prim
	@��ڲ�����ͼ���ڽӾ����ָ�루MatrixMap *����������С�������ıߵļ��ϣ�Edge []�� 
	@���ڲ������� 
	@�������ܣ�prim�㷨������ͼ����С������ 
*/
void Map_prim(MatrixMap * map, Edge * tree)
{  
	Edge x;
   	int length,min,minIndex; //�ߵĳ��ȣ���С���ܱߺ��������������е�λ�� 
	int i,j;
	int selectVertex,beginVertex,vertex; //�����������ĵ㣬�ߵ���ʼ�� 

   	//������ʼ��ѡ�㣬����ʼ���������߼�tree
  	selectVertex = 0; //��ʱ�����������ĵ� 
	for(vertex=1,i=0;vertex<map->n;i++,vertex++)
	{
		tree[i].begin = selectVertex;
		tree[i].end = vertex;
		tree[i].length = map->edges[selectVertex][vertex];
	}

	for(i=0;i<map->n-1;i++) //��ʱiΪ�����С���ܱ�Ҫ��tree�з��õ�λ��
	{
		//������ǰ(��i������С���ܱߣ���������С�������� 
		min = tree[i].length;
		minIndex = i;
		for(j=i+1;j<map->n-1;j++)
		{
			if(tree[j].length < min) //��������߲�����ε���С���ܱ�
			{
				//������С���ܱߵ�ֵ����¼λ��
				min = tree[j].length;
				minIndex = j; //�����С���ܱߵ�λ��
			}
		}
	    if(minIndex != i) //�������С���ܱߵ������Ƶ�i��
	    {
			x = tree[i];
			tree[i] = tree[minIndex];
			tree[minIndex] = x;
	    }
	   	//�����¶���ļ��룬�޸����ܱߵĻ�����Ϣ
	    selectVertex = tree[i].end; //Ϊ���Ҫ���ߵĵ�
	    for(j=i+1;j<map->n-1;j++)
	    {
			length = map->edges[selectVertex][tree[j].end]; //ȡselectVertex��һ���ߵĳ���
			if(length < tree[j].length) //���һ���㵽selectVertex�ĳ��ȱ�֮ǰ����ĵ�ĳ���С
			{
				tree[j].begin = selectVertex;
				tree[j].length = length;
			}
	    }
	}
}

/*
	@�������ƣ�Map_getEdges
	@��ڲ�����ͼ���ڽӾ����ָ�루MatrixMap *�����洢���б���Ϣ�ı�����ָ�루Edge []�� 
	@���ڲ�����ͼ�ߵ�������int�� 
	@�������ܣ��õ����ڽӾ����ʾ������ͼ�����еı� 
*/
int Map_getEdges(MatrixMap * map,Edge * edges)
{
	int i,j,k=0;
	int edgesSum = 0; //�ߵ����� 
	
	for(i=0;i<map->n;i++)
	{
		for(j=0;j<i;j++)
		{
			if(map->edges[i][j] != 0 && map->edges[i][j] < FINITY)
			{
				edges[k].begin = i;
				edges[k].end = j;
				edges[k].length = map->edges[i][j]; 
				edgesSum++;
				k++;
			}
		}
	}
	return edgesSum;
}

/*
	@�������ƣ�Map_sortEdges 
	@��ڲ�����ͼ�ıߣ�Edge []������������ҷ�Χ��int�� 
	@���ڲ������� 
	@�������ܣ��ÿ������򷨶�ͼ�ı߽������� 
*/
void Map_sortEdges(Edge * edges,int left,int right)
{
	Edge key;
	int i,j;
	
	if(left >= right) return ;
	i = left;
	j = right;
	key = edges[0];
	
	while(i < j)
	{  
		while(i < j && key.length <= edges[j].length) j--; //�ҵ����ڵ���key�ı� 
        if(i<j)  edges[i++]=edges[j];
        
        while(i < j && key.length > edges[i].length) i++; //�ҵ�С��key�ı� 
       	if(i<j)  edges[j--]=edges[i];
    }
	edges[i] = key;
	
	Map_sortEdges(edges,left,i-1);
	Map_sortEdges(edges,i+1,right);
} 

/*
	@�������ƣ�Map_kruskal
	@��ڲ�����ͼ���ڽӾ����ָ�루MatrixMap *����������С�������ı�����Edge []�� 
	@���ڲ������� 
	@�������ܣ�kruskal������ͼ����С������ 
*/
void Map_kruskal(MatrixMap * map,Edge * tree)
{  
	Edge edges[map->e]; //ͼ�����еı� 
	int connect[map->n]; //ÿ���㣨����ֵ�����ڵ���ͨ�����ı��
	int connectNum1,connectNum2; //һ�������ͨ�����ı�� 
	int edgesSum; //�ߵ����� 
	int vertex,edge,selectEdge=0; //ͼ�ڵ㣬��С�������ıߣ���ǰѡ��ı� 
	int j;
	
	edgesSum = Map_getEdges(map,edges); //�õ�ͼ�����б� 
	Map_sortEdges(edges,0,edgesSum-1); //�Ա߽������� 
	//�����е�����ڵ���ͨ������ʼ�� 
	for(vertex=0;vertex<map->n;vertex++)
	{
		connect[vertex] = vertex;
	}
	//�����С������ 
	for(edge=0;edge<map->n;edge++)
	{
		//�ҵ��ߵ��������ڲ�ͬ����ͨ��������СȨֵ�� 
		while(connect[edges[selectEdge].begin] == connect[edges[selectEdge].end])
			selectEdge++;
		//���뵽�������� 
		tree[edge] = edges[selectEdge];
		//��������ͨ�������кϲ� 
		connectNum1 = connect[edges[selectEdge].begin];
		connectNum2 = connect[edges[selectEdge].end];
		for(j=0;j<map->n;j++)
			if(connect[j] == connectNum2)
				connect[j] = connectNum1;
				
		selectEdge++;
	}
} 

/*
	@�������ƣ�Map_dijkstra
	@��ڲ�����ͼ���ڽӾ����ָ�루MatrixMap *����Դ�㣨int�����洢·���ı�����ָ�루Path *�� 
	@���ڲ������� 
	@�������ܣ�dijkstra�㷨���޸�Ȩ��ͼ�ĵ�Դ���·�� 
*/
void Map_dijkstra(MatrixMap * map,int vertex0,Path * p)
{ 
	int final[map->n]; //��ʾ��ǰԪ���Ƿ���������·��
   	int k; //ͼ�ڵ�k 
	int vertex,minDist,endVertex; //ͼ�ڵ㣬��̾��룬·�������ĵ� 
	int i;
	
   	//1��ʼ��·��p->path�;���p->d 
    for(vertex=0;vertex<map->n;vertex++)
    {
		final[vertex] = 0;
		p->distance[vertex] = map->edges[vertex0][vertex];
		
		if(p->distance[vertex] < FINITY) //���vertex0���Ե�������㣬��������ǰ��Ϊvertex0
			p->path[vertex] = vertex0;
		else //����û��
			p->path[vertex] = -1;
    }
	//��ʼ������������Ƿ��ҵ����·����·���;���
    final[vertex0] = 1;
    p->distance[vertex0] = 0;
	p->path[vertex0] = -1; 
	
   	//2�����ҳ�n-1��������p��
    for(i=1;i<map->n;i++)
    {
      	minDist = FINITY;
      	//�ҵ���С�ߵ����
		for(k=0;k<map->n;k++)
		{
			if(!final[k] && p->distance[k] < minDist)
			{
			    endVertex = k;
			    minDist = p->distance[k];
			}
		}

        if(minDist == FINITY) return;
        final[endVertex] = TRUE; //�ҵ�Դ�㵽v����С·��

   		//3�޸�Դ�㵽�����ľ���
		for(k=0;k<map->n;k++)
		{
			if(!final[k] && ((minDist + map->edges[endVertex][k]) < p->distance[k]))
			{
			  	p->distance[k] = minDist + map->edges[endVertex][k];
			  	p->path[k] = endVertex;
			}
		}
    }
}

/*
	@�������ƣ�Map_floyd
	@��ڲ�����ͼ���ڽӾ����ָ�루MatrixMap *�����������е�ĵ�Դ���·�����飨Path []�� 
	@���ڲ������� 
	@�������ܣ�floyd�㷨�����е�ĵ�Դ���·�� 
*/
void Map_floyd(MatrixMap * map,Path * p)
{
	int beginVertex,endVertex,insertVertex; //·������ʼ�㣬�յ㣬Ҫ���뵽·���ĵ� 
	int dist; 
	//��ʼ�� 
	for(beginVertex=0;beginVertex<map->n;beginVertex++)
	{
		for(endVertex=0;endVertex<map->n;endVertex++)
		{
			p[beginVertex].distance[endVertex] = map->edges[beginVertex][endVertex];
			if(beginVertex != endVertex && map->edges[beginVertex][endVertex] < FINITY) 
				p[beginVertex].path[endVertex] = beginVertex;
			else 
				p[beginVertex].path[endVertex] = -1;
		}
	}
	//�Ե����������е�ĵ�Դ���·�� 
	for(insertVertex=0;insertVertex<map->n;insertVertex++) //��������֪�����·���в���һ���� 
		for(beginVertex=0;beginVertex<map->n;beginVertex++)
			for(endVertex=0;endVertex<map->n;endVertex++)
			{
				dist = p[beginVertex].distance[insertVertex] + p[insertVertex].distance[endVertex];
				if(dist < p[beginVertex].distance[insertVertex]) //����һ�����·������ 
				{
					p[beginVertex].distance[endVertex] = dist;
					p[beginVertex].path[endVertex] = insertVertex;
				}
			} 
} 

/*
	@�������ƣ�Map_free 
	@��ڲ�����Ҫ�ͷŵ��ڽӱ��ָ�루LinkedMap *�� 
	@���ڲ������� 
	@�������ܣ��ͷ�һ���ڽӱ�����еı� 
*/
void Map_free(LinkedMap * map)
{
	EdgeNode * p;
	EdgeNode * pp;
	int i;
	
	for(i=0;i<map->n;i++) //����ÿ���� 
	{
		p = map->edges[i];
		while(p != NULL) //�ͷ�һ��������е��ڽӵ� 
		{
			pp = p;
			p = p->next;
			free(pp);
		}
	}
}

/*
	@�������ƣ�Map_Matrix2Linked
	@��ڲ�����Դ�ڽӾ���ָ�루MatrixMap *����Ŀ���ڽӱ�LinkedMap *�� 
	@���ڲ������� 
	@�������ܣ���һ���ڽӾ���ת��Ϊ�ڽӱ��ʾ 
*/
void Map_Matrix2Linked(MatrixMap * map1,LinkedMap * map2)
{
	int i,j,length;
	EdgeNode * edge;
	
	map2->n = map1->n; //����ĸ��� 
	map2->e = map1->e; //�ߵ����� 
	//���Ƶ����Ϣ 
	for(i=0;i<map1->n;i++)
	{
		map2->vertices[i] = map1->vertices[i]; 
	} 
	//�Ա߳�ʼ�� 
	for(i=0;i<map1->n;i++)
	{
		map2->edges[i] = NULL; 
	} 
	//���Ʊ���Ϣ 
	for(i=0;i<map1->n;i++)
	{
		for(j=map1->n-1;j>=0;j--)
		{
			length = map1->edges[i][j]; 
        	if(length == 0 || length == FINITY) continue; //������ޱ� 
			
			edge = (EdgeNode *)malloc(sizeof(EdgeNode));
			edge->adjvex = j;
			edge->length = length;
			//ͷ�巨 
			edge->next = map2->edges[i];
			map2->edges[i] = edge; 
		} 
	} 
} 
