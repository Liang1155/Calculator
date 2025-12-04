/* Stack */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define C24_VERSION 202311L//版本问题
#if __STDC_VERSION__ < C24_VERSION
    #define alignas _Alignas
    #define alignof _Alignof
    #define noreturn _Noreturn
    #define nullptr NULL
    typedef enum{false=0,true=1}bool;
#endif

#define STACK_INIT_SIZE 100
//栈初始化的元素个数
#define STACK_INCREMENT 100
//栈每次更新增加的元素个数


#define DEBUG 0
//添加调试模式，1为启用调试，0为关闭调试


typedef enum {ERROR=0,OK=1} Status;
//定义返回类型，Status，如果失败返回ERROR，成功返回OK

typedef struct{
    void* pBase;
    //栈底指针
    void* pTop;
    //栈顶指针
    unsigned int stackSize;
    //栈内元素的个数
    unsigned int elemSize;
    //栈内每个元素所占的字节数
}Stack;
//定义一个栈

Status StackInit(Stack *pStack,unsigned int elemSize);
//初始化栈，pStack是需要进行初始化的栈，elemsize是这个栈的每个元素所占的字节数

void StackFree(Stack* pStack);
//释放栈内存，pStack是需要被释放的栈

#define StackClear(pStack) (pStack)->pTop=(pStack)->pBase
//清空栈，也就是让栈顶指针指向栈底指针


#define StackIsEmpty(pStack) (((pStack)->pTop==\
                               (pStack)->pBase)?true:false)
//判断栈是否为空，如果栈顶指针指向栈底指针，那么栈为空


#define StackLength(pStack) (((char*)(pStack)->pTop-(char*)(pStack)->pBase)/pStack->elemSize)
//获得栈的元素个数，相当于栈顶指针减去栈顶指针除以每个字符所占的字节数


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




Status StackInit(Stack *pStack,unsigned int elemSize){
    //初始化一个栈pStack  ,elemsize是这个栈中每个元素的字节数

    pStack->elemSize=elemSize;
    //给定栈中元素所占的字节数，并赋值给Stack结构体

    pStack->pBase=(void*)malloc(
        //给Stack分配内存
                   STACK_INIT_SIZE*pStack->elemSize);
                   //分配的内存数量是初始化的字符个数乘以每个字符占的字节数

    if(pStack->pBase==NULL){
        return ERROR;
        //如果初始化失败，返回ERROR
    }
    pStack->pTop=pStack->pBase;
    //初始化的时候，栈顶指针等于栈底指针

    pStack->stackSize=STACK_INIT_SIZE;
    //初始的时候栈内元素个数为定义的初始化个数

    return OK;
    //如果栈成功被创建，就返回OK
}

void StackFree(Stack *pStack){
    //释放内存

    free(pStack->pBase);
    //首先释放栈底指针
    pStack->pBase=NULL;
    //将栈底指针指定为空指针
    pStack->pTop=NULL;
    //将栈顶指针指定为空指针
    pStack->stackSize=0;
    //栈内元素个数返回到0

    return;
}

Status StackPeek(Stack *pStack,void *pElem){
    //这个函数获取栈顶元素，并赋值给pElem指针
    if(pStack->pTop==pStack->pBase){
        return ERROR;
        //如果是空栈，返回ERROR
    }
    memcpy(pElem, (char*)(pStack->pTop) - pStack->elemSize, pStack->elemSize);
    //将栈顶元素复制到pElem指针所指向的位置
    return OK;
    //复制成功，返回OK
}


Status StackPush(Stack *pStack,void *pElem){
    //向栈pStack内插入元素，pElem是需要被插入的元素
    int newSize;
    //由于栈的元素个数是不确定的，所以需要扩容；newSize是栈的新的容量
    void *pTemp;
    //创建一个临时指针

    if(StackLength(pStack)>=pStack->stackSize){
        //如果站内元素的个数大于栈所能容纳的元素个数，进行扩容
        newSize=pStack->stackSize+STACK_INCREMENT;
        //每一次都扩大STACK_INCREMENT的元素个数
        pTemp=(void*)realloc(
                               pStack->pBase,
                               newSize*pStack->elemSize);
                               //重新分配内存，并且给pTemp指针
        if(pTemp==NULL){
            return ERROR;
            //如果临时指针为空，返回ERROR
        }
        else{
            pStack->pBase=pTemp;
            //让栈底指针指向temp指针，实现扩容
            pStack->pTop=(char*)pStack->pBase+pStack->stackSize;
            //栈顶指针对应向上移动
            pStack->stackSize=newSize;
            //将栈内元素个数变成newSize
        }
    }
    memcpy(pStack->pTop,pElem,pStack->elemSize);
    //然后将新元素pElem复制到栈顶的位置
    pStack->pTop = (char*)pStack->pTop + pStack->elemSize;
    //栈顶指针向上移动，移到新元素上面的一个位置
    return OK;//if successful,return OK
}

Status StackPop(Stack *pStack){
    //该函数用于弹出栈顶元素,栈为pStack
    if(pStack->pTop==pStack->pBase){
        return ERROR;
        //如果栈为空，就返回ERROR
    }
    else{
        pStack->pTop=(char*)pStack->pTop-pStack->elemSize;
        //要实现弹出功能，只需要将栈顶指针向下移动一位
        return OK;
    }
}