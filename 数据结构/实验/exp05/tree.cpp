#include <stdio.h>
#include <stdlib.h>

typedef char DataType;

typedef struct Node {
    DataType data; /* 数据域 */
    struct Node* leftChild; /* 左子树指针 */
    struct Node* rightChild; /* 右子树指针 */
} BiTreeNode; /* 结点的结构体定义 */


/*初始化创建二叉树的头结点*/

// C6011 警告试图解引用一个可能为 NULL 的指针。这通常发生在尝试访问未经初始化或已被释放的内存时
//void Initiate(BiTreeNode** root)
//{
//    *root = (BiTreeNode*)malloc(sizeof(BiTreeNode));
//    (*root)->leftChild = NULL;
//    (*root)->rightChild = NULL;
//}

void Initiate(BiTreeNode** root) {
    *root = (BiTreeNode*)malloc(sizeof(BiTreeNode));
    if (*root == NULL) {
        // 处理内存分配失败的情况
        printf("Error: Memory allocation failed.\n");
        return;
    }
    (*root)->leftChild = NULL;
    (*root)->rightChild = NULL;
}

void Destroy(BiTreeNode** root)
{
    if ((*root) != NULL && (*root)->leftChild != NULL)
        Destroy(&(*root)->leftChild);

    if ((*root) != NULL && (*root)->rightChild != NULL)
        Destroy(&(*root)->rightChild);

    free(*root);
}

/*若当前结点curr非空，在curr的左子树插入元素值为x的新结点*/
/*原curr所指结点的左子树成为新插入结点的左子树*/
/*若插入成功返回新插入结点的指针，否则返回空指针*/
BiTreeNode* InsertLeftNode(BiTreeNode* curr, DataType x)
{
    BiTreeNode* s, * t;
    if (curr == NULL) return NULL;

    t = curr->leftChild;/*保存原curr所指结点的左子树指针*/
    s = (BiTreeNode*)malloc(sizeof(BiTreeNode));
    if (s == NULL) {
        // 处理内存分配失败的情况
        printf("Error: Memory allocation failed.\n");
        return NULL;
    }
    s->data = x;
    s->leftChild = t;/*新插入结点的左子树为原curr的左子树*/
    s->rightChild = NULL;

    curr->leftChild = s;/*新结点成为curr的左子树*/
    return curr->leftChild;/*返回新插入结点的指针*/
}

/*若当前结点curr非空，在curr的右子树插入元素值为x的新结点*/
/*原curr所指结点的右子树成为新插入结点的右子树*/
/*若插入成功返回新插入结点的指针，否则返回空指针*/
BiTreeNode* InsertRightNode(BiTreeNode* curr, DataType x)
{
    BiTreeNode* s, * t;

    if (curr == NULL) return NULL;

    t = curr->rightChild;/*保存原curr所指结点的右子树指针*/
    s = (BiTreeNode*)malloc(sizeof(BiTreeNode));
    if (s == NULL) {
        // 处理内存分配失败的情况
        printf("Error: Memory allocation failed.\n");
        return NULL;
    }
    s->data = x;
    s->rightChild = t;/*新插入结点的右子树为原curr的右子树*/
    s->leftChild = NULL;

    curr->rightChild = s;/*新结点成为curr的右子树*/
    return curr->rightChild;/*返回新插入结点的指针*/
}



/* 前序遍历 */
void PreOrder(BiTreeNode* root, void (*visit)(DataType)) {
    if (root != NULL) {
        visit(root->data);
        PreOrder(root->leftChild, visit);
        PreOrder(root->rightChild, visit);
    }
}

/* 中序遍历 */
void InOrder(BiTreeNode* root, void (*visit)(DataType)) {
    if (root != NULL) {
        InOrder(root->leftChild, visit);
        visit(root->data);
        InOrder(root->rightChild, visit);
    }
}

/* 后序遍历 */
void PostOrder(BiTreeNode* root, void (*visit)(DataType)) {
    if (root != NULL) {
        PostOrder(root->leftChild, visit);
        PostOrder(root->rightChild, visit);
        visit(root->data);
    }
}

/* 查询特定元素 */
int Search(BiTreeNode* root, DataType x) {
    if (root == NULL) {
        return 0; // 未找到
    }
    if (root->data == x) {
        return 1; // 找到
    }
    return Search(root->leftChild, x) | Search(root->rightChild, x);
}

/* 用于打印节点数据的辅助函数 */
void PrintData(DataType data) {
    printf("%c ", data);
}

// 主函数，测试上述功能
int main() {
    BiTreeNode* root = NULL;

    // 初始化根节点
    Initiate(&root);

    root->data = ' ';
    InsertLeftNode(root, 'A');
    InsertLeftNode(root->leftChild, 'B');
    InsertRightNode(root->leftChild, 'C');
    InsertLeftNode(root->leftChild->leftChild, 'D');
    InsertLeftNode(root->leftChild->rightChild, 'E');
    InsertRightNode(root->leftChild->rightChild, 'F');
    InsertRightNode(root->leftChild->leftChild->leftChild, 'G');

    //画图
    //          根
    //         / 
    //        A 
    //       / \
    //      B   C
    //     /   / \
    //    D   E   F
    //     \ 
    //      G
    printf("          根\n");
    printf("         /\n");
    printf("        A\n");
    printf("       / \\\n");
    printf("      B   C\n");
    printf("     /   / \\\n");
    printf("    D   E   F\n");
    printf("     \\\n");
    printf("      G\n");

    // 前序遍历
    printf("PreOrder: ");
    PreOrder(root, PrintData);
    printf("\n");

    // 中序遍历
    printf("InOrder: ");
    InOrder(root, PrintData);
    printf("\n");

    // 后序遍历
    printf("PostOrder: ");
    PostOrder(root, PrintData);
    printf("\n");

    // 搜索特定元素
    char searchItem = 'H';
    if (Search(root, searchItem)) {
        printf("Element '%c' found in the tree.\n", searchItem);
    }
    else {
        printf("Element '%c' not found in the tree.\n", searchItem);
    }

    // 释放树的内存
    Destroy(&root);

    return 0;
}
