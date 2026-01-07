#include "DLinkList.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

/// 测试删除操作
void test_delete_operations()
{
    printf("\n========== 测试删除操作 ==========\n");

    LIST_HEAD(test_list);
    struct test_node nodes[5];

    /// 初始化节点
    for (int i = 0; i < 5; i++)
    {
        nodes[i].id = i;
        snprintf(nodes[i].name, sizeof(nodes[i].name), "Node%d", i);
        INIT_LIST_HEAD(&nodes[i].list);
        list_add_tail(&nodes[i].list, &test_list);
    }

    printf("初始链表: ");
    print_list(&test_list);

    /// 1. 删除中间节点
    list_del(&nodes[2].list);
    printf("1. 删除节点2后: ");
    print_list(&test_list);

    /// 2. 删除头节点
    list_del(&nodes[0].list);
    printf("2. 删除头节点0后: ");
    print_list(&test_list);

    /// 3. 删除尾节点
    list_del(&nodes[4].list);
    printf("3. 删除尾节点4后: ");
    print_list(&test_list);

    /// 4. 使用 list_del_init
    printf("4. 使用list_del_init删除节点1:\n");
    list_del_init(&nodes[1].list);
    printf("   删除后链表: ");
    print_list(&test_list);
    printf("   节点1自身: next=%p, prev=%p\n", nodes[1].list.next, nodes[1].list.prev);
}

/// 测试遍历操作
void test_traversal_operations()
{
    printf("\n========== 测试遍历操作 ==========\n");

    LIST_HEAD(test_list);
    struct test_node nodes[5];

    /// 初始化并添加节点
    for (int i = 0; i < 5; i++)
    {
        nodes[i].id = i;
        snprintf(nodes[i].name, sizeof(nodes[i].name), "Node%d", i);
        INIT_LIST_HEAD(&nodes[i].list);
        list_add_tail(&nodes[i].list, &test_list);
    }

    printf("链表内容:\n");

    /// 1. 使用 list_for_each 遍历
    printf("1. 使用list_for_each遍历:\n");
    struct list_head *pos;
    list_for_each(pos, &test_list)
    {
        struct test_node *node = list_entry(pos, struct test_node, list);
        printf("   节点: id=%d, name=%s\n", node->id, node->name);
    }

    /// 2. 使用 list_for_each_safe 安全遍历并删除
    printf("2. 使用list_for_each_safe遍历并删除偶数节点:\n");
    struct list_head *n;
    list_for_each_safe(pos, n, &test_list)
    {
        struct test_node *node = list_entry(pos, struct test_node, list);
        if (node->id % 2 == 0)
        {
            printf("   删除节点: id=%d\n", node->id);
            list_del(pos);
        }
    }
    printf("   删除后链表: ");
    print_list(&test_list);
}

/// 测试 list_replace
void test_replace_operation()
{
    printf("\n========== 测试替换操作 ==========\n");

    LIST_HEAD(test_list);
    struct test_node nodes[3];
    struct test_node new_node;

    /// 初始化节点
    for (int i = 0; i < 3; i++)
    {
        nodes[i].id = i;
        snprintf(nodes[i].name, sizeof(nodes[i].name), "OldNode%d", i);
        INIT_LIST_HEAD(&nodes[i].list);
        list_add_tail(&nodes[i].list, &test_list);
    }

    printf("初始链表: ");
    print_list(&test_list);

    /// 创建新节点
    new_node.id = 999;
    strcpy(new_node.name, "NewNode");
    INIT_LIST_HEAD(&new_node.list);

    /// 替换中间节点
    list_replace(&nodes[1].list, &new_node.list);
    printf("替换节点1后: ");
    print_list(&test_list);

    /// 验证被替换的节点
    printf("被替换的节点1: next=%p, prev=%p\n", nodes[1].list.next, nodes[1].list.prev);
}

/// 测试 container_of 宏
void test_container_of()
{
    printf("\n========== 测试container_of宏 ==========\n");

    struct test_node node;
    node.id = 100;
    strcpy(node.name, "TestNode");

    /// 获取指向node的指针
    struct list_head *list_ptr = &node.list;

    /// 使用container_of从list_ptr获取完整的node结构
    struct test_node *node_ptr = container_of(list_ptr, struct test_node, list);

    printf("原始节点地址: %p\n", &node);
    printf("list成员地址: %p\n", list_ptr);
    printf("container_of结果: %p\n", node_ptr);
    printf("结果正确性: %s\n", (node_ptr == &node) ? "正确" : "错误");

    if (node_ptr == &node)
    {
        printf("节点内容: id=%d, name=%s\n", node_ptr->id, node_ptr->name);
    }
}


/// 测试空链表
void test_empty_list()
{
    printf("\n========== 测试空链表 ==========\n");

    /// 1. 静态初始化
    LIST_HEAD(empty_list);
    printf("1. 静态初始化空链表: ");
    print_list(&empty_list);
    printf("   list_empty返回: %d\n", list_empty(&empty_list));

    /// 2. 动态初始化
    struct list_head dynamic_list;
    INIT_LIST_HEAD(&dynamic_list);
    printf("2. 动态初始化空链表: ");
    print_list(&dynamic_list);
    printf("   list_empty返回: %d\n", list_empty(&dynamic_list));

    /// 3. 添加后删除
    struct test_node node;
    node.id = 1;
    strcpy(node.name, "TempNode");
    INIT_LIST_HEAD(&node.list);

    list_add(&node.list, &dynamic_list);
    printf("3. 添加节点后: ");
    print_list(&dynamic_list);

    list_del(&node.list);
    printf("4. 删除节点后: ");
    print_list(&dynamic_list);
    printf("   list_empty返回: %d\n", list_empty(&dynamic_list));
}

/// 性能测试：大量节点操作
void test_performance()
{
    printf("\n========== 性能测试 ==========\n");

    const int NODE_COUNT = 10000;
    LIST_HEAD(perf_list);

    printf("创建 %d 个节点...\n", NODE_COUNT);

    /// 动态分配节点
    struct test_node *nodes = malloc(NODE_COUNT * sizeof(struct test_node));
    if (!nodes)
    {
        printf("内存分配失败！\n");
        return;
    }

    /// 添加节点到链表
    for (int i = 0; i < NODE_COUNT; i++)
    {
        nodes[i].id = i;
        snprintf(nodes[i].name, sizeof(nodes[i].name), "PerfNode%d", i);
        INIT_LIST_HEAD(&nodes[i].list);
        list_add_tail(&nodes[i].list, &perf_list);
    }

    printf("链表节点数: ");
    int               count = 0;
    struct list_head *pos;
    list_for_each(pos, &perf_list)
    {
        count++;
    }
    printf("%d\n", count);

    /// 删除所有节点
    printf("删除所有节点...\n");
    struct list_head *n;
    list_for_each_safe(pos, n, &perf_list)
    {
        list_del(pos);
    }

    printf("删除后链表是否为空: %s\n", list_empty(&perf_list) ? "是" : "否");

    free(nodes);
}

int main(int argc, char *argv[])
{
    printf("双向链表测试程序\n");
    printf("================================\n\n");
    test_basic_operations();
    test_delete_operations();
    test_traversal_operations();
    test_replace_operation();
    test_container_of();
    test_empty_list();
    test_performance();

    printf("\n================================\n");
    printf("所有测试完成！\n");
    getchar();
    return 0;
}
