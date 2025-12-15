#include "SeqList.h"

///	初始化：给线性表中的相关参数赋值
///	求长度：求线性表中的元素的个数
///	取元素：取给定位置的元素值
///	查元素：查找给定元素值的位置
///	插入元素：在指定的位置插入给定的值
///	删除：删除指定位置的值或者是删除给定的值。
///	遍历元素：从头到尾扫描线性表。


/// 实现初始化
SequenList *InitSeq()
{
    SequenList *pList = NULL;
    pList             = (SequenList *)malloc(sizeof(SequenList));
    if (pList != NULL)
        pList->last = 0; /// 初始化成功，且长度为0

    return pList;
}

/// SequenList seqenList;
/// SequenList *seqenList;
/// 前者分配空间了，而后者没有空间

/// 求长度：求线性表中的元素的个数
int GetSizeSeq(SequenList *pList)
{
    return pList->last;
}

/// 取元素：取给定位置的元素值
/// pList:目标的顺序表, pos：获取元素的下标 ,e：将元素值放入
int GetElemSqList(SequenList *pList, int pos, ElemType *e)
{
    if (pos < 0 || pos > pList->last)
    {
        return FALSE;
    }
    if (pList->last <= 0)
    {
        return FALSE;
    }
    /// 说明此时pos在0 -- n之间
    *e = pList->data[pos];
    return TRUE;
}

///	查元素：查找给定元素值的位置
/// 相同值只去第一个
/// 返回值：-1表示没有找到，否则返回带查找元素的角标
/// pList：传入的数组顺序表，Key比对的值
int LocateElemSqList(SequenList *pList, ElemType key)
{
    for (int i = 0; i < pList->last; i++)
    {
        if (pList->data[i] == key)
        {
            return i;
        }
    }
    return -1;
}

///	插入元素：在指定的位置插入给定的值
/// 插入的位置为k：k: 0 -- n-1
/// 顺序表：不满
/// pList:目标顺序表，x待插入的元素，k插入的位置
int InsertElemSqList(SequenList *pList, ElemType x, int k)
{
    /// 顺序表尚未填满
    if (pList->last >= LIST_SIZE - 1)
    {
        return FALSE;
    }
    /// 表明K是有效位置
    if (k < 0 || k > (pList->last + 1))
    {
        return FALSE;
    }
    for (int j = pList->last; j >= k; j--)
    {
        pList->data[j + 1] = pList->data[j];
    }
    pList->data[k] = x;
    pList->last    = pList->last + 1;
    return TRUE;
}

/// 删除：删除指定位置的值或者是删除给定的值。
/// pList:目标顺序数组，k表示需要删除的位置
int DelElemSqList(SequenList *pList, int k)
{
    if ((k >= 0 && k <= pList->last) && (pList->last != 0))
    {
        for (int j = k; j <= pList->last; j++)
        {
            pList->data[j] = pList->data[j + 1];
        }
        pList->last--;
        return TRUE;
    }
    return FALSE;
}

void showSeqList(SequenList *pList)
{
    for (int i = 0; i < pList->last; i++)
    {
        printf(" %d", pList->data[i]);
    }
    printf("\n");
}

void RevseSeqList(SequenList *pList)
{
    if (pList->last == 0 || pList->last == 1)
    {
        return;
    }

    int nCount = pList->last / 2;
    for (int i = 0; i < nCount; i++)
    {
        int temp                         = pList->data[i];
        pList->data[i]                   = pList->data[pList->last - 1 - i];
        pList->data[pList->last - 1 - i] = temp;
    }
}
