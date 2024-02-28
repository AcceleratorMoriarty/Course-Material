#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#define StackSize 100
typedef int ElemType;

typedef struct
{
    ElemType data[StackSize];
    int top;
}SqStack;
typedef struct {
	float data[StackSize];
	int top;
}OpStack;
void InitStack(SqStack *S)
{
    S->top = -1;
}
int StackEmpty(SqStack S)
{
    if(S.top==-1){
       // printf("栈已经空\n");
        return 1;
    }
    else
        return 0;
}
void Push(SqStack *s,ElemType e)
{
    if(s->top==StackSize-1)
        return;
    s->top=s->top+1;
    s->data[s->top]=e;    
}
void Pop(SqStack *s,ElemType *e)
{
    if(s->top==-1)
        return; 
    *e=s->data[s->top];   
    s->top=s->top-1;
}
//取栈顶元素
int GetTop(SqStack S, ElemType *e) {
	if (!StackEmpty(S))
	{
		*e = S.data[S.top];
		return 1;
	}
    return 0;
}
// 后缀表达式
void Tohouzhui(SqStack *S,char input[],char output[])
{
    char p;
    ElemType e;
    int i=0,j=0;
    p = input[i++];
    while(p!='\0')
    {
        switch (p)
        {
        case '(':
            Push(S,p);
            break;
        case ')':         //取栈顶元素    
			while (GetTop(*S, &e) && e != '(')
			{
				Pop(S, &e);
				output[j] = e;
				j++;
			}
			Pop(S, &e);//当遇到（时，将符号插入栈中；当遇到）时，将（取出栈 
			break;
        case '+':
		case '-':
			while (!StackEmpty(*S) && GetTop(*S, &e) && e != '(')
			{
				Pop(S, &e);
				output[j] = e;
				j++;
			}
			Push(S, p);//将当前运算符进栈
			break;
		case '*':
		case '/':
			while (!StackEmpty(*S) && GetTop(*S, &e) && e == '/' || e == '*')
			{
				Pop(S, &e);
				output[j] = e;
				j++;
			}
			Push(S, p);//将当前运算符进栈
			break;
		case ' ':
			break;
		default:
			while (p >= '0' && p <= '9')
			{
				output[j] = p; 
				j++;
				p = input[i];  
				i++;
			}
			i--;
			output[j] = ' ';
			j++;
		}
		p = input[i];
		i++;
	}
	while (!StackEmpty(*S))
	{
		Pop(S, &e);
		output[j] = e;
		j++;
	}
	output[j] = '\0';
}
//计算后缀表达式
float Caculate(char a[]) {
	OpStack S;
	int i = 0, value;
	float x1, x2;
	float result;
	S.top = -1;
	while (a[i] != '\0')
	{
		if (a[i] != ' ' && a[i] >= '0' && a[i] <= '9')
		{
			value = 0;
			while (a[i] != ' ')
			{
				value = 10 * value + a[i] - '0';
				i++;
			}
			S.top++;
			S.data[S.top] = value;
		}
		else
		{
			switch (a[i])
			{
			case '+':
				x1 = S.data[S.top];
				S.top--;
				x2 = S.data[S.top];
				S.top--;
				result = x1 + x2;
				S.top++;
				S.data[S.top] = result;
				break;
			case '-':
				x1 = S.data[S.top];
				S.top--;
				x2 = S.data[S.top];
				S.top--;
				result = x2 - x1;
				S.top++;
				S.data[S.top] = result;
				break;
			case '*':
				x1 = S.data[S.top];
				S.top--;
				x2 = S.data[S.top];
				S.top--;
				result = x1 * x2;
				S.top++;
				S.data[S.top] = result;
				break;
			case '/':
				x1 = S.data[S.top];
				S.top--;
				x2 = S.data[S.top];
				S.top--;
				result = x2 / x1;
				S.top++;
				S.data[S.top] = result;
				break;
			}
			i++;
		}
	}
	// if (S.top != -1) {
	// 	result = S.data[S.top];
	// 	S.top--;
	// 	if (S.top == -1)
	// 		return result;
	// 	else
	// 	{
	// 		printf("表达式错误");
	// 		exit(-1);
	// 	}
	// }
}

int main(void)
{
    float result;
    SqStack S;
    InitStack(&S);
    // SqStack Operate,Number;
    // InitStack(&Operate);
    // InitStack(&Number);
    char Orignal[StackSize]={0};
    char Out[StackSize]={0};
    printf("请输入计算式：");
    scanf("%s",&Orignal);
    printf("%s\n",Orignal);

    // result = Caculate(&Operate,&Number,Orignal); 
    // printf("结果是：%f",result);

    printf("后缀表达式：");
    Tohouzhui(&S,Orignal,Out);
    printf("%s\n",Out);

    result = Caculate(Out);
    printf("结果是：%f",result);
    return 0;
}