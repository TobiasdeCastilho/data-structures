#include "intTree.h"

int intTreeCount(INT_TREE *node, int *count)
{
  if (node == NULL)
    return tNull;
  *count += 1;
  nTCount(node->left, count);
  nTCount(node->right, count);
  return tTrue;
}

int intTreeFind(INT_TREE *node, INT_TREE **returnNode, int value)
{
  (*returnNode) = node;
  if (node == NULL)
    return tFalse;
  if ((*returnNode)->value == value)
    return tTrue;
  if (node->value < value)
    return intTreeFind(node->right, returnNode, value);
  else
    return intTreeFind(node->left, returnNode, value);
}

int intTreeMajor(INT_TREE *node, int *value)
{
  if (node == NULL)
    return tNull;
  if (node->right != NULL)
    intTreeMajor(node->right, value);
  else
    *value = node->value;
  return tTrue;
}

int intTreeMinor(INT_TREE *node, int *value)
{
  if (node == NULL)
    return tNull;
  if (node->left != NULL)
    intTreeMinor(node->left, value);
  else
    *value = node->value;
  return tTrue;
}

int intTreeTravel(INT_TREE *node, int travelType)
{
  if (node == NULL)
    return tNull;
  if (travelType > preOrder || travelType < posOrder)
    return tInvalidType;
  if (travelType == preOrder)
    printf("[%d]", node->value);
  intTreeTravel(node->left, travelType);
  if (travelType == order)
    printf("[%d]", node->value);
  intTreeTravel(node->right, travelType);
  if (travelType == posOrder)
    printf("[%d]", node->value);
  return tTrue;
}

int intTreeLeafInsert(INT_TREE **node, int value)
{
  if (node == NULL)
    exit tNull;
  if (*node == NULL)
  {
    *node = (INT_TREE *)malloc(sizeof(INT_TREE));
    (*node)->value = value;
    (*node)->left = NULL;
    (*node)->right = NULL;
  }
  else if ((*node)->value > value)
  {
    if ((*node)->left == NULL)
    {
      (*node)->left = (INT_TREE *)malloc(sizeof(INT_TREE));
      ((*node)->left)->value = value;
      ((*node)->left)->left = NULL;
      ((*node)->left)->right = NULL;
    }
    else
      intTreeLeafInsert(&(*node)->left, value);
  }
  else if ((*node)->value < value)
  {
    if ((*node)->right == NULL)
    {
      (*node)->right = (INT_TREE *)malloc(sizeof(INT_TREE));
      ((*node)->right)->value = value;
      ((*node)->right)->left = NULL;
      ((*node)->right)->right = NULL;
    }
    else
      intTreeLeafInsert(&(*node)->right, value);
  }
  else
    return tFalse;
  return tTrue;
}

int intTreeSumTree(INT_TREE *node, int *value)
{
  if (node == NULL)
    return tNull;
  int newValue = node->value;
  intTreeSumTree(node->left, &newValue);
  intTreeSumTree(node->right, value);
  *value += newValue;
  return tTrue;
}

int intTreeFreeTree(INT_TREE **node)
{
  if (*node == NULL)
    return tNull;
  intTreeFreeTree(&(*node)->left);
  intTreeFreeTree(&(*node)->right);
  free(*node);
  node = NULL;
  return tTrue;
}

int intTreeGetChildren(INT_TREE *node, int *returnValue, int value)
{
  if (node == NULL)
    return tNull;
  INT_TREE *nodeAux;
  if (nTFind(node, &nodeAux, value) != tTrue)
    return tFalse;
  if (nodeAux->left != NULL)
    *returnValue = (nodeAux->left)->value;
  else if (nodeAux->right != NULL)
    *returnValue = (nodeAux->right)->value;
  else
    return tFalse;
}

int intTreeGetFather(INT_TREE *node, int *returnValue, int value)
{
  if (node == NULL)
    return tFalse;
  if ((node->left != NULL && (node->left)->value == value) || (node->right != NULL && (node->right)->value == value))
  {
    *returnValue = node->value;
    return tTrue;
  }
  if (node->value < value)
    return intTreeGetFather(node->right, returnValue, value);
  else
    return intTreeGetFather(node->left, returnValue, value);
}