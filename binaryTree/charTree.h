#include <stdio.h>
#include <stdlib.h>

#define preOrder -1
#define order -2
#define posOrder -3

#define tTrue 0
#define tFalse 1

#define tNull -10
#define tInvalidType -11

typedef struct charTree{
    struct charTree *left, *right;
    char *value;
} cT;

int cTFindFirstNode(cT *node, cT **returnNode, char *value){
    (*returnNode) = node;
    if(node == NULL)
        return tFalse;
    if(*((*returnNode)->value) == *value)
        return tTrue;
    if(node->value < value)
        return cTFindFirstNode(node->right,returnNode,value);
    else
        return cTFindFirstNode(node->left,returnNode,value);
}

int cTFindSubstituteLeaf(cT *node, cT **returnLeaf, cT **returnNode){
    cT *leftLeaf, *rightLeaf, *leftNode, *rightNode;
    leftLeaf = node->left;
    rightLeaf = node->right;
    leftNode = rightNode = NULL;
    while(leftLeaf->right != NULL){
        leftNode = leftLeaf;
        leftLeaf = leftLeaf->right;
    }
    while(rightLeaf->left != NULL){ 
        rightNode = rightLeaf;
        rightLeaf = rightLeaf->left;
    }
    if(leftNode != NULL){
        *returnLeaf = leftLeaf;
        *returnNode = leftNode;
    }else if(rightNode != NULL){
        *returnLeaf = rightLeaf;
        *returnNode = rightNode;
    }else
        return tFalse;
    return tTrue;
}

int cTTravel(cT *node, int travelType){
    if(node == NULL)
        return tNull;
    if(travelType > preOrder || travelType < posOrder)
        return tInvalidType;
    if(travelType == preOrder)
        printf("[%s]", node->value);
    if(node->left != NULL)
        cTTravel(node->left, travelType);
    if(travelType == order)
        printf("[%s]", node->value);
    if(node->right != NULL)
        cTTravel(node->right, travelType);
    if(travelType == posOrder)
        printf("[%s]", node->value);
    return tTrue;
}

int cTLeafInsert(cT **node, char *value){
    if(node == NULL)
        exit tNull;
    if(*node == NULL){
        *node = (cT *) malloc(sizeof(cT));
        (*node)->value = value;
        (*node)->left = NULL;
        (*node)->right = NULL;
    }else{
        if(*(*node)->value == *value)
            return tFalse;
        int i = 0;
        while(1 == 1){
            if((*node)->value[i] > value[i] || value[i] == '\n' || value[i] == '\0'){
                if((*node)->left == NULL){
                    (*node)->left = (cT *) malloc(sizeof(cT));
                    ((*node)->left)->value = value;
                    ((*node)->left)->left = NULL;
                    ((*node)->left)->right = NULL;
                }else
                    cTLeafInsert(&(*node)->left, value);
                break;
            }else if((*node)->value[i] < value[i] || (*node)->value[i] == '\n' || (*node)->value[i] == '\0'){
                if((*node)->right == NULL){
                    (*node)->right = (cT *) malloc(sizeof(cT));
                    ((*node)->right)->value = value;
                    ((*node)->right)->left = NULL;
                    ((*node)->right)->right = NULL;
                }else
                    cTLeafInsert(&(*node)->right, value);
                break;
            }
            i++;
        }
    }
    return tTrue;
}

int cTRemoveFirstNode(cT **node, char *value){
    if(*node == NULL)
        return tFalse;
    int i = 0;
    int equal;
    while(value[i] != '\0' && (*node)->value[i] != '\0')
        if((equal = (*node)->value[i] - value[i]) != 0)
            break;
        else
            i++;
    equal = (*node)->value[i] - value[i];
    if(equal == 0){
        if((*node)->left != NULL && (*node)->right != NULL){
            cT *leaf, *leafFather;
            cTFindSubstituteLeaf(*node, &leaf, &leafFather);
            if((*node)->value < leaf->value && leaf->left != NULL)
                    leafFather->right = leaf->left;
            else if(leaf->right != NULL)
                leafFather->left = leaf->right;
            leaf->right = (*node)->right;
            leaf->left = (*node)->left;
            free(*node);
            *node = leaf;
            return tTrue;
        }else{
            cT *nodeAux = NULL;
            if((*node)->right != NULL)
                nodeAux = (*node)->right;
            else if((*node)->left != NULL)
                nodeAux = (*node)->left;
            free(*node);
            *node = nodeAux;
            return tTrue;
        }
    }else if(equal < 0){
        if((*node)->right != NULL)
            return cTRemoveFirstNode(&((*node)->right),value);
        else
            return tFalse;
    }else{
        if((*node)->left != NULL)
            return cTRemoveFirstNode(&((*node)->left),value);
        else
            return tFalse;
    }
}