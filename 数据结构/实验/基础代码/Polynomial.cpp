#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

typedef struct PLnode {
    float coef; //系数
    int expn;   //指数
    struct PLnode* next;//指针域
}PLnode, * PLinkList;

/*  
    一元多项式的链表表示创建函数
    输入 m 项的系数和指数
    建立一元多项式的有序链表L
*/
void creatpolyn(PLinkList L, int m) {
    int i;
    float coef;
    int expn;
    PLinkList tail, newer;
    //初始化头结点L，其中系数域记录 链表的长度
    L->coef = m;
    L->expn = -1;
    //另 tail 作为遍历链表的指针
    tail = L;
    //创建 m 个新结点并对其初始化，而后链接到 L 上
    for (i = 1; i <= m; i++) {
        newer = (PLinkList)malloc(sizeof(PLnode));
        printf("intput coef & expn:");
        scanf_s("%f", &coef);
        scanf_s("%d", &expn);
        newer->coef = coef;
        newer->expn = expn;
        newer->next = NULL;
        //将新结点链接到 L 上
        tail->next = newer;
        tail = newer;
    }
}
//完成多项式相加运算，即 Lc = La + Lb，并销毁一元多项式 Lb
PLinkList addpolyn(PLinkList La, PLinkList Lb) {
    int x, len;
    float y;
    PLinkList Lc, pa, pb, pc, u;
    Lc = La;
    len = 0;
    pc = Lc;
    //另pa，pb 指向La 、Lb 的首元结点
    pa = La->next;
    pb = Lb->next;
    //通过 pa，pb 遍历链表 La、Lb，只有两指针同时存在时，才需要讨论
    while (pa && pb) {
        x = pa->expn - pb->expn;
        //判断pa 所指结点的指数与pb 所指结点指数的大小关系
        if (x < 0) {
            //如果小，则找去 qa 结点到Lc 上
            pc = pa;
            len++;
            pa = pa->next;
        }
        //如果相等，则判断两结点的系数和是否为0
        else if (x == 0) {
            y = pa->coef + pb->coef;
            if (y != 0.0) {
                //如果不为 0，修改 pa 结点的系数值，同时链接到 LC 上
                pa->coef = y;
                pc = pa;
                len++;
            }
            //如果 y 值为0，则从 pc 的链表中摘除该结点，并释放该结点
            else {
                pc->next = pa->next;
                free(pa);
            }
            //无论是否相等，都执行下列操作
            pa = pc->next;
            u = pb;
            pb = pb->next;
            free(u);
        }
        //如果pb 所指结点指数值小，则摘取pb所指结点到 LC链表上
        else {
            u = pb->next;
            pb->next = pa;
            pc->next = pb;
            pc = pb;
            len++;
            pb = u;
        }
    }
    //将pb剩余结点链接到 Lc 上
    if (pb) {
        pc->next = pb;
    }
    //计算 Lc 的长度
    while (pc) {
        pc = pc->next;
        if (pc) {
            len++;
        }
    }
    //Lc 的头结点中记录Lc 链表的长度
    Lc->coef = len;
    //加和完成的同时，释放Lb 结点
    free(Lb);
    return Lc;
}
//根据链表存储信息。输出结点 q
void printpoly(PLinkList q) {
    if (q->expn == 0) {
        printf("%.0f", q->coef);
    }
    else if (q->expn == 1) {
        if (q->coef == 1) {
            printf("x");
        }
        else if (q->coef == -1) {
            printf("-x");
        }
        else {
            printf("%.0f", q->coef);
            printf("x");
        }
    }
    else if (q->coef == 1) {
        printf("x^%d", q->expn);
    }
    else if (q->coef == -1) {
        printf("-x^%d", q->expn);
    }
    else {
        printf("%.0fx^%d", q->coef, q->expn);
    }
}
//输出一元多项式L
void printpolyn(PLinkList L) {
    int n;
    PLinkList p;
    p = L->next;
    n = 0;
    while (p) {
        n++;
        if (n == 1) {
            printpoly(p);
        }
        else if (p->coef > 0) {
            printf("+");
            printpoly(p);
        }
        else {
            printpoly(p);
        }
        p = p->next;
    }
}
int main() {
    PLinkList La, Lb, Lc;
    int m, n;
    //根据 n 的值，创建链表La
    printf("input n of La:");
    scanf_s("%d", &n);
    La = (PLinkList)malloc(sizeof(PLnode));
    creatpolyn(La, n);
    //根据 m 的值，创建 Lb
    printf("input m of Lb:");
    scanf_s("%d", &m);
    Lb = (PLinkList)malloc(sizeof(PLnode));
    creatpolyn(Lb, m);
    //输出La和Lb
    printf("\nLa=");
    printpolyn(La);
    printf("\nLb=");
    printpolyn(Lb);
    //计算La+Lb，结果保存在 Lc中
    Lc = addpolyn(La, Lb);
    printf("\nLc=");
    printpolyn(Lc);
    return 0;
}