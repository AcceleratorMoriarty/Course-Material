#include <stdio.h>
#include<stdlib.h>

//定义队列
typedef struct {
    int arrive; //到达时间
    int treat;  //需要办理业务的时间
}QNODE;

typedef struct node {
    QNODE data;
    struct node* next;//队列中的元素信息
}LNODE, * LNODEPtr;

// 队头指针和队尾指针
LNODE* front, * rear;

//入队
void EnQueue(QNODE e);
//出队
int DeQueue(QNODE* e);



int main()
{
    int sever_wait = 0, client_wait = 0;//sever_wait业务员等待时间。client_wait为客户等待时间
    int clock = 0;
    int number = 0;//用于积累客户人数
    int exist = 0;//exist用于判断是否有未处理的客户 非0为存在 0为不存在

    QNODE temp, e;

    //建造空队列
    front = rear = (LNODEPtr)malloc(sizeof(LNODE));
    front->next = NULL;//防止野指针

    //txt文件并打入‘10 20 23 10 45 5'
    FILE* fp = fopen("D:\\Desktop\\Data Structure\\exp04\\queue.txt", "r");
    if (fp == NULL) {
        printf("文件打开失败");
        return 0;
    }

    exist = fscanf(fp, "%d %d", &temp.arrive, &temp.treat);

    do {
        if (exist == 2 && front == rear)//有客户&&队列为空
        {
            sever_wait += (temp.arrive - clock);
            clock = temp.arrive;

            //入队
            EnQueue(temp);

            exist = fscanf(fp, "%d %d", &temp.arrive, &temp.treat);
        }

        number++;//积累客户人数+1

        //出队
        DeQueue(&e);

        client_wait += (clock - e.arrive);

        clock += e.treat;//时间推进到客户结束时间

        while (temp.arrive <= clock && exist == 2) //上一个没结束，有到达的客户就入队
        {
            //入队
            EnQueue(temp);
            exist = fscanf(fp, "%d %d", &temp.arrive, &temp.treat);
        }
    } while (exist == 2 || front != rear);//有未处理的客户&&队列不为空
    printf("业务员等待时间为%d\n客户平均等待时间为%f", sever_wait, (float)client_wait / (float)number);

    return 0;
}

//入队
void EnQueue(QNODE e)
{
    LNODEPtr s = (LNODEPtr)malloc(sizeof(LNODE));
    if (!s)
        exit(0);// 存储分配失败退出
    s->data = e;
    s->next = NULL;
    rear->next = s;
    rear = s;		// rear指向s队尾
}


//出队
int DeQueue(QNODE* e)
{
    LNODEPtr p;
    if (front == rear)
        return 0;
    *e = front->next->data; //把删除的队头结点值赋值给e
    p = front->next;				//p暂存删除的队头结点
    front->next = front->next->next;
    if (rear == p)		// 若队头就是队尾，删除后rear指向头结点
        rear = front;
    free(p);
    return 1;
}
