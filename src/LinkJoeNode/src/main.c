#include <stdio.h>
#include <stdlib.h>

/// 问题描述：
/// n个人围成一圈
/// 从第k个人开始报数（从1开始报）
/// 报到第m个数的人出列
/// 然后从下一个人重新开始报数
/// 重复这个过程，直到所有人出列
/// 问题：求最后一个出列的人的编号（幸存者编号）

typedef struct node
{
    int          data;
    struct node *pNext;
} LinkJoeNode;

/// 考虑建立约瑟夫环的循环链表
/// 不带头节点：需要模拟约瑟夫环的工作过程
LinkJoeNode *CreateLkList(int arr[], int length)
{
    LinkJoeNode *head, *p, *q;
    head       = (LinkJoeNode *)malloc(sizeof(LinkJoeNode));
    head->data = arr[0];
    q          = head;

    for (int i = 1; i < length; i++)
    {
        p        = (LinkJoeNode *)malloc(sizeof(LinkJoeNode));
        p->data  = arr[i];
        q->pNext = p;
        q        = p;
    }

    p->pNext = head;
    return p;
}


int main(int argc, char *argv[])
{
    /// 从位置1开始，初始30个人，剩余15个人
    int s = 1;
    int m = 9;  /// 每逢9就出圈
    int k = 15; /// 表明出圈者要有15个人

    int arr[30];
    /// 构造初始的序列
    for (int i = 0; i < 30; i++)
    {
        arr[i] = i + 1; /// 因为我们为每一个变量的序号设为i+1
    }

    LinkJoeNode *p, *q;
    LinkJoeNode *rear = CreateLkList(arr, 30);
    p                 = rear; /// p是遍历指针，只要游戏运行，那么这个p就要移动

    while (k > 0) /// 循环15次，找出15个出圈者
    {
        /// Step1: p向后移动 m-1 次（找"前驱"）
        for (int j = 0; j < m - 1; j++)
        {
            p = p->pNext; /// p移动到要出圈者的前一个位置
        }

        /// Step2: q指向要出圈的人（第m个）
        q = p->pNext;

        /// Step3: 出圈操作
        printf("第%d个元素出圈\n", q->data); /// 输出出圈者
        p->pNext = q->pNext;                 /// 跳过q，直接连接q的下一个
        free(q);                             /// 释放内存
        k--;                                 /// 剩余出圈人数减1
    }


    getchar();
    return 0;
}
