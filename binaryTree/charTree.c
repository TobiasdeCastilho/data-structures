#include "charTree.h"

int charTreeTFindFirstNode(CHAR_TREE *node, CHAR_TREE **returnNode, char *value)
{
  (*returnNode) = node;
  if (node == NULL)
    return tFalse;
  if (*((*returnNode)->value) == *value)
    return tTrue;
  if (node->value < value)
    return charTreeTFindFirstNode(node->right, returnNode, value);
  else
    return charTreeTFindFirstNode(node->left, returnNode, value);
}

int charTreeFindSubstituteLeaf(CHAR_TREE *node, CHAR_TREE **returnLeaf, CHAR_TREE **returnNode)
{
  CHAR_TREE *leftLeaf, *rightLeaf, *leftNode, *rightNode;
  leftLeaf = node->left;
  rightLeaf = node->right;
  leftNode = rightNode = NULL;
  while (leftLeaf->right != NULL)
  {
    leftNode = leftLeaf;
    leftLeaf = leftLeaf->right;
  }
  while (rightLeaf->left != NULL)
  {
    rightNode = rightLeaf;
    rightLeaf = rightLeaf->left;
  }
  if (leftNode != NULL)
  {
    *returnLeaf = leftLeaf;
    *returnNode = leftNode;
  }
  else if (rightNode != NULL)
  {
    *returnLeaf = rightLeaf;
    *returnNode = rightNode;
  }
  else
    return tFalse;
  return tTrue;
}

int charTreeTTravel(CHAR_TREE *node, int travelType)
{
  if (node == NULL)
    return tNull;
  if (travelType > preOrder || travelType < posOrder)
    return tInvalidType;
  if (travelType == preOrder)
    printf("[%s]", node->value);
  if (node->left != NULL)
    charTreeTTravel(node->left, travelType);
  if (travelType == order)
    printf("[%s]", node->value);
  if (node->right != NULL)
    charTreeTTravel(node->right, travelType);
  if (travelType == posOrder)
    printf("[%s]", node->value);
  return tTrue;
}

int charTreeLeafInsert(CHAR_TREE **node, char *value)
{
  if (node == NULL)
    exit tNull;
  if (*node == NULL)
  {
    *node = (CHAR_TREE *)malloc(sizeof(CHAR_TREE));
    (*node)->value = value;
    (*node)->left = NULL;
    (*node)->right = NULL;
  }
  else
  {
    if (*(*node)->value == *value)
      return tFalse;
    int i = 0;
    while (1 == 1)
    {
      if ((*node)->value[i] > value[i] || value[i] == '\n' || value[i] == '\0')
      {
        if ((*node)->left == NULL)
        {
          (*node)->left = (CHAR_TREE *)malloc(sizeof(CHAR_TREE));
          ((*node)->left)->value = value;
          ((*node)->left)->left = NULL;
          ((*node)->left)->right = NULL;
        }
        else
          charTreeLeafInsert(&(*node)->left, value);
        break;
      }
      else if ((*node)->value[i] < value[i] || (*node)->value[i] == '\n' || (*node)->value[i] == '\0')
      {
        if ((*node)->right == NULL)
        {
          (*node)->right = (CHAR_TREE *)malloc(sizeof(CHAR_TREE));
          ((*node)->right)->value = value;
          ((*node)->right)->left = NULL;
          ((*node)->right)->right = NULL;
        }
        else
          charTreeLeafInsert(&(*node)->right, value);
        break;
      }
      i++;
    }
  }
  return tTrue;
}

int charTreeRemoveFirstNode(CHAR_TREE **node, char *value)
{
  if (*node == NULL)
    return tFalse;
  int i = 0;
  int equal;
  while (value[i] != '\0' && (*node)->value[i] != '\0')
    if ((equal = (*node)->value[i] - value[i]) != 0)
      break;
    else
      i++;
  equal = (*node)->value[i] - value[i];
  if (equal == 0)
  {
    if ((*node)->left != NULL && (*node)->right != NULL)
    {
      CHAR_TREE *leaf, *leafFather;
      charTreeFindSubstituteLeaf(*node, &leaf, &leafFather);
      if ((*node)->value < leaf->value)
        leafFather->right = leaf->left;
      else if (leaf->right != NULL)
        leafFather->left = leaf->right;
      leaf->right = (*node)->right;
      leaf->left = (*node)->left;
      free(*node);
      *node = leaf;
      return tTrue;
    }
    else
    {
      CHAR_TREE *nodeAux = NULL;
      if ((*node)->right != NULL)
        nodeAux = (*node)->right;
      else if ((*node)->left != NULL)
        nodeAux = (*node)->left;
      free(*node);
      *node = nodeAux;
      return tTrue;
    }
  }
  else if (equal < 0)
  {
    if ((*node)->right != NULL)
      return charTreeRemoveFirstNode(&((*node)->right), value);
    else
      return tFalse;
  }
  else
  {
    if ((*node)->left != NULL)
      return charTreeRemoveFirstNode(&((*node)->left), value);
    else
      return tFalse;
  }
}
