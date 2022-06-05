#include <stdio.h>
#include <stdlib.h>

#define preOrder -1
#define order -2
#define posOrder -3

#define tTrue 0
#define tFalse 1

#define tNull -10
#define tInvalidType -11

typedef struct numberTree{
    struct numberTree *left, *right;
    int value;
} nT;

int nTCount(nT *node, int *count){
    if(node == NULL)
        return tNull;
    *count += 1;
    nTCount(node->left, count);
    nTCount(node->right, count);
    return tTrue;    
}

int nTFind(nT *node, nT **returnNode, int value){
    (*returnNode) = node;
    if(node == NULL)
        return tFalse;
    if((*returnNode)->value == value)
        return tTrue;
    if(node->value < value)
        return nTFind(node->right,returnNode,value);
    else
        return nTFind(node->left,returnNode,value);
}

int nTMajor(nT *node, int *value){
    if(node == NULL)
        return tNull;
    if(node->right != NULL)
        nTMajor(node->right, value);
    else
        *value = node->value;
    return tTrue;
}

int nTMinor(nT *node, int *value){
    if(node == NULL)
        return tNull;
    if(node->left != NULL)
        nTMinor(node->left, value);
    else
        *value = node->value;
    return tTrue;
}

int nTTravel(nT *node, int travelType){
    if(node == NULL)
        return tNull;
    if(travelType > preOrder || travelType < posOrder)
        return tInvalidType;
    if(travelType == preOrder)
        printf("[%d]", node->value);
    nTTravel(node->left, travelType);
    if(travelType == order)
        printf("[%d]", node->value);
    nTTravel(node->right, travelType);
    if(travelType == posOrder)
        printf("[%d]", node->value);
    return tTrue;
}

int nTLeafInsert(nT **node, int value){
    if(node == NULL)
        exit tNull;
    if(*node == NULL){
        *node = (nT *) malloc(sizeof(nT));
        (*node)->value = value;
        (*node)->left = NULL;
        (*node)->right = NULL;
    }else
        if((*node)->value > value){
            if((*node)->left == NULL){
                (*node)->left = (nT *) malloc(sizeof(nT));
                ((*node)->left)->value = value;
                ((*node)->left)->left = NULL;
                ((*node)->left)->right = NULL;
            }else
                nTLeafInsert(&(*node)->left, value);
        }else if((*node)->value < value){
            if((*node)->right == NULL){
                (*node)->right = (nT *) malloc(sizeof(nT));
                ((*node)->right)->value = value;
                ((*node)->right)->left = NULL;
                ((*node)->right)->right = NULL;
            }else
                nTLeafInsert(&(*node)->right, value);
        }else
            return tFalse;
    return tTrue;
}

int nTSumTree(nT *node, int *value){
    if(node == NULL)
        return tNull;
    int newValue = node->value;
    nTSumTree(node->left, &newValue);
    nTSumTree(node->right, value);
    *value += newValue;
    return tTrue;
}

int nTFreeTree(nT **node){
    if(*node == NULL)
        return tNull;
    nTFreeTree(&(*node)->left);
    nTFreeTree(&(*node)->right);
    free(*node);
    node = NULL;
    return tTrue;
}

int nTGetChildren(nT *node, int *returnValue, int value){
    if(node == NULL)
        return tNull;
    nT *nodeAux;
    if(nTFind(node,&nodeAux,value) != tTrue)
        return tFalse;
    if(nodeAux->left != NULL)
        *returnValue = (nodeAux->left)->value;
    else if (nodeAux->right != NULL)
        *returnValue = (nodeAux->right)->value;
    else
        return tFalse;
}

int nTGetFather(nT *node, int *returnValue, int value){
    if(node == NULL)
        return tFalse;
    if((node->left != NULL && (node->left)->value == value) || (node->right != NULL && (node->right)->value == value)){
        *returnValue = node->value;
        return tTrue;
    }
    if(node->value < value)
        return nTGetFather(node->right,returnValue,value);
    else
        return nTGetFather(node->left,returnValue,value);
}