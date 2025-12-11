#include <stdio.h>
#include <stdlib.h>

/// 定义节点
typedef struct node
{
    int          data;
    struct node *pNext;
} LinkListNode;


int main(int argc, char *argv[])
{
    {
        LinkListNode x, y, *p;
        p       = &x;
        x.data  = 100;
        x.pNext = NULL;

        y.data  = 200;
        y.pNext = NULL;

        x.pNext = &y;

        LinkListNode *head    = &x;
        LinkListNode *current = head;
        while (current != NULL)
        {
            printf(" %d ", current->data);
            current = current->pNext;
        }
        printf("\n");
    }

    {
        LinkListNode *xPtr = NULL, *yPtr = NULL, *p = NULL;
        xPtr = (LinkListNode *)malloc(sizeof(LinkListNode));
        if (xPtr)
        {
            xPtr->pNext = NULL;
            xPtr->data  = 100;
        }

        yPtr = (LinkListNode *)malloc(sizeof(LinkListNode));
        if (yPtr)
        {
            yPtr->data  = 200;
            yPtr->pNext = NULL;
        }
        xPtr->pNext = yPtr;

        LinkListNode *head    = xPtr;
        LinkListNode *current = head;
        while (current != NULL)
        {
            printf(" %d ", current->data);
            current = current->pNext;
        }
        printf("\n");
    }

    getchar();
    return 0;
}
