#ifdef ___dm__dmMatrixNode_Functions
static int __dmCL_clear(dmCL **node){
    while(__dmCL_freeNode(node) == dmTrue){}
    return dmTrue;
}
static int __dmCL_freeNode(dmCL **node){
    if(node == NULL)
        return dmNull;
    dmCL *nodeResult = NULL;
    if((*node)->next != NULL){
        ((*node)->next)->prior = (*node)->prior;
        nodeResult = (*node)->next;
    }
    if((*node)->prior != NULL){
        ((*node)->prior)->next = (*node)->next;
        nodeResult = (*node)->prior;
    }
    free(*node);
    *node = nodeResult;
    return dmTrue;
}
static int __dmCL_initializer(dmCL **node){
    int result = dmTrue;
    if(node != NULL)
        result = __dmCL_clear(node);
    *node = NULL;
    return result;
}
static int __dmCL_insert(dmCL **node, int position){
    dmCL *newNode = (dmCL *) malloc(sizeof(dmCL));
    if((*node) != NULL){
        __dmCL_goToNearestPos(node,position);
        if((*node)->position == position)
            return dmFalse;
        __dmCL_prepareNode(&newNode);
        if((*node)->position < position){
            newNode->next = (*node)->next;
            if(newNode->next != NULL)
                ((*node)->next)->prior = newNode;
            (*node)->next = newNode;
            newNode->prior = (*node);
        }else{
            newNode->prior = (*node)->prior;
            if(newNode->prior != NULL)
                ((*node)->prior)->next = newNode;
            (*node)->prior = newNode;
            newNode->next = (*node);
        }
    }else
        __dmCL_prepareNode(&newNode);
    newNode->position = position;
    *node = newNode;
    return dmTrue;
}
static int __dmCL_next(dmCL **node){
    if(node == NULL)
        return dmNull;
    dmCL *initialNode = (*node);
    *node = (*node)->next != NULL ? (*node)->next : (*node);
    return (*node != initialNode ? dmTrue : dmEON);
}
static int __dmCL_prepareNode(dmCL **node){
    (*node)->nodeValue = NULL;
    (*node)->prior = NULL;
    (*node)->next = NULL;
    (*node)->position = 0;
    return dmTrue;
}
static int __dmCL_prior(dmCL **node){
    if(node == NULL)
        return dmNull;
    dmCL *initialNode = (*node);
    *node = (*node)->prior != NULL ? (*node)->prior : (*node);
    return (*node != initialNode ? dmTrue : dmBON);
}
static int __dmCL_goToNearestNode(dmCL **node, int position, int axys){
    int firstPosition = (axys == dmAxysX ? ((*node)->nodeFirst)->posX : ((*node)->nodeFirst)->posY);
    int currentPosition = (axys == dmAxysX ? ((*node)->nodeValue)->posX : ((*node)->nodeValue)->posY);
    int lastPosition = (axys == dmAxysX ? ((*node)->nodeLast)->posX : ((*node)->nodeLast)->posY);
    float diference = (currentPosition-firstPosition)/2;
    dmMN *currentNode;
    if(firstPosition >= position && position < diference)
        currentNode = (*node)->nodeFirst;
    else if(diference >= position && (diference = (lastPosition-currentPosition)/2) < position)
        currentNode = (*node)->nodeValue;
    else
        currentNode = (*node)->nodeLast;
    while((axys == dmAxysX ? currentNode->posX : currentNode->posY) != position){
        int result;
        currentPosition = (axys == dmAxysX ? currentNode->posX : currentNode->posY);
        if(currentPosition > position){
            result = __dmMN_prior(&currentNode, axys);
            if((axys == dmAxysX ? currentNode->posX : currentNode->posY) <  position)
                break;
        }else if(currentPosition < position){
            result = __dmMN_next(&currentNode, axys);
            if((axys == dmAxysX ? currentNode->posX : currentNode->posY) >  position)
                break;
        }
        if(result == dmEON || result == dmBON)
            break;
    }
    (*node)->nodeValue = currentNode;
    return dmTrue;
}
static int __dmCL_goToNearestPos(dmCL **node, int position){
    while(position != (*node)->position){
        int result;
        int lastPos = (*node)->position;
        if((*node)->position > position){
            result = __dmCL_prior(node);
            if((*node)->position < position)
                break;
        }else if((*node)->position < position){
            result = __dmCL_next(node);
            if((*node)->position > position)
                break;
        }
        if(result == dmEON || result == dmBON)
            break;
    }
    return dmTrue;
}
#define ___dm__dmChainedList_Functions
#endif
