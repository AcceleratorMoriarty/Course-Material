#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VEX 100       // 最大顶点数
#define INFINITY 65535    // 用65535来代表无穷大
#define LENGTH(a) (sizeof(a) / sizeof(a[0]))

typedef struct {
    char vexs[MAX_VEX];            // 顶点集合
    int matrix[MAX_VEX][MAX_VEX];  // 邻接矩阵
    int vexnum;                    // 图的顶点数
    int edgnum;                    // 图的边数
} MGraph;


// 获取顶点在数组中的位置
int getPosition(MGraph* G, char ch) {
    for (int i = 0; i < G->vexnum; i++) {
        if (G->vexs[i] == ch)
            return i;
    }
    return -1;
}

// 创建无向图的邻接矩阵
void createMGraph_wuxiang(MGraph* G) {
    char vexs[] = { '0', '1', '2', '3', '4', '5', '6', '7' };
    char edges[][2] = {
        {'0', '1'}, {'0', '2'}, {'1', '3'}, {'1', '4'},
        {'2', '5'}, {'2', '6'}, {'3', '7'}, {'4', '7'},
        {'5', '6'}
    };

    int vlen = LENGTH(vexs);
    int elen = LENGTH(edges);

    G->vexnum = vlen;
    G->edgnum = elen;

    // 初始化顶点
    for (int i = 0; i < G->vexnum; i++) {
        G->vexs[i] = vexs[i];
    }

    // 初始化邻接矩阵
    for (int i = 0; i < G->vexnum; i++) {
        for (int j = 0; j < G->vexnum; j++) {
                G->matrix[i][j] = 0;
        }
    }

    // 填充邻接矩阵
    for (int i = 0; i < elen; i++) {
        int start = getPosition(G, edges[i][0]);
        int end = getPosition(G, edges[i][1]);

        if (start != -1 && end != -1) {
            G->matrix[start][end] = 1;  // 有边为1
            G->matrix[end][start] = 1;  // 无向图，需要填充两次
        }
    }
}

void createMGraph_youxiang(MGraph* G) {
    char vexs[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
    char edges[][2] = {
        { 'A', 'B' },
        { 'B', 'C' },
        { 'B', 'E' },
        { 'B', 'F' },
        { 'C', 'E' },
        { 'D', 'C' },
        { 'E', 'B' },
        { 'E', 'D' },
        { 'F', 'G' }
    };

    int vlen = LENGTH(vexs);
    int elen = LENGTH(edges);

    G->vexnum = vlen;
    G->edgnum = elen;

    // 初始化顶点
    for (int i = 0; i < G->vexnum; i++) {
        G->vexs[i] = vexs[i];
    }

    // 初始化邻接矩阵
    for (int i = 0; i < G->vexnum; i++) {
        for (int j = 0; j < G->vexnum; j++) {
                G->matrix[i][j] = 0;  
        }
    }

    // 填充邻接矩阵
    for (int i = 0; i < elen; i++) {
        int start = getPosition(G, edges[i][0]);
        int end = getPosition(G, edges[i][1]);

        if (start != -1 && end != -1) {
            G->matrix[start][end] = 1;  // 只设置有向边
        }
    }
}

// 打印图的邻接矩阵
void printMGraph(MGraph* G) {
    for (int i = 0; i < G->vexnum; i++) {
        for (int j = 0; j < G->vexnum; j++) {
            if (G->matrix[i][j] == INFINITY)
                printf("%7s", "INF");
            else
                printf("%7d", G->matrix[i][j]);
        }
        printf("\n");
    }
}
void DFS(MGraph* G, int i, int* visited) {
    visited[i] = 1;  // 标记为已访问
    printf("%c ", G->vexs[i]);

    for (int j = 0; j < G->vexnum; j++) {
        if (G->matrix[i][j] == 1 && !visited[j])
            DFS(G, j, visited);
    }
}

void DFSTraverse(MGraph* G) {
    int visited[MAX_VEX] = { 0 };

    for (int i = 0; i < G->vexnum; i++) {
        if (!visited[i])
            DFS(G, i, visited);
    }
}
void BFS(MGraph* G, int start) {
    int visited[MAX_VEX] = { 0 };
    int queue[MAX_VEX];
    int front = 0, rear = 0;

    printf("%c ", G->vexs[start]);
    visited[start] = 1;
    queue[rear++] = start;

    while (front != rear) {
        int i = queue[front++];
        for (int j = 0; j < G->vexnum; j++) {
            if (G->matrix[i][j] == 1 && !visited[j]) {
                printf("%c ", G->vexs[j]);
                visited[j] = 1;
                queue[rear++] = j;
            }
        }
    }
}
int main() {
    MGraph G;
    //createMGraph_wuxiang(&G);
    createMGraph_youxiang(&G);
    printf("Graph's Adjacency Matrix:\n");
    printMGraph(&G); 

    printf("\nBFS:");
    BFS(&G, 0);

    printf("\nDFS:");
    DFSTraverse(&G);
    return 0;
}
