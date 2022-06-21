#include <stdlib.h>

#ifndef defined_stackDataType
typedef struct stackDataDefinition {
    int value;
} stackDataType;
#endif

typedef struct stackNode {
    stackDataType value;
    int length;
    struct stackNode *prior;
} stack;

int stackInitialize(stack **node);
int stackPeek(stack *node, stackDataType *returnValue);
int stackPop(stack **node, stackDataType *returnValue);
int stackRemove(stack **node);
int stackPush(stack **node, stackDataType value);

int stackInitialize(stack **node){
    if(*node == NULL)
        return 0;
    stackRemove(node);
    return stackInitialize(node);
}

int stackPeek(stack *node, stackDataType *returnValue){
    if(node == NULL)
        return 1;
    *returnValue = node->value;
    return 0;
}

int stackPop(stack **node, stackDataType *returnValue){
    if(*node == NULL)
        return 1;
    stackPeek(*node, returnValue);
    stackRemove(node);
    return 0;
}

int stackRemove(stack **node){
    if(*node == NULL)
        return 1;
    stack *newTop = (*node)->prior;
    free(*node);
    *node = newTop;
    return 0;
}

int stackPush(stack **node, stackDataType value){
    stack *newNode = (stack *)malloc(sizeof(stack));
    newNode->value = value;
    newNode->prior = NULL;
    if(*node == NULL){
        newNode->length = 1;
        *node = newNode;
        return 0;
    }
    stack *top = *node;
    newNode->prior = top;
    newNode->length = top->length + 1;
    *node = newNode;
    return 0;
}