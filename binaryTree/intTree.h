#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

typedef struct numberTree
{
    struct numberTree *left, *right;
    int value;
} INT_TREE;

int intTreeCount(INT_TREE *node, int *count);
int intTreeFind(INT_TREE *node, INT_TREE **returnNode, int value);
int intTreeMajor(INT_TREE *node, int *value);
int intTreeMinor(INT_TREE *node, int *value);
int intTreeTravel(INT_TREE *node, int travelType);
int intTreeLeafInsert(INT_TREE **node, int value);
int intTreeSumTree(INT_TREE *node, int *value);
int intTreeFreeTree(INT_TREE **node);
int intTreeGetChildren(INT_TREE *node, int *returnValue, int value);
int intTreeGetFather(INT_TREE *node, int *returnValue, int value);