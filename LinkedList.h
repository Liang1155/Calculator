#include <stdlib.h>
#include "./Status.h"
#include<stdio.h>


typedef struct ListNode {
    struct ListNode *pNextNode;
    //pNextNode是指向下一个节点的指针
    void *pData;
    //pData是节点要存储的数据指针
} ListNode;
//ListNode储存的是单个节点的数据

typedef struct {
    ListNode *pHead;
    //pHead是头节点的指针
    int dataSize;
    //dataSize是节点中存储的数据的字节数
    int length;
    //length是节点的数量
} LinkedList;
//LinkedList储存的是整个链表的信息


LinkedList* ListMakeNode(int dataSize);
// 初始化链表,dataSize是每个数据所占的字节数

void ListFreeNode(LinkedList* pNode);
// 释放节点,pNode是节点的名字

Status ListInsertFirstNode(LinkedList* list, void* pData);
// 在链表头部插入元素，list是链表的名字，pData是要插入的元素

Status ListDeleteFirstNode(LinkedList* list);
// 删除链表头部元素，list是链表的名字

Status ListGetFirstNode(LinkedList* list, void* pData);
// 获取链表头部元素，list是链表的名字，pData是用来

int ListIsEmpty(LinkedList* list);
// 判断链表是否为空，list是链表名字

int ListLength(LinkedList* list);
// 获取链表长度，list是链表名字

ListNode* ListConstruct(int sizeOfData);
//构造链表，元素的大小是sizeOfData

void ListDestruct(LinkedList* pList);
//析构链表,pList是要被析构的链表名称

void ListClear(LinkedList* pList);
//清空链表，pList是被清空的链表

Status ListAppend(LinkedList* pList,void* pData);
//在链表后添加新元素，pList是要添加新元素的链表，pData是被添加的新元素

Status ListInsertAfter(LinkedList* pList,ListNode* pNode,void* pData);
//在某个节点添加新元素，pList是被添加节点的链表，pNode是节点，pData是被添加的新元素