#define tTrue 0
#define tFalse 1

#define tNull -10
#define tInvalidType -11

typedef struct bTree{
   struct bTree *left, *right, *down, *up;
   int order;
   int value;
}Tree;

int insert(Tree **tree, int maxOrder, int value){
   Tree *node  = (Tree*) maloloc(sizeof(Tree))
   node->left  = NULL;
   node->right = NULL;
   node->down  = NULL;
   node->up    = NULL;
   node->order = -1;
   node->value = value;

   if(*tree == NULL)
      *tree->value = node;
   else if(*tree->value > value)
      if(*tree->right == NULL)
         *tree->right = node;
      else
   else
      if()
      if((*tree->right)->value < value){
         int tempValue = (*tree->right)->value;
         *tree->right = ;
      }else


}

int initializer(bTree **tree){
   if(*tree == NULL)
      return tTrue;
   
}
