#pragma once

#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;  ///< 假定线性表的元素类型为整型
#define LIST_SIZE 1024 ///< 假定我们的线性表长度是1024
#define TRUE      1
#define FALSE     0
typedef struct
{
    ElemType data[LIST_SIZE];
    int      last; ///< 指向最后一个节点的位置 ******
} SequenList;


///< last的存在的目的：为了在函数调用的时候传递数据方便，因为我们与分配
///< 的空间中，并不是立即存满的


/// \brief   数组顺序表的实现初始化
/// \details 获得一个长度为0的数组
/// \return
SequenList* InitSeq();


/// \brief      求长度：求线性表中的元素的个数
/// \details    获得当前数组顺序表的元素个数，pList:顺序表的起始地址
/// \param pList
/// \return
int GetSizeSeq(SequenList* pList);


/// \brief 取元素：取给定位置的元素值
/// \param pList  目标的顺序表, pos：获取元素的下标 ,e：将元素值放入
/// \param pos
/// \param e
/// \return  元素值
int GetElemSqList(SequenList* pList, int pos, ElemType* e);


/// \brief 查元素：查找给定元素值的位置
/// \details 相同值只去第一个
/// \param pList 传入的数组顺序表
/// \param key 比对的值
/// \return  -1表示没有找到，否则返回带查找元素的角标
int LocateElemSqList(SequenList* pList, ElemType key);


/// \brief 插入元素：在指定的位置插入给定的值
/// \details 插入的位置为k：k: 0 -- n-1
/// \param pList 目标顺序表
/// \param x 待插入的元素
/// \param k 插入的位置
/// \return
int InsertElemSqList(SequenList* pList, ElemType x, int k);


/// \brief  删除：删除指定位置的值或者是删除给定的值。
/// \param pList  目标顺序数组，k表示需要删除的位置
/// \param k
/// \return
int DelElemSqList(SequenList* pList, int k);


/// \brief  遍历元素：从头到尾扫描线性表。
/// \param pList  目标顺序数组
void showSeqList(SequenList* pList);

void RevseSeqList(SequenList* pList);
