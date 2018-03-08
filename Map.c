#include "dataAndStructure.h"
//和图有关的函数

int visited[MAP_MAX_SIZE]; //标志变量 

/*
	@函数名称：Map_bfs 
	@入口参数：邻接表的指针（LinkedMap *），被访问的起始图节点（int），
				记录队列（int []）和记录的起始位置（int） 
	@出口参数：被访问了的图节点的个数（int） 
	@函数功能：广度优先遍历图的部分 
*/
int Map_bfs(LinkedMap * map, int i,int * queue,int queueFront)
{ 
	//queue有两个用处，一是记录图节点被访问的顺序，二是当作一个队列来使用
	//从顶点i出发广度优先遍历图的连通分量 
	int queueRear = queueFront; //记录队列的队尾 
	int visitedNum = 0; //被遍历的图节点的个数 
	int currentVertex = i; //当前要遍历的点
	EdgeNode * p; //存有与当前点相连的点的链表
	
	//起始点入列，并标记
	queue[queueRear++] = i;
	visited[i] = 1;
	visitedNum++;
	
	while(queueFront != queueRear)//队列不空
	{
		//一个点出列
		currentVertex = queue[queueFront++];
		
		//记录存有与当前点相连的点的链表
		p = map->edges[currentVertex];
		while(p != NULL)//遍历
		{
			if(visited[p->adjvex] == 0)//没有进入过队列，就入列并标记
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
	@函数名称：Map_bfsTraverse
	@入口参数：邻接表的指针（LinkedMap *），记录队列（int []） 
	@出口参数：图中的连通分量的个数（无向图时） 
	@函数功能：实现图的广度优先遍历 
*/
int Map_bfsTraverse(LinkedMap * map,int * queue)
{  
	int queueRear = 0; //记录队列的队尾  
	int i,count=0;
	
   	for(i=0;i<map->n;i++)
       	visited[i]=0; //初始化标志数组

   	for(i=0;i<map->n;i++)
		if (!visited[i]) //图节点未访问过
		{ 
			count++; //连通分量个数加1（无向图时）
			queueRear += Map_bfs(map,i,queue,queueRear);
		}
		
	for(i=0;i<map->n;i++)
       	visited[i]=0; //清空标志数组
    
    return count; 
}

/*
	@函数名称：Map_dfs 
	@入口参数：邻接表的指针（LinkedMap *），被访问的起始图节点（int），
				记录队列（int []）和记录的起始位置（int） 
	@出口参数：被访问了的图节点的个数（int） 
	@函数功能：深度优先遍历图的部分 
*/
int Map_dfs(LinkedMap * map,int i,int * queue,int queueFront)
{   
	//从顶点i开始深度优先遍历图的连通分量
	int queueRear = queueFront; //记录队列的队尾 
	int visitedNum = 0; //被访问的图节点的个数 
    EdgeNode * p;
  	int stack[100];//定义栈
  	int top=0;//栈顶
  	int currentVertex; //当前访问的点
  	
  	stack[top++] = i; //起始点入栈

  	while(top != 0) //栈不为空
    {
		currentVertex = stack[--top]; //一个点出栈
		
		p = map->edges[currentVertex]; //一个点的所有邻接点
		while(p != NULL) //将该点所有邻接点入栈 
		{
			stack[top++] = p->adjvex;
			p = p->next;
		} 
		
		//当前的点被访问 
		queue[queueRear++] = currentVertex;
		visited[currentVertex] = 1; //标记
		visitedNum++; //被访问的点的个数加1 
    }
    return visitedNum; 
}

/*
	@函数名称：Map_dfsTraverse
	@入口参数：邻接表的指针（LinkedMap *），记录队列（int []） 
	@出口参数：图中的连通分量的个数（无向图时） 
	@函数功能：实现图的深度优先遍历 
*/
int Map_dfsTraverse(LinkedMap * map,int * queue)
{  
	int queueRear = 0; //记录队列的队尾 
	int i,count=0;
	
	for(i=0;i<map->n;i++)
		visited[i]=0; //初始化标志数组
		
	for(i=0;i<map->n;i++)
       	if(!visited[i]) //未访问过
		{
			count++; //连通分量个数加1（无向图时） 
			queueRear += Map_dfs(map,i,queue,queueRear);
		}
    
    for(i=0;i<map->n;i++)
       	visited[i]=0; //清空标志数组
    
    return count;
}

/*
	@函数名称：Map_prim
	@入口参数：图的邻接矩阵的指针（MatrixMap *），储存最小生成树的边的集合（Edge []） 
	@出口参数：无 
	@函数功能：prim算法求无向图的最小生成树 
*/
void Map_prim(MatrixMap * map, Edge * tree)
{  
	Edge x;
   	int length,min,minIndex; //边的长度，最小两栖边和它的在生成树中的位置 
	int i,j;
	int selectVertex,beginVertex,vertex; //加入生成树的点，边的起始点 

   	//建立初始入选点，并初始化生成树边集tree
  	selectVertex = 0; //此时加入生成树的点 
	for(vertex=1,i=0;vertex<map->n;i++,vertex++)
	{
		tree[i].begin = selectVertex;
		tree[i].end = vertex;
		tree[i].length = map->edges[selectVertex][vertex];
	}

	for(i=0;i<map->n-1;i++) //此时i为这次最小两栖边要在tree中放置的位置
	{
		//依次求当前(第i条）最小两栖边，并加入最小生成树中 
		min = tree[i].length;
		minIndex = i;
		for(j=i+1;j<map->n-1;j++)
		{
			if(tree[j].length < min) //如果这条边不是这次的最小两栖边
			{
				//更改最小两栖边的值并记录位置
				min = tree[j].length;
				minIndex = j; //这次最小两栖边的位置
			}
		}
	    if(minIndex != i) //将这次最小两栖边的数据移到i处
	    {
			x = tree[i];
			tree[i] = tree[minIndex];
			tree[minIndex] = x;
	    }
	   	//由于新顶点的加入，修改两栖边的基本信息
	    selectVertex = tree[i].end; //为这次要检查边的点
	    for(j=i+1;j<map->n-1;j++)
	    {
			length = map->edges[selectVertex][tree[j].end]; //取selectVertex的一条边的长度
			if(length < tree[j].length) //如果一个点到selectVertex的长度比之前加入的点的长度小
			{
				tree[j].begin = selectVertex;
				tree[j].length = length;
			}
	    }
	}
}

/*
	@函数名称：Map_getEdges
	@入口参数：图的邻接矩阵的指针（MatrixMap *），存储所有边信息的变量的指针（Edge []） 
	@出口参数：图边的条数（int） 
	@函数功能：得到以邻接矩阵表示的无向图的所有的边 
*/
int Map_getEdges(MatrixMap * map,Edge * edges)
{
	int i,j,k=0;
	int edgesSum = 0; //边的条数 
	
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
	@函数名称：Map_sortEdges 
	@入口参数：图的边（Edge []），排序的左右范围（int） 
	@出口参数：无 
	@函数功能：用快速排序法对图的边进行排序 
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
		while(i < j && key.length <= edges[j].length) j--; //找到大于等于key的边 
        if(i<j)  edges[i++]=edges[j];
        
        while(i < j && key.length > edges[i].length) i++; //找到小于key的边 
       	if(i<j)  edges[j--]=edges[i];
    }
	edges[i] = key;
	
	Map_sortEdges(edges,left,i-1);
	Map_sortEdges(edges,i+1,right);
} 

/*
	@函数名称：Map_kruskal
	@入口参数：图的邻接矩阵的指针（MatrixMap *），储存最小生成树的变量（Edge []） 
	@出口参数：无 
	@函数功能：kruskal求无向图的最小生成树 
*/
void Map_kruskal(MatrixMap * map,Edge * tree)
{  
	Edge edges[map->e]; //图的所有的边 
	int connect[map->n]; //每个点（索引值）属于的连通分量的编号
	int connectNum1,connectNum2; //一个点的连通分量的编号 
	int edgesSum; //边的条数 
	int vertex,edge,selectEdge=0; //图节点，最小生成树的边，当前选择的边 
	int j;
	
	edgesSum = Map_getEdges(map,edges); //得到图的所有边 
	Map_sortEdges(edges,0,edgesSum-1); //对边进行排序 
	//对所有点的属于的连通分量初始化 
	for(vertex=0;vertex<map->n;vertex++)
	{
		connect[vertex] = vertex;
	}
	//求得最小生成树 
	for(edge=0;edge<map->n;edge++)
	{
		//找到边的两点属于不同的连通分量的最小权值边 
		while(connect[edges[selectEdge].begin] == connect[edges[selectEdge].end])
			selectEdge++;
		//加入到生成树中 
		tree[edge] = edges[selectEdge];
		//将两个连通分量进行合并 
		connectNum1 = connect[edges[selectEdge].begin];
		connectNum2 = connect[edges[selectEdge].end];
		for(j=0;j<map->n;j++)
			if(connect[j] == connectNum2)
				connect[j] = connectNum1;
				
		selectEdge++;
	}
} 

/*
	@函数名称：Map_dijkstra
	@入口参数：图的邻接矩阵的指针（MatrixMap *），源点（int），存储路径的变量的指针（Path *） 
	@出口参数：无 
	@函数功能：dijkstra算法求无负权环图的单源最短路径 
*/
void Map_dijkstra(MatrixMap * map,int vertex0,Path * p)
{ 
	int final[map->n]; //表示当前元素是否已求出最短路径
   	int k; //图节点k 
	int vertex,minDist,endVertex; //图节点，最短距离，路径结束的点 
	int i;
	
   	//1初始化路径p->path和距离p->d 
    for(vertex=0;vertex<map->n;vertex++)
    {
		final[vertex] = 0;
		p->distance[vertex] = map->edges[vertex0][vertex];
		
		if(p->distance[vertex] < FINITY) //如果vertex0可以到达这个点，则这个点的前驱为vertex0
			p->path[vertex] = vertex0;
		else //否则，没有
			p->path[vertex] = -1;
    }
	//初始化自身到自身的是否找到最短路径和路径和距离
    final[vertex0] = 1;
    p->distance[vertex0] = 0;
	p->path[vertex0] = -1; 
	
   	//2依次找出n-1个结点加入p中
    for(i=1;i<map->n;i++)
    {
      	minDist = FINITY;
      	//找到最小边的入点
		for(k=0;k<map->n;k++)
		{
			if(!final[k] && p->distance[k] < minDist)
			{
			    endVertex = k;
			    minDist = p->distance[k];
			}
		}

        if(minDist == FINITY) return;
        final[endVertex] = TRUE; //找到源点到v的最小路径

   		//3修改源点到各结点的距离
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
	@函数名称：Map_floyd
	@入口参数：图的邻接矩阵的指针（MatrixMap *），储存所有点的单源最短路径数组（Path []） 
	@出口参数：无 
	@函数功能：floyd算法求所有点的单源最短路径 
*/
void Map_floyd(MatrixMap * map,Path * p)
{
	int beginVertex,endVertex,insertVertex; //路径的起始点，终点，要插入到路径的点 
	int dist; 
	//初始化 
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
	//自低向上求所有点的单源最短路径 
	for(insertVertex=0;insertVertex<map->n;insertVertex++) //尝试在已知的最短路径中插入一个点 
		for(beginVertex=0;beginVertex<map->n;beginVertex++)
			for(endVertex=0;endVertex<map->n;endVertex++)
			{
				dist = p[beginVertex].distance[insertVertex] + p[insertVertex].distance[endVertex];
				if(dist < p[beginVertex].distance[insertVertex]) //插入一个点后路径更短 
				{
					p[beginVertex].distance[endVertex] = dist;
					p[beginVertex].path[endVertex] = insertVertex;
				}
			} 
} 

/*
	@函数名称：Map_free 
	@入口参数：要释放的邻接表的指针（LinkedMap *） 
	@出口参数：无 
	@函数功能：释放一个邻接表的所有的边 
*/
void Map_free(LinkedMap * map)
{
	EdgeNode * p;
	EdgeNode * pp;
	int i;
	
	for(i=0;i<map->n;i++) //遍历每个点 
	{
		p = map->edges[i];
		while(p != NULL) //释放一个点的所有的邻接点 
		{
			pp = p;
			p = p->next;
			free(pp);
		}
	}
}

/*
	@函数名称：Map_Matrix2Linked
	@入口参数：源邻接矩阵指针（MatrixMap *）和目标邻接表（LinkedMap *） 
	@出口参数：无 
	@函数功能：将一个邻接矩阵转换为邻接表表示 
*/
void Map_Matrix2Linked(MatrixMap * map1,LinkedMap * map2)
{
	int i,j,length;
	EdgeNode * edge;
	
	map2->n = map1->n; //顶点的个数 
	map2->e = map1->e; //边的条数 
	//复制点的信息 
	for(i=0;i<map1->n;i++)
	{
		map2->vertices[i] = map1->vertices[i]; 
	} 
	//对边初始化 
	for(i=0;i<map1->n;i++)
	{
		map2->edges[i] = NULL; 
	} 
	//复制边信息 
	for(i=0;i<map1->n;i++)
	{
		for(j=map1->n-1;j>=0;j--)
		{
			length = map1->edges[i][j]; 
        	if(length == 0 || length == FINITY) continue; //两点间无边 
			
			edge = (EdgeNode *)malloc(sizeof(EdgeNode));
			edge->adjvex = j;
			edge->length = length;
			//头插法 
			edge->next = map2->edges[i];
			map2->edges[i] = edge; 
		} 
	} 
} 
