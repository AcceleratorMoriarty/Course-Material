#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define MAX 100
#define isLetter(a) ((((a) >= 'a')&&((a)<='z'))||(((a) >= 'A')&& ((a) <='Z')))
#define LENGTH(a) (sizeof(a) / sizeof(a[0]))

//邻接表中表对应的链表的顶点
typedef struct ENode
{
	int ivex;//该边所指向的顶点的位置
	struct ENode* next_edge;//指向下一条弧的指针
}ENode, * PENode;


// 邻接表中表的顶点
typedef struct _VNode
{
	char data;
	ENode* first_edge;
}VNode;

// 邻接表
typedef struct _LGraph
{
	int vexnum;	//顶点数
	int edgnum; //边数
	VNode vexs[MAX];
}LGraph;
static int getPosition(LGraph G, char ch)
{
	int i;
	for(i = 0; i < G.vexnum; i++)
		if(G.vexs[i].data == ch)
			return i;
	return -1;
}
static void linkLast(ENode* list, ENode* node)
{
	ENode* p = list;
	while(p->next_edge)
		p = p->next_edge;
	p->next_edge = node;
}



//创建邻接表
LGraph* CreateGraph()
{
	char c1, c2;
	//无向图

	//char vexs[] = {'0', '1', '2', '3', '4', '5', '6', '7'};
	//char edges[][2] = {
	//	{ '0', '1' },
	//	{ '0', '2' },
	//	{ '1', '0' },
	//	{ '1', '3' },
	//	{ '1', '4' },
	//	{ '2', '0' },
	//	{ '2', '5' },
	//	{ '2', '6' },
	//	{ '3', '1' },
	//	{ '3', '7' }, 
	//	{ '4', '1' },
	//	{ '4', '7' },  
	//	{ '5', '2' },
	//	{ '5', '6' },  
	//	{ '6', '2' },
	//	{ '6', '5' },
	//	{ '7', '3' },
	//	{ '7', '4' }
	//	};


	// 有向图
	
	 char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
	 char edges[][2] = {
	 	{ 'A', 'B' },
	 	{ 'B', 'C' },
	 	{ 'B', 'E' },
	 	{ 'B', 'F' },
	 	{ 'C', 'E' },
	 	{ 'D', 'C' },
	 	{ 'E', 'B' }, 
	 	{ 'E', 'D' }, 
	 	{ 'F', 'G' } };



	int vlen = LENGTH(vexs);
	int elen = LENGTH(edges);
	int i, p1, p2;
	ENode* node1;
	LGraph* pG;

	if((pG = (LGraph*)malloc(sizeof(LGraph))) == NULL)
		return NULL;
	memset(pG, 0, sizeof(LGraph));

	//初始化顶点数和边数
	pG->vexnum = vlen;
	pG->edgnum = elen;

	//初始化邻接表顶点
	for(i = 0; i < pG->vexnum; i++)
	{
		pG->vexs[i].data = vexs[i];
		pG->vexs[i].first_edge = NULL;
	}
	//初始化邻接表的边
	for(i = 0; i < pG->edgnum; i++)
	{
		//读取边的起始顶点和结束顶点
		c1 = edges[i][0];
		c2 = edges[i][1];

		p1 = getPosition(*pG, c1);
		p2 = getPosition(*pG, c2);

		//初始化node1
		node1 = (ENode*)calloc(1,sizeof(ENode));
		node1->ivex = p2;
		//将node1链接到"p1所在链表的末尾"
		if(pG->vexs[p1].first_edge == NULL)
			pG->vexs[p1].first_edge = node1;
		else
			linkLast(pG->vexs[p1].first_edge, node1);
	}
	return pG;
}
//打印邻接表图
void printLGraph(LGraph* pG)
{
	int i, j;
	ENode* node;

	printf("List Graph:\n");
	for(i = 0; i < pG->vexnum; i++)
	{
		printf("%d(%c): ", i, pG->vexs[i].data);
		node = pG->vexs[i].first_edge;
		while(node != NULL)
		{
			printf("%d(%c) ", node->ivex, pG->vexs[node->ivex].data);
			node = node->next_edge;
		}
		printf("\n");
	}
}
//邻接表的广度优先遍历
void BFS(LGraph G)
{
	int head = 0;
	int rear = 0;
	int queue[MAX];
	int visited[MAX];	//顶点访问标记
	int i, j, k;
	ENode* node;

	for ( i = 0; i < G.vexnum; i++)
		visited[i] = 0;
	printf("BFS:");
	
	for ( i = 0; i < G.vexnum; i++)
	{
		if(!visited[i])
		{
			visited[i] = 1;
			printf("%c", G.vexs[i].data);
			queue[rear++] = i;	//入队列
		}
		while(head != rear)
		{
			j = queue[head++];	//出队列
			node = G.vexs[j].first_edge;
			while(node != NULL)
			{
				k = node->ivex;
				if(!visited[k])
				{
					visited[k] = 1;
					printf("%c", G.vexs[k].data);
					queue[rear++] = k;
				}
				node = node->next_edge;
			}
		}
	}
	printf("\n");
}
//邻接表的深度优先遍历
static void DFS(LGraph G, int i, int* visited)
{
	ENode* node;
	visited[i] = 1;
	printf("%c", G.vexs[i].data);
	node = G.vexs[i].first_edge;
	while(node != NULL)
	{
		if(!visited[node->ivex])
			DFS(G, node->ivex, visited);
		node = node->next_edge;
	}
}
void DFSTraverse(LGraph G)
{
	int i;
	int visited[MAX];	//顶点访问标记

	for ( i = 0; i < G.vexnum; i++)
		visited[i] = 0;
	printf("DFS:");
	for ( i = 0; i < G.vexnum; i++)
	{
		if(!visited[i])
			DFS(G, i, visited);
	}
	printf("\n");
}
void main()
{
	LGraph* pG;

	pG = CreateGraph();
	printLGraph(pG);
	BFS(*pG);
	DFSTraverse(*pG);

}