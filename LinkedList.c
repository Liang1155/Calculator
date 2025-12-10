#include"./LinkedList.h"
#include<string.h>

LinkedList* ListMakeNode(int dataSize){
    //创建节点
    LinkedList *pNewNode=(LinkedList*)malloc(sizeof(LinkedList));
    //分配内存空间
    if(pNewNode==nullptr){
        return nullptr;
    }
    //分配失败，返回null
    pNewNode->pHead = NULL;
    //头节点初始化为空
    pNewNode->dataSize=dataSize;
    //dataSize为每个数据所占的字节数
    pNewNode->length=0;
    //初始的时候节点长度为0
    return pNewNode;
    //返回生成的节点
}

void ListFreeNode(LinkedList* pNode){
    if(pNode==nullptr){
        return ;
    }
    //本身为空，不操作
    ListNode* pCurrent=pNode->pHead;
    //设定一个pCurrent,指向头节点
    while(pCurrent!=NULL){
        //当头街迪安不为空的时候
        ListNode* pNext=pCurrent->pNextNode;
        //创建pNext指向pCurrent的下一节点
        free(pCurrent->pData);
        //将pCurrent中存储的数据释放
        free(pCurrent);
        //将pCurrent释放(也就是pHead)
        pCurrent=pNext;
        //让pCurrent指向下一个节点即pNext
    }
    free(pNode);
    //将整个链表释放
}

Status ListInsertFirstNode(LinkedList* pList,void* pData){
    //在链表头部插入节点
    if(pList==NULL||pData==NULL) return ERROR;
    //如果链表为空，返回ERROR
    ListNode* pNewNode=(ListNode*)malloc(sizeof(ListNode));
    //创建一个新节点pNewNode,并分配内存
    if(pNewNode==NULL) return ERROR;
    //如果pNewNode为空，创建失败，返回ERROR
    pNewNode->pData=malloc(pList->dataSize);
    //为pNewNode中存储数据的指针分配内存
    if(pNewNode->pData==NULL){
        //分配失败
        free(pNewNode);
        //释放内存
        return ERROR;
    }
    
    memcpy(pNewNode->pData,pData,pList->dataSize);
    //将要插入的数据pData复制给pNewNode中存储数据的pData，长度为dataSize
    pNewNode->pNextNode=pList->pHead;
    //插入的作为头节点，下一个节点为原来的头节点
    pList->pHead=pNewNode;
    //让pHead变成现在的这个pNewNode
    pList->length++;
    //长度增加
    return OK;
}

Status ListDeleteFirstNode(LinkedList* pList){
    //用于删除头节点
    if(pList==NULL||pList->pHead==NULL) return ERROR;
    //如果链表为空，返回ERROR
    ListNode* pTemp=pList->pHead;
    //创建一个临时的pTemp,指向原来的头节点
    pList->pHead=pTemp->pNextNode;
    //头节点指向自己的下一个节点，也就是pTemp的nextnode
    free(pTemp->pData);
    //释放pTemp的data
    free(pTemp);
    //释放ptemp
    pList->length--;
    //链表的长度减小
    return OK;
}

Status ListGetFirstNode(LinkedList* list, void* pData) {
    //用于获取头节点的数值
    //list是需要被获取头节点的链表
    //pdata用于存储头节点的数值
    if (list == NULL || pData == NULL || list->pHead == NULL) return ERROR;
    //如果链表为空，或者数据为空，或者头节点为空，返回ERROR
    memcpy(pData,list->pHead->pData,list->dataSize);
    //将头节点的数据复制给pData
    return OK;
}

int ListIsEmpty(LinkedList* list) {
    //判断链表是否为空
    return (list == NULL || list->pHead == NULL);
    //只要list或者phead为空，就返回空
}

int ListLength(LinkedList* list) {
    //获取list的长度
    return (list == NULL) ? 0 : list->length;
    //如果为空，返回0，否则返回length
}





















//一下功能也属于ListNode，但是在本文件中并没有使用到
/*

ListNode* ListConstruct(int sizeOfData){
    ListNode* pList=(ListNode*)malloc(sizeof(pList));
    if(pList==nullptr){
        return nullptr;
    }
    pList->pNextNode=nullptr;
    return pList;
}

void ListDestruct(LinkedList* pList){
    ListClear(pList);
    free(pList);
    return ;
}

void ListClear(LinkedList* pList){
    ListNode *pCurrentNode,*pNextNode;
    pCurrentNode=pList->pHead;
    while(pCurrentNode!=nullptr){
        pNextNode=pCurrentNode->pNextNode;
        ListFreeNode(pCurrentNode);
        pCurrentNode=pNextNode;
    }
    pList->pHead=nullptr;
    pList->length=0;
}


Status ListAppend(LinkedList* pList,void* pData){
    ListNode *pNewNode,*pTail;
    pNewNode-ListMakeNode(pList,pData);
    if(pNewNode==nullptr){
        return ERROR;
    }
    if(pList->pHead==nullptr){
        pList->pHead=pNewNode;
    }
    else{
        pTail=pList->pHead;
        while(pTail->pNextNode!=nullptr){
            pTail->pNextNode;
        }
        pTail->pNextNode=pNewNode;
    }
    pList->length++;
    return OK;
}


Status ListInsertAfter(LinkedList* pList,ListNode* pNode,void* pData){
    ListNode* pNewNode;
    pNewNode=ListMakeNode(pList,pData);
    if(pNewNode=nullptr){
        return ERROR;
    }
    pNewNode->pNextNode=pNode->pNextNode;
    pNode->pNextNode=pNewNode;
    pList->length++;
    return OK;
}





Status ListDeleteLastNode(LinkedList* pList){
    ListNode *p,*q;
    if(pList->length==0){
        return ERROR;
    }
    q=pList->pHead;
    if(q->pNextNode==nullptr){
        return ListDeleteFirstNode(pList);
    }
    while(q->pNextNode!=nullptr){
        p=q;
        q=q->pNextNode;
    }
    p->pNextNode=nullptr;
    ListFreeNode(q);
    pList->length--;
    return OK;
}

ListNode* ListSearch(LinkedList* pList,void* pKey,bool(*isThisOne)(void*,void*)){
    ListNode* pTemptNode=pList->pHead;
    while(pTemptNode!=nullptr){
        if(isThisOne(pTemptNode->pData,pKey)==true){
            return pTemptNode;
        }
        pTemptNode=pTemptNode->pNextNode;
    }
    return nullptr;
}

Status ListTraverse(LinkedList* pList,Status(*visit)(void*)){
    ListNode* pTemptNode;
    pTemptNode=pList->pHead;
    while(pTemptNode!=nullptr){
        if(visit(pTemptNode->pData)==ERROR){
            return ERROR;
        }
        pTemptNode=pTemptNode->pNextNode;
    }
    return OK;
}

*/