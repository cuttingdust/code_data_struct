#include "LinkList.h"

///	初始化：给线性表中的相关参数赋值
///	求长度：求线性表中的元素的个数
///	取元素：取给定位置的元素值
///	查元素：查找给定元素值的位置
///	插入元素：在指定的位置插入给定的值
///	删除：删除指定位置的值或者是删除给定的值。
///	遍历元素：从头到尾扫描线性表。

/// 创建带有头节点的链表Init
LinkListNode *InitLinkList(void)
{
    LinkListNode *pHead = NULL;
    pHead               = (LinkListNode *)malloc(sizeof(LinkListNode));
    if (pHead)
    {
        pHead->pNext = NULL;
    }
    return pHead;
}

/// 求长度：求线性表中的元素的个数
int GetSizeLinkList(LinkListNode *pHead)
{
    int n = 0;
    while (pHead->pNext)
    {
        n++;
        pHead = pHead->pNext;
    }
    return n;
}

/// 取元素：取给定位置的元素值
/// 输入链表的头指针，要查找的编号，输出第i个元素的地址
/// pHead：头指针，i 待查节点的序号
LinkListNode *GetLinkListNode(LinkListNode *pHead, int pos)
{
    LinkListNode *p = pHead;
    int           j = 0;
    if (pos == 0)
    {
        return NULL;
    }

    while (j < pos && p->pNext != NULL)
    {
        p = p->pNext;
        j++;
    }

    if (pos == j)
    {
        return p;
    }
    else
    {
        return NULL;
    }
}

/// 查元素：查找给定元素值的位置
/// 找到就返回节点的地址，找不到就返回NULL
LinkListNode *LocateLinkList(LinkListNode *pHead, int objData)
{
    LinkListNode *p = pHead->pNext; /// 跳过头节点
    while (p != NULL && p->data != objData)
    {
        p = p->pNext;
    }
    return p;
}

/// 插入元素：在指定的位置插入给定的值
/// 因为链表这种结构的内存是由程序员管理的，因此它的建立有一定的运算
/// 方法
/// 尾插法建立单链表（将逻辑上的顺序表放入单链表的物理结构当中）
/// arr:传入的顺序表，length：顺序表的长度
LinkListNode *Create_Rear_LkList(ElemType arr[], int length)
{
    LinkListNode *p, *q;
    /// 循环变量，用来遍历全部的顺序表

    LinkListNode *pHead = (LinkListNode *)malloc(sizeof(LinkListNode));

    q = pHead; /// q是获得了当前链表的头节点
    /// q保存了pHead,同时通过q不断前移使得链表串联起来
    for (int i = 0; i < length; i++)
    {
        /// 获得一个单链表的节点，将这个节点加入到有
        /// pHead指向的这个链表当中
        p = (LinkListNode *)malloc(sizeof(LinkListNode));
        /// p获得一个可以加入链表的节点单元
        p->data = arr[i]; /// 将顺序表的内容存入单链表的节点

        q->pNext = p;
        q        = p;
    }
    p->pNext = NULL;
    return pHead;
}

/// 头插法建立单链表
LinkListNode *Create_Front1_LkList(ElemType arr[], int length)
{
    LinkListNode *pHead, *p, *q;
    pHead        = (LinkListNode *)malloc(sizeof(LinkListNode));
    pHead->pNext = NULL;
    q            = pHead->pNext;
    /// 头插的时候，必须逆序遍历顺序表
    for (int i = length - 1; i >= 0; i--)
    {
        p            = (LinkListNode *)malloc(sizeof(LinkListNode));
        p->data      = arr[i];
        p->pNext     = q;            /// 是的新加入的节点传入了上一个节点
        pHead->pNext = p;            /// 头节点指向了当前的新加入节点
        q            = pHead->pNext; /// 让q指向当前的节点
    }
    return pHead;
}

LinkListNode *Create_Front2_LkList(ElemType arr[], int length)
{
    LinkListNode *pHead, *p, *q;
    /// p是新加入节点，q是当前节点
    q = NULL;
    for (int i = length - 1; i >= 0; i--)
    {
        p        = (LinkListNode *)malloc(sizeof(LinkListNode));
        p->data  = arr[i];
        p->pNext = q;
        q        = p;
    }
    pHead        = (LinkListNode *)malloc(sizeof(LinkListNode));
    pHead->pNext = q;
    return pHead;
}

LinkListNode *Create_Front3_LkList(ElemType arr[], int length)
{
    LinkListNode *pHead, *p;
    pHead        = (LinkListNode *)malloc(sizeof(LinkListNode));
    pHead->pNext = NULL;
    for (int i = length - 1; i >= 0; i--)
    {
        p            = (LinkListNode *)malloc(sizeof(LinkListNode));
        p->data      = arr[i];
        p->pNext     = pHead->pNext;
        pHead->pNext = p;
    }
    /// 之所以我们的方法三可以节省方法一中的一个变量q
    /// 原因是：pHead不发生变化，而pHead中的pNext始终作为当前节点的指针
    return pHead;
}

