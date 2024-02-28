#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#define Maxsize 10
typedef int ElemType;

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;
int a[10]={1,2,3,4,5,6,7,8,9,10};
int InitList(LinkList *L)
{
	*L=(LNode*)malloc(sizeof(LNode));
	if(*L==NULL)
		return -1;
	(*L)->next = NULL;
	return 0;
}
void CreatList(LinkList *L)
{
	InitList(L);
	LNode *rear;
	rear = *L;
	for(int i=0;i<Maxsize;i++)
	{
		LNode *p = (LNode*)malloc(sizeof(LNode));
		p->data =a[i];
		rear->next = p;
		rear=p; 
	}
	rear->next = NULL;
}
void PrintList(LinkList L)
{
	LNode *p;
	p=L->next;
	while (p->next!=NULL)
	{
		/* code */
		printf("%d->",p->data);
		p=p->next;
	}
	printf("NULL\n");	
}
int ListDelete(LinkList *L, ElemType e)
{
	LNode *p = (*L)->next;  //L为头指针，p为头结点，p->next为首元结点
	while(p->next->data != e)
	{
		p = p->next;	
	}	
	if(p->next == NULL)
		return -1;
	p->next = p->next->next;   //删除
	return 0; 
}
int main(void)
{
	LinkList L;
	CreatList(&L);
	PrintList(L);
	ListDelete(&L, 5);
	PrintList(L);
	return 0;
}