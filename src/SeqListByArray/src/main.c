#include "stdio.h"
#include "SeqList.h"

void PrintList(SequenList *lPtr)
{
    if (!lPtr)
    {
        return;
    }

    printf("初始化后顺序表的元素个数：%d\n", GetSizeSeq(lPtr));
    printf("***********************************\n");
    showSeqList(lPtr);
}

int main(int argc, char *argv[])
{
    SequenList *lPtr = InitSeq(); /// 这样是否可以=>可以的，且使用NULL来判断是否初始化完毕
    if (lPtr)
    {
        /// todo:继续使用这个顺序表
        for (int i = 0; i < 10; i++)
        {
            InsertElemSqList(lPtr, i, i);
        }
        PrintList(lPtr);
        InsertElemSqList(lPtr, 2000, 0);
        PrintList(lPtr);
        //////////////////////////////////////////////////////////////////
        DelElemSqList(lPtr, 1); /// 删除1号: 0
        PrintList(lPtr);
        //////////////////////////////////////////////////////////////////
        // int pos = LocateElemSqList(lPtr, 16);
        int pos = LocateElemSqList(lPtr, 2000);
        if (pos >= 0)
        {
            printf("当前元素位于%d\n", pos);
        }
        else
        {
            printf("没有找到这个元素\n");
        }
        PrintList(lPtr);
        //////////////////////////////////////////////////////////////////
        /// rerverse
        RevseSeqList(lPtr);
        PrintList(lPtr);
    }
    else
    {
        /// todo:提示没有可以使用的空间
    }

    getchar();
    return 0;
}
