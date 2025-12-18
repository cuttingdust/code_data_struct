#include <stdio.h>
#include <stdlib.h>


/// 循环链表节点结构体
/// 每个节点包含一个整型数据和一个指向下一个节点的指针
typedef struct node
{
    int          data;  ///< 节点存储的数据
    struct node *pNext; ///< 指向下一个节点的指针
} LinkCircleListNode;


/// \brief 根据整型数组创建带头节点的循环链表
/// \param arr 输入数组，包含要插入链表的数据
/// \param length 数组长度（即要创建的节点数）
/// \return 循环链表的尾节点地址（注意：不是头节点！）
///
/// 创建后链表结构：head -> arr[0] -> arr[1] -> ... -> arr[length-1] -> head (循环)
///
LinkCircleListNode *Create_Circle_LkList(int arr[], int length)
{
    LinkCircleListNode *head, *p, *q;
    head = (LinkCircleListNode *)malloc(sizeof(LinkCircleListNode));
    q    = head;

    for (int i = 0; i < length; i++)
    {
        /// p指向了临时申请的空间
        p        = (LinkCircleListNode *)malloc(sizeof(LinkCircleListNode));
        p->data  = arr[i];
        q->pNext = p; /// q在串联p的节点
        q        = p; /// q移动到当前的节点
    }
    p->pNext = head; /// 回头
    return p;
}


/// \brief 遍历并打印带头节点的循环链表的所有数据节点
/// \param pRear 循环链表的尾节点指针
///
/// 链表结构：head(哨兵节点) -> 数据1 -> 数据2 -> ... -> 尾节点 -> head(循环)
/// 注意：pRear是尾节点，pRear->pNext 指向的是头节点（head）
void ShowCircleLkList(LinkCircleListNode *pRear)
{
    if (pRear == NULL)
    {
        printf("链表为空（尾节点为NULL）！\n");
        return;
    }

    /// 步骤1：获取头节点（哨兵节点）
    /// pRear->pNext 指向头节点，这是循环链表的特性
    LinkCircleListNode *p = pRear->pNext; /// p 现在指向头节点（head）

    /// 步骤2：跳过哨兵节点，定位到第一个实际的数据节点
    /// 头节点本身不存储有效数据，所以需要再向后移动一次
    p = p->pNext; /// 此时 p 指向第一个真正的数据元素

    /// 步骤3：遍历循环，打印所有数据节点
    /// 循环条件：当 p 没有再次绕回到头节点时继续
    /// pRear->pNext 始终是头节点，所以 p != pRear->pNext 意味着 p 还没绕一圈
    while (p != pRear->pNext) /// 当 p 回到头节点时停止
    {
        printf("%d\n", p->data); /// 打印当前节点的数据
        p = p->pNext;            /// 移动到下一个节点
    }

    /// 循环结束后：p 正好指向头节点，所有数据节点已打印完毕
}

/// 两个循环链表合并
/// 输入为链表a的尾指针，链表b的尾指针
LinkCircleListNode *Connect_Circle_LkList(LinkCircleListNode *ra, LinkCircleListNode *rb)
{
    LinkCircleListNode *p;

    /// 记录a的头节点
    /// ra 是链表A的尾节点，ra->pNext 就是链表A的头节点
    /// 将头节点地址暂存到 p，因为后面需要用到
    p = ra->pNext;

    /// 将b的第一个元素节点链入a的尾部
    /// rb->pNext 是链表B的头节点
    /// rb->pNext->pNext 是链表B的第一个实际数据节点
    /// 这一行：让链表A的尾节点 直接指向 链表B的第一个数据节点
    ra->pNext = rb->pNext->pNext;

    /// 回收空间，意味着b链表的头节点空间不可达，但是rb->pNext依然是有值的
    /// 注意：这里释放的是链表B的【头节点】，不是rb本身！
    /// 因为链表B已经“融入”链表A，不再需要独立的头节点
    free(rb->pNext); /// 回收空间

    /// free(rb->pnext),rb->pnext中的（data和pnext）分量不可用
    /// rb->pNext始终指向的是原b链表的头节点
    /// 将b链表的尾指针指向了a链表的头节点
    /// 这一行：让链表B的尾节点 指向 链表A的头节点（暂存在p中）
    /// 至此，A和B连接成一个大的循环链表
    rb->pNext = p;

    /// 返回新的尾节点（即原链表B的尾节点rb）
    /// 因为现在链表B的尾节点就是整个合并后链表的尾节点
    return rb;
}

int main(int argc, char *argv[])
{
    {
        int                 arr[]  = { 11, 22, 33, 44, 55 };
        LinkCircleListNode *pRrear = Create_Circle_LkList(arr, 5);
        ShowCircleLkList(pRrear);
    }

    {
        int                 a[] = { 1, 3, 5 };
        int                 b[] = { 2, 4, 6 };
        LinkCircleListNode *ra, *rb;
        ra                        = Create_Circle_LkList(a, 3);
        rb                        = Create_Circle_LkList(b, 3);
        LinkCircleListNode *pRear = Connect_Circle_LkList(ra, rb);
        ShowCircleLkList(pRear);
    }

    getchar();
    return 0;
}
