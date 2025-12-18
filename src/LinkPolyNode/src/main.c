#include <stdlib.h>
#include <stdio.h>
/**
 * 多项式链表节点结构体
 * 用于存储多项式的每一项：系数(coef)和指数(exp)
 */
typedef struct Polynode
{
    int              coef;  ///< 系数
    int              exp;   ///< 指数（通常按降幂或升幂排列）
    struct Polynode* pNext; ///< 指向下一个节点的指针
} LinkPolyNode;

/// \brief 在多项式链表末尾添加一个新节点
/// \param[in] coef 系数
/// \param[in] exp  指数
/// \param[in,out] pc 当前链表的尾节点指针（插入位置）
/// \return 新分配节点的地址
LinkPolyNode* attach(int coef, int exp, LinkPolyNode* pc)
{
    /// 1. 为新节点动态分配内存
    LinkPolyNode* p = (LinkPolyNode*)malloc(sizeof(LinkPolyNode));

    /// 2. 设置新节点的数据域
    p->coef = coef;
    p->exp  = exp;

    /// 3. 将新节点链接到链表末尾
    /// pc是当前尾节点，将其pNext指向新节点
    pc->pNext = p;

    /// 4. 返回新节点的地址，使其成为新的尾节点
    return p;
}


/// \brief  将两个有序（按指数排序）多项式链表相加
/// \param headA 多项式A的哨兵头节点（头节点不存数据）
/// \param headB 多项式B的哨兵头节点
/// \return 结果多项式C的哨兵头节点地址
LinkPolyNode* MergePoly(LinkPolyNode* headA, LinkPolyNode* headB)
{
    LinkPolyNode* headC; /// 结果多项式C的头节点（哨兵节点）
    LinkPolyNode *pa, *pb, *pc, *p;

    /// 跳过哨兵头节点，从第一个有效数据节点开始
    pa = headA->pNext;
    pb = headB->pNext;

    /// 为结果多项式C创建哨兵头节点（不存储实际数据）
    headC = (LinkPolyNode*)malloc(sizeof(LinkPolyNode));
    pc    = headC; /// pc始终指向结果链表的当前尾节点

    /// 阶段1：合并pa和pb都存在的部分（类似于合并两个有序链表）
    while (pa != NULL && pb != NULL)
    {
        /// 情况1：指数相同，系数相加
        if (pa->exp == pb->exp)
        {
            const int sum_coef = pa->coef + pb->coef;
            /// 只有系数和非零时才创建新节点（消去为零的项）
            if (sum_coef != 0)
            {
                /// 将结果项添加到C链表末尾
                pc = attach(sum_coef, pa->exp, pc);
            }

            /// A和B的当前项都已处理，指针后移
            pa = pa->pNext;
            pb = pb->pNext;
            continue;
        }

        /// 情况2：A当前项指数 < B当前项指数
        /// 将指数较小的项（A的当前项）加入结果，保持结果有序
        if (pa->exp < pb->exp)
        {
            p  = pa;        /// 临时保存要处理的节点
            pa = pa->pNext; /// A指针后移
        }
        ///  情况3：A当前项指数 > B当前项指数
        else
        {
            p  = pb;        /// 临时保存要处理的节点
            pb = pb->pNext; /// B指针后移
        }
        /// 将指数较小的项复制到结果链表中
        pc = attach(p->coef, p->exp, pc);
    }

    /// 阶段2：处理剩余部分（pa或pb中还有未处理的节点）
    /// 确定哪个链表还有剩余节点
    p = pa;
    if (pa == NULL)
    {
        p = pb; /// 如果A已处理完，则处理B的剩余部分
    }

    /// 将剩余节点全部复制到结果链表
    while (p != NULL)
    {
        pc = attach(p->coef, p->exp, pc);
        p  = p->pNext;
    }

    /// 非常重要：将结果链表的最后一个节点的next指针置为NULL
    pc->pNext = NULL;

    return headC;
}

/// 设计显示的辅助函数
void ShowList(LinkPolyNode* pHead)
{
    LinkPolyNode* p;
    p = pHead->pNext;
    while (p != NULL)
    {
        /// 美化设计显示的内容:设计常数项的显示
        if (p->exp == 0)
        {
            printf("%d", p->coef);
            p = p->pNext;
            continue;
        }

        /// 设计一次项的显示
        if (p->exp == 1)
        {
            //printf("x")
            if (p->coef > 0)
            {
                printf("+%dx", p->coef);
            }
            else
            {
                printf("%dx", p->coef);
            }
            p = p->pNext;
            continue;
        }

        /// 设计高此项的显示
        if (p->coef > 0)
        {
            printf("+%dx^%d", p->coef, p->exp);
        }
        else
        {
            printf("%dx^%d", p->coef, p->exp);
        }

        p = p->pNext;
    }
}


int main(int argc, char* argv[])
{
    /// PolyA: 1+2x+3x^2
    /// PolyB: 3x+x^4

    LinkPolyNode HeadA, A1, A2, A3;
    LinkPolyNode HeadB, B1, B2;

    HeadA.pNext = &A1;
    A1.pNext    = &A2;
    A2.pNext    = &A3;
    A3.pNext    = NULL;

    HeadB.pNext = &B1;
    B1.pNext    = &B2;
    B2.pNext    = NULL;

    /// 建立多项式:PolyA: 1+2x+3x^2
    A1.coef = 1;
    A1.exp  = 0;
    A2.coef = 2;
    A2.exp  = 1;
    A3.coef = 3;
    A3.exp  = 2;

    /// PolyB: 3x+x^4
    B1.coef = 3;
    B1.exp  = 1;
    B2.coef = 1;
    B2.exp  = 4;

    printf("\n*********PolyA********\n");
    ShowList(&HeadA);
    printf("\n*********PolyB********\n");
    ShowList(&HeadB);
    
    LinkPolyNode* pPloyC;
    pPloyC = MergePoly(&HeadA, &HeadB);
    printf("\n*********PolyC********\n");
    ShowList(pPloyC);


    getchar();
    return 0;
}