/// 插入元素：在指定的位置插入给定的值
/// 在指定位置之后插入
void Insert_After_LkList(LinkListNode *ptr, ElemType x)
{
    LinkListNode *s;
    s          = (LinkListNode *)malloc(sizeof(LinkListNode));
    s->data    = x;
    s->pNext   = ptr->pNext;
    ptr->pNext = s;
}

/// 指定位置之前插入
void Insert_Before_LkList(LinkListNode *pHead, LinkListNode *ptr, ElemType x)
{
    LinkListNode *s, *qPtr;
    s       = (LinkListNode *)malloc(sizeof(LinkListNode));
    s->data = x;
    qPtr    = pHead;           /// qPtr是用来代替pHead的移动的,ptr是目标节点
    while (qPtr->pNext != ptr) /// 移动到目标的前一个
    {
        qPtr = qPtr->pNext;
    }
    s->pNext    = ptr;
    qPtr->pNext = s;
    /// 因为链表是单向的，虽然我知道当前节点是ptr
    /// 但是在语法层面上，我如果想知道ptr的前继节点只能从head遍历而来
    /// 查到了当前节点的前继，才能使用后插的方法完成节点的加入
}

/// 删除：删除指定位置的值或者是删除给定的值。
/// 情形一：删除指定节点的后继结点
/// 情形二：删除第i个节点，假定头节点i=0
/// 删除返回目标节点的地址，并不涉及到动态空间的回收
/// 在动态回收空间的要求中，应该遵循的原理是谁污染谁治理
/// 在顺序表中的删除就是逻辑上的删除，就是说我们的这个节点不再
/// 存在于当前的顺序表中了

/// 删除节点：Ptr是需要删除的节点，将删除ptr的后续节点 /// 2的后面
LinkListNode *Delete_After_LkList(LinkListNode *ptr)
{
    LinkListNode *fptr;
    /// 假定我们的顺序表A-》B-》C,我们要删除的是A的后续节点B，A-》C
    fptr       = ptr->pNext;  /// ptr是A，所以ptr的next是B，所以fptr是B
    ptr->pNext = fptr->pNext; /// ptr是A，fptr是B，所以fptr的next是C，所以ptr-next就变成C
    return fptr;
}

/// 删除第i个节点
LinkListNode *Delete_i_LkList(LinkListNode *pHead, int i)
{
    LinkListNode *ptr, *qPtr = NULL;
    /// 1的后面
    ptr = GetLinkListNode(pHead, i - 1); /// 找到i的前继节点
    if (ptr != NULL && ptr->pNext != NULL)
    {
        qPtr = Delete_After_LkList(ptr);
    }

    return qPtr;
}

/// 遍历
void ShowLkList(LinkListNode *pHead)
{
    LinkListNode *p = pHead->pNext;
    while (p != NULL)
    {
        printf(" %d", p->data);
        p = p->pNext;
    }
}


LinkListNode *ReverseLkList(LinkListNode *pHead)
{
    if (pHead == NULL || pHead->pNext == NULL)
    {
        return pHead;
    }

    LinkListNode *prev    = NULL;         /// 前驱节点（初始为NULL）
    LinkListNode *current = pHead->pNext; /// 当前节点（从第一个元素开始）
    LinkListNode *next    = NULL;         /// 后继节点（临时存储）

    /// 3. 记录第一个元素，后面需要将其next置为NULL
    LinkListNode *firstElement = current;

    /// 4. 遍历链表，逐个反转指针
    while (current != NULL)
    {
        /// 4.1 保存当前节点的下一个节点
        next = current->pNext;

        /// 4.2 反转当前节点的指针方向
        current->pNext = prev;

        /// 4.3 移动prev和current指针
        prev    = current;
        current = next;

        /// 此时的状态：
        /// prev指向刚刚处理完的节点
        /// current指向下一个待处理的节点
        /// next已经完成了它的使命，在下一循环会重新赋值
    }

    /// 头节点 -> [1] -> 2 -> 3 -> 4 -> NULL
    /// prev: NULL
    /// current: 1
    ///
    /// 第一次循环
    /// 头节点 -> [1] -> NULL    [2] -> 3 -> 4 -> NULL
    ///            ↑             ↑
    ///          prev=1        current=2
    ///
    /// 第二次循环
    /// 头节点    [2] -> 1 -> NULL    [3] -> 4 -> NULL
    ///	           ↑                  ↑
    ///          prev=2            current=3
    /// 注意：现在 2 指向了 1，形成局部反转链 2->1->NULL

    /// 5. 更新头节点的next指针
    /// 此时prev指向原链表的最后一个节点，即反转后的第一个元素
    pHead->pNext = prev;

    /// 6. 将原第一个元素的next置为NULL（现在它是最后一个元素）
    if (firstElement != NULL)
    {
        firstElement->pNext = NULL;
    }

    return pHead;
}
