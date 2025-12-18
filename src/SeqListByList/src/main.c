#include "LinkList.h"

void PrintList(LinkListNode *pHead)
{
    printf("\n********显示当前单链表中的全部元素******\n");
    ShowLkList(pHead);
}

int main(int argc, char *argv[])
{
    ElemType MySeq[] = { 1, 2, 3, 4, 5 };
    // LinkListNode *pHead   = Create_Rear_LkList(MySeq, 5);
    // LinkListNode *pHead = Create_Front1_LkList(MySeq, 5);
    // LinkListNode *pHead = Create_Front2_LkList(MySeq, 5);
    LinkListNode *pHead = Create_Front3_LkList(MySeq, 5);
    PrintList(pHead);

    //////////////////////////////////////////////////////////////////
    LinkListNode *pPos = GetLinkListNode(pHead, 2);
    Insert_After_LkList(pPos, 999);
    PrintList(pHead);

    Insert_Before_LkList(pHead, pPos, 666);
    PrintList(pHead);

    //////////////////////////////////////////////////////////////////
    // Delete_After_LkList(pPos); /// 删除999 2的后面
    Delete_i_LkList(pHead, 2); /// 2的前面
    PrintList(pHead);

    //////////////////////////////////////////////////////////////////
    printf("\nList Size:%d\n", GetSizeLinkList(pHead));

    //////////////////////////////////////////////////////////////////
    ReverseLkList(pHead);
    PrintList(pHead);

    getchar();
    return 0;
}
