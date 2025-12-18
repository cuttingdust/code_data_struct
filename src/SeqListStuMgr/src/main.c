#include <stdlib.h>
#include <stdio.h>

typedef struct student
{
    int   num;
    float score;
} node;


/// 单班人数上限是50
#define LIST_SIZE 50

#define TRUE  1
#define FALSE 0

/// 定义顺序表的结构
typedef struct
{
    node data[LIST_SIZE];
    int  last; /// 表明最后一个节点的位置
} SeqList;

//////////////////////////////////////////////////////////////////

/// 初始化
SeqList *InitSeq()
{
    SeqList *pList = NULL;
    pList          = (SeqList *)malloc(sizeof(SeqList));
    if (pList != NULL)
    {
        pList->last = 0; /// 初始化成功，且长度为0
    }
    return pList;
    /// 因为在服务器分配中，连续分配大量空间，往往不容易成功
    /// 所以我们经常在内部就进行判断
}

/// 插入元素
int InesrtStuSeq(SeqList *pList, node *pNode, int k)
{
    if (pList->last >= LIST_SIZE - 1)
    {
        return FALSE;
    }

    for (int i = pList->last; i >= k; --i)
    {
        pList->data[i + 1].num   = pList->data[i].num;
        pList->data[i + 1].score = pList->data[i].score;
    }
    pList->data[k].num   = pNode->num;
    pList->data[k].score = pNode->score;
    pList->last++;
    return TRUE;
}

/// 获取班级人数
int GetSize(SeqList *pList)
{
    return pList->last;
}

int DelSeqList(SeqList *pList, int k)
{
    if (k <= 0 || k > pList->last)
    {
        return FALSE;
    }

    if (pList->last == 0)
    {
        return FALSE;
    }

    for (int i = k; i <= pList->last; ++i)
    {
        pList->data[i].num   = pList->data[i + 1].num;
        pList->data[i].score = pList->data[i + 1].score;
    }
    pList->last--;
    return TRUE;
}

/// 实现按学号查找的
void DisplayStu(const SeqList *pList, int stuNo)
{
    for (int i = 0; i < pList->last; ++i)
    {
        if (pList->data[i].num == stuNo)
        {
            printf("该学生的成绩是%f\n", pList->data[i].score);
            return;
        }
    }
    printf("该学生不存在\n");
}

/// 遍历输出全体学生信息
void ShowSeqList(SeqList *pList)
{
    for (int i = 0; i < pList->last; ++i)
    {
        printf("学生的学号是%d,成绩是%f\n", pList->data[i].num, pList->data[i].score);
    }
    printf("\n************\n");
}

int main(int argc, char *argv[])
{
    SeqList *stuList = InitSeq();
    node     stu[2];
    stu[0].num   = 1;
    stu[0].score = 99;
    stu[1].num   = 2;
    stu[1].score = 100;
    if (stuList)
    {
        for (int i = 0; i < 2; i++)
        {
            InesrtStuSeq(stuList, &stu[i], i);
        }
    }
    ShowSeqList(stuList);

    //////////////////////////////////////////////////////////////////
    DisplayStu(stuList, 1);

    //////////////////////////////////////////////////////////////////
    DelSeqList(stuList, 1);
    ShowSeqList(stuList);

    return 0;
}
