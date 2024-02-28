#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int arrive; //到达时间
    int treat;  //需要办理业务的时间
}ElemType;

typedef struct LinkNode {
    ElemType data;
    struct LinkNode* next;//队列中的元素信息
}LinkNode;

typedef struct  {
    LinkNode* front,*rear;//队列中的元素信息
}LinkQueue;

void InitQueue(LinkQueue *Q)
{
    Q->rear=Q->front=(LinkNode*)malloc(sizeof(LinkNode));
    Q->front->next=NULL;
}

//入队
void EnQueue(LinkQueue *Q,ElemType e)
{
    LinkNode *s = (LinkNode*)malloc(sizeof(LinkNode));
    if (!s)
        exit(0);// 存储分配失败退出
    s->data = e;
    s->next = NULL;
    Q->rear->next = s;
    Q->rear = s;		// rear指向s队尾
}

//出队
int DeQueue(LinkQueue *Q,ElemType *e)
{
    if (Q->front == Q->rear)
        return 0;
    LinkNode *P = Q->front->next;\
    *e = P->data;
    Q->front->next=P->next;
    if(Q->rear==P)
    {
        Q->rear=Q->front;
    }
    free(P);
    return 1;
}

int main()
{
    int sever_wait = 0, client_wait = 0;//sever_wait业务员等待时间。client_wait为客户等待时间
    int clock = 0;
    int number = 0;//用于积累客户人数
    int exist = 0;//exist用于判断是否有未处理的客户 非0为存在 0为不存在

    ElemType temp, e;

    //建造空队列
    LinkQueue Q;
    InitQueue(&Q);

    //txt文件并打入‘10 20 23 10 45 5'
    FILE* fp = fopen("E:\\Desktop\\queue.txt", "r");
    if (fp == NULL) {
        printf("文件打开失败");
        return 0;
    }

    exist = fscanf(fp, "%d %d", &temp.arrive, &temp.treat);

    do {
        if (exist == 2 && Q.front == Q.rear)//有客户&&队列为空
        {
            sever_wait += (temp.arrive - clock);
            clock = temp.arrive;
            EnQueue(&Q,temp);
            exist = fscanf(fp, "%d %d", &temp.arrive, &temp.treat);
        }
        number++;//积累客户人数+1
        DeQueue(&Q,&e);
        client_wait += (clock - e.arrive);
        clock += e.treat;//时间推进到客户结束时间
        while (temp.arrive <= clock && exist == 2) //上一个没结束，有到达的客户就入队
        {
            EnQueue(&Q,temp);
            exist = fscanf(fp, "%d %d", &temp.arrive, &temp.treat);
        }
    } while (exist == 2 || Q.front != Q.rear);//有未处理的客户&&队列不为空
    printf("业务员等待时间为%d\n客户平均等待时间为%f", sever_wait, (float)client_wait / (float)number);
    return 0;
}