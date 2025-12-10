#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"Status.h"
#include"./LinkedList.h"


#define STACK_INIT_SIZE 100
//栈初始化的元素个数
#define STACK_INCREMENT 100
//栈每次更新增加的元素个数


#define DEBUG 0
//添加调试模式，1为启用调试，0为关闭调试


typedef struct{
    void* pList;
    //指向下一个节点的指针
    unsigned int elemSize;
    //栈内每个元素所占的字节数
}Stack;
//定义一个栈

Status StackInit(Stack *pStack,unsigned int elemSize);
//初始化栈，pStack是需要进行初始化的栈，elemsize是这个栈的每个元素所占的字节数

void StackFree(Stack* pStack);
//释放栈内存，pStack是需要被释放的栈

#define StackClear(pStack) while(!StackIsEmpty(pStack)) StackPop(pStack)
//清空栈，也就是一直弹出栈顶


#define StackIsEmpty(pStack) (ListIsEmpty((pStack)->pList)?true:false)
//判断栈是否为空，通过判断链表指针是否为空


#define StackLength(pStack) (ListLength((pStack)->pList))
//获得栈的元素个数，相当于


Status StackPeek(Stack *pStack,void *pElem);
//这个函数用于获取栈顶元素
//pStack是需要获取元素的那个栈，pElem用于存储栈顶的元素


Status StackPush(Stack *pStack,void *pElem);
//这个函数用于入栈
//pSTack是需要被入的栈，pELem是需要入栈的元素的指针


Status StackPop(Stack *pStack);
//这个函数用于弹出栈顶元素
//pStack是需要被弹出元素的栈


Status StackTraverse(Stack *pStack,
                     Status (*visit)(void*));
/* 这个函数遍历所有栈内的元素
如果visit调用成功返回OK
如果失败返回ERROR
如果发生ERROR,整个函数马上返回ERROR
否则在全部遍历完返回OK
*/