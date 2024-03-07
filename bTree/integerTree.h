#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

typedef struct numberTree
{
    struct numberTree *left, *right;
    int value;
} INT_TREE;

int integerTreeCount(INT_TREE *node, int *count);
int integerTreeFind(INT_TREE *node, INT_TREE **returnNode, int value);
int integerTreeMajor(INT_TREE *node, int *value);
int integerTreeMinor(INT_TREE *node, int *value);
int integerTreeTravel(INT_TREE *node, int travelType);
int integerTreeLeafInsert(INT_TREE **node, int value);
int integerTreeSumTree(INT_TREE *node, int *value);
int integerTreeFreeTree(INT_TREE **node);
int integerTreeGetChildren(INT_TREE *node, int *returnValue, int value);
int integerTreeGetFather(INT_TREE *node, int *returnValue, int value);