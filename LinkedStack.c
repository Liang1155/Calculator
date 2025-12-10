#include"./LinkedStack.h"


Status StackInit(Stack *pStack,unsigned int elemSize){
    //初始化一个栈pStack  ,elemsize是这个栈中每个元素的字节数

    pStack->elemSize=elemSize;
    //给定栈中元素所占的字节数，并赋值给Stack结构体
    pStack->pList=ListMakeNode(elemSize);
    //初始化链表，给定链表中的数据的字节数
    if(pStack->pList==NULL) return ERROR;

    return OK;
    //如果栈成功被创建，就返回OK
}

void StackFree(Stack *pStack){
    //释放内存
    if(pStack==NULL) return ;
    ListFreeNode(pStack->pList);
    pStack->pList=NULL;
    pStack->elemSize=0;
}

Status StackPeek(Stack *pStack,void *pElem){
    //这个函数获取栈顶元素，并赋值给pElem指针
    if(pStack==NULL||pElem==NULL){
        return ERROR;
        //如果是空栈或者没有传入元素地址，返回ERROR
    }
    return ListGetFirstNode(pStack->pList,pElem);
}


Status StackPush(Stack *pStack,void *pElem){
    //这个函数用于向栈顶插入元素
    //pStack是被插入元素的栈
    //pElem是被插入的元素
    if(pStack==NULL||pElem==NULL) return ERROR;
    return ListInsertFirstNode(pStack->pList,pElem);
}

Status StackPop(Stack *pStack){
    //该函数用于弹出栈顶元素,栈为pStack
    if(pStack==NULL) return ERROR;
    //如果栈是空的，就没法弹出
    return ListDeleteFirstNode(pStack->pList);
}

/*
Status StackTraverse(Stack* pStack,Status (*visit)(void*)){
    if(pStack==NULL||visit==NULL) return ERROR;
    ListNode* pCurrent=pStack->pList->pHead;
    while(pCurrent!=NULL){
        if(visit(pCurrent->pData)==ERROR){
            return ERROR;
        }
        pCurrent=pCurrent->pNextNode;
    }
    return OK;
}
*/