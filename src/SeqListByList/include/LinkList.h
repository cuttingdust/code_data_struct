#include <stdio.h>
#include <stdlib.h>
#define TRUE  1
#define FALSE 0

typedef int ElemType; /// 假定线性表的元素类型为整型

/// 定义节点
typedef struct node
{
    int          data;
    struct node *pNext;
} LinkListNode;


/// \brief 初始化：创建带有头节点的链表Init
/// \return 头节点
LinkListNode *InitLinkList(void);


/// \brief 求长度：求顺序表中的元素的个数
/// \param pHead 是单链表的头节点
/// \return 顺序表的长度
int GetSizeLinkList(LinkListNode *pHead);


/// \brief 取元素：取给定位置的元素值
/// \param pHead 头指针
/// \param pos 待查节点的序号
/// \return 第i个元素的地址
LinkListNode *GetLinkListNode(LinkListNode *pHead, int pos);


/// \brief 查元素：查找给定元素值的位置
/// \param pHead  单链表的头指针
/// \param objData  是需要匹配的元素值
/// \return  节点的地址，找不到就返回NULL
LinkListNode *LocateLinkList(LinkListNode *pHead, int objData);


/// \brief 插入元素：在指定的位置插入给定的值
/// 、details 尾插法建立单链表（将逻辑上的顺序表放入单链表的物理结构当中）
/// \param arr 传入的顺序表
/// \param length 顺序表的长度
/// \return 链表的头指针
LinkListNode *Create_Rear_LkList(ElemType arr[], int length);


/// \brief 头插法建立单链表
/// \param arr 传入的顺序表
/// \param length 顺序表的长度
/// \return  链表的头指针
LinkListNode *Create_Front1_LkList(ElemType arr[], int length);


/// \brief 头插法2
/// \param arr  传入的顺序表
/// \param length 顺序表的长度
/// \return 链表的头指针
LinkListNode *Create_Front2_LkList(ElemType arr[], int length);


/// \brief 头插法建立
/// \param arr 传入的顺序表
/// \param length  顺序表的长度
/// \return
LinkListNode *Create_Front3_LkList(ElemType arr[], int length);

/// \brief 插入元素：在指定的位置插入给定的值
/// \param ptr 带插入的元素位置, 将在ptr的后继结点中插入
/// \param x 插入的值
void Insert_After_LkList(LinkListNode *ptr, ElemType x);


/// \brief 插入元素：在指定的位置之前插入给定的值
/// \param pHead  链表的头指针
/// \param ptr  带插入的元素位置
/// \param x  插入的值
void Insert_Before_LkList(LinkListNode *pHead, LinkListNode *ptr, ElemType x);


/// \brief 删除节点：Ptr是需要删除的节点，将删除ptr的后续节点
/// \param ptr  需要删除的节点
/// \return  带删除的节点位置
LinkListNode *Delete_After_LkList(LinkListNode *ptr);


/// \brief 删除第i个节点
/// \param pHead
/// \param i
/// \return 带删除的节点位置
LinkListNode *Delete_i_LkList(LinkListNode *pHead, int i);

void ShowLkList(LinkListNode *pHead);
