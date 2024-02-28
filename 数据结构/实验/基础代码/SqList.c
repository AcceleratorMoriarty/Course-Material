#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#define Maxsize 100
typedef int ElemType;

typedef struct {
	ElemType data[Maxsize];
	int length;
}SqList;

void InitList(SqList *L)
{
	int i = 0;
	for (i = 0; i < Maxsize; i++)
		L->data[i] = 0;
	L->length = 0;
}
void InputList(SqList* L)
{
	printf("请输入数据元素个数\n");
	ElemType a,num;
	scanf("%d", &num);
	L->length = num;
	printf("请依次输入数据元素\n");
	for (int i = 0; i < num; i++)
	{
		scanf("%d", &a);
		L->data[i] = a;
	}
}
void PrintfList(SqList L) {
	printf("Length=%d\n",L.length);
	for (int i = 0; i < L.length; i++)
	{
		printf("%d\t", L.data[i]);
	}
}
void DeletElem(SqList *L,ElemType e) {
	int i,deletnum=0;
	for (i = 0; i < L->length; i++)
		if (L->data[i] == e) {	
            for (int j = i; j < L->length-deletnum; j++) {
		        L->data[j] = L->data[j+1];
	        }
	        deletnum++;	
		}
    L->length=L->length-deletnum;
}
int main(void)
{
	SqList L;
	InitList(&L);
	InputList(&L);
	PrintfList(L);
	DeletElem(&L, 5);
	PrintfList(L);
	return 0;
}
