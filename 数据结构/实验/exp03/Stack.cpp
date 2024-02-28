// Stack.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<stdio.h>

using namespace std;



#define StatckSize 100
#define MaxSize 50
#define false 0
#define true 1

typedef char DataType;  //定义数据类型char

//定义顺序栈
typedef struct {
	DataType stack[StatckSize];//存放栈中元素的数组
	int top;//栈顶指针   	
}SeqStack;


//语法检查
int Make_str(char a[]);
int Operator(char a[], int i);
//初始化堆栈
void initstack(SeqStack* S);
//进栈操作
int Push(SeqStack* S, DataType e);
//出栈操作
int Pop(SeqStack* S, DataType* e);
//中缀表达式转换成后缀表达式
void Change_opnd(char str[], char exp[]);
//计算后缀表达式
float Caculate(char a[]);



//判断栈是否为空
int StackEmpty(SeqStack S);
//取栈顶元素
int GetTop(SeqStack S, DataType* e);

typedef struct {
	float data[MaxSize];
	int top;
}OpStack;



//主函数
int main() {
	char a[MaxSize], b[MaxSize];
	float f;
	printf("请输入一个算术表达式：\n");
	gets_s(a);
	//printf("语法判断:%d",Make_str(a));
	if(Make_str(a))
	{   
		printf("中缀表达式：%s \n", a);
		Change_opnd(a, b);
		printf("后缀表达式 %s \n", b);
		f = Caculate(b);
		printf("计算结果： %.2lf \n", f);
	}
	
	return 0;
}
//语法检查
int Make_str(char a[])
{
	int i = 1;
	for (int i = 1; a[i]!= '\0'; i++)
	{
		if (Operator(a, i - 1) == 4 && Operator(a, i) == 5)
		{
			printf("语法错误：不能除以0\n");
			return 0;
		}
		if (Operator(a, i - 1) < 5 && Operator(a, i - 1) > 0 && Operator(a, i) < 5 && Operator(a, i) > 0)
		{
			printf("语法错误：不能连续输入运算符\n");
			return 0;
		}
		if (Operator(a, i - 1) == 0)
		{
			printf("语法错误：存在非法符号\n");
			return 0;
		}
	}
	return 1;
}
int Operator(char a[],int i)
{
	char ch;
	ch = a[i];
	switch (ch) {
	case '+':return 1; break;
	case '-':return 2; break;
	case '*':return 3; break;
	case '/':return 4; break;
	case '0':return 5; break;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':return 6; break;
	case ')':
	case '(':return 7; break;
	default :return 0; break;
	}
}

//顺序栈初始化
void initstack(SeqStack* S) {
	S->top = 0;//把栈顶指针位置为0 
}

//判断栈是否为空
int StackEmpty(SeqStack S) {
	if (S.top == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

//取栈顶元素
int GetTop(SeqStack S, DataType* e) {
	if (S.top <= 0)
	{
		printf("栈已经空\n");
		return 0;
	}
	else {
		*e = S.stack[S.top - 1];
		return 1;
	}
}

//进栈操作
int Push(SeqStack* S, DataType e) {
	if (S->top >= StatckSize)			//进栈前 ，判断是否栈已经满了
	{
		printf("栈已满，进栈失败\n");
		return 0;
	}
	else {
		S->stack[S->top] = e;
		S->top++;
		return 1;
	}
}

//出栈操作
int Pop(SeqStack* S, DataType* e) {
	if (S->top == 0)
	{
		printf("栈已经没有元素，不能出栈");
		return 0;
	}
	else {
		S->top--;
		*e = S->stack[S->top];
		return 1;
	}
}

//中缀表达式转换成后缀表达式
void Change_opnd(char str[], char exp[]) {
	SeqStack S;      //  a           b 
	char ch;
	DataType e;
	int i = 0, j = 0;
	initstack(&S);
	ch = str[i];//获取输入的第一个数或符号 
	i++;
	while (ch != '\0')
	{
		//case  进栈均是 算术符号 
		switch (ch)
		{
		case '(':
			Push(&S, ch);//进栈操作 
			break;
		case ')':         //取栈顶元素    
			while (GetTop(S, &e) && e != '(')
			{
				Pop(&S, &e);
				exp[j] = e;
				j++;
			}
			Pop(&S, &e);//当遇到（时，将符号插入栈中；当遇到）时，将（取出栈 
			break;
		case '+':
		case '-':
			while (!StackEmpty(S) && GetTop(S, &e) && e != '(')
			{
				Pop(&S, &e);
				exp[j] = e;
				j++;
			}
			Push(&S, ch);//将当前运算符进栈
			break;
		case '*':
		case '/':
			while (!StackEmpty(S) && GetTop(S, &e) && e == '/' || e == '*')
			{
				Pop(&S, &e);
				exp[j] = e;
				j++;
			}
			Push(&S, ch);//将当前运算符进栈
			break;
		case ' ':
			break;
		default:
			while (ch >= '0' && ch <= '9')
			{
				exp[j] = ch;  //b 
				j++;
				ch = str[i];  //a 
				i++;
			}
			i--;
			exp[j] = ' ';
			j++;
		}
		ch = str[i];
		i++;
	}
	while (!StackEmpty(S))
	{
		Pop(&S, &e);
		exp[j] = e;
		j++;
	}
	exp[j] = '\0';
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
	if (S.top != -1) {
		result = S.data[S.top];
		S.top--;
		if (S.top == -1)
			return result;
		else
		{
			printf("表达式错误");
			exit(-1);
		}
	}
}

