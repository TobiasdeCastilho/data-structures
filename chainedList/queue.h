#include <stdlib.h>

#ifndef defined_queueDataType
typedef struct queueDataDefinition {
    int value;
} queueDataType;
#endif

typedef struct queueNode {
    queueDataType value;
    int length;
    struct queueNode *next, *last;
} queue;

int queueInitialize(queue *node);
int queuePeek(queue *node, queueDataType *returnValue);
int queuePop(queue **node, queueDataType *returnValue);
int queueRemove(queue **node);
int queuePush(queue **node, queueDataType value);

int queueInitialize(queue *node){
    if(node == NULL)
        return 0;
    queueRemove(&node);
    return queueInitialize(node);
}

int queuePeek(queue *node, queueDataType *returnValue){
    if(node == NULL)
        return 1;
    *returnValue = node->value;
    return 0;
}

int queuePop(queue **node, queueDataType *returnValue){
    if(*node == NULL)
        return 1;
    queuePeek(*node, returnValue);
    queueRemove(node);
    return 0;
}

int queueRemove(queue **node){
    if(*node == NULL)
        return 1;
    queue *newFirst = NULL;
    if((*node)->next != NULL){
        (*node)->next;
        newFirst->length = (*node)->length - 1;
        newFirst->last = (*node)->last;
        free(*node);
    }
    *node = newFirst;
    return 0;
}

int queuePush(queue **node, queueDataType value){
    queue *newNode = (queue *)malloc(sizeof(queue));
    newNode->value = value;
    newNode->next = NULL;
    newNode->last = NULL;
    if(*node == NULL){
        newNode->length = 1;
        *node = newNode;
        return 0;
    }
    queue *first = *node;
    first->length += 1;
    if(first->last != NULL)
        (first->last)->next = newNode;
    else
        first->next = newNode;
    first->last = newNode;
    return 0;
}