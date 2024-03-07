#ifndef CHARTREE_H
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

typedef struct charTree
{
    struct charTree *left, *right;
    char *value;
} CHAR_TREE;

int charTreeFindFirstNode(CHAR_TREE *node, CHAR_TREE **returnNode, char *value);
int charTreeFindSubstituteLeaf(CHAR_TREE *node, CHAR_TREE **returnLeaf, CHAR_TREE **returnNode);
int charTreeTravel(CHAR_TREE *node, int travelType);
int charTreeLeafInsert(CHAR_TREE **node, char *value);
int charTreeRemoveFirstNode(CHAR_TREE **node, char *value);

#define CHARTREE_H
#endif