#include "DLinkList.h"

#include <stdio.h>
#include <stdlib.h>


/// 测试数据结构
struct test_node
{
    int              id;
    char             name[32];
    struct list_head list; /// 链表节点
};

/// 打印链表
void print_list(struct list_head *head)
{
    struct test_node *node;

    printf("链表内容: ");
    if (list_empty(head))
    {
        printf("(空)\n");
        return;
    }

    ///  暂时不用 list_for_each_entry 宏
    struct list_head *pos;
    list_for_each(pos, head)
    {
        node = list_entry(pos, struct test_node, list); /// list_entry 也需要修改
        printf("[%d:%s] -> ", node->id, node->name);
    }
    printf("NULL\n");
}

/// 测试基本操作
void test_basic_operations()
{
    printf("========== 测试基本操作 ==========\n");

    /// 1. 创建链表头
    LIST_HEAD(test_list);

    /// 2. 创建几个测试节点
    struct test_node nodes[5];
    for (int i = 0; i < 5; i++)
    {
        nodes[i].id = i;
        snprintf(nodes[i].name, sizeof(nodes[i].name), "Node%d", i);
        INIT_LIST_HEAD(&nodes[i].list);
    }

    /// 3. 测试 list_add (添加到头部)
    printf("1. 使用list_add添加到头部:\n");
    for (int i = 0; i < 3; i++)
    {
        list_add(&nodes[i].list, &test_list);
        printf("   添加节点%d后: ", i);
        print_list(&test_list);
    }

    /// 4. 清空链表
    while (!list_empty(&test_list))
    {
        struct test_node *first =
                list_entry(test_list.next, struct test_node, list); /// 通过test_list.next 找到 这个结构体的首地址
        /// test_list.next -  他在结构体的偏移地址
        list_del(&first->list);
    }
    printf("2. 清空链表后: ");
    print_list(&test_list);

    /// 5. 测试 list_add_tail (添加到尾部)
    printf("3. 使用list_add_tail添加到尾部:\n");
    for (int i = 0; i < 3; i++)
    {
        list_add_tail(&nodes[i].list, &test_list);
        printf("   添加节点%d后: ", i);
        print_list(&test_list);
    }
}

int main(int argc, char *argv[])
{
    printf("双向链表测试程序\n");
    printf("================================\n\n");
    test_basic_operations();
    return 0;
}
