#ifdef __dm_dmMNDefinitions
static int __dmMN_clear(dmMN **node, int axys){
    dmMN *nodeValue;
    int result;
    while (result == dmTrue){
        nodeValue = *node;
        result = __dmMN_next(node, axys);
        __dmMN_remove(&nodeValue);
    }
    return (result == dmBON ? dmTrue : result);
}
static int __dmMN_create(dmMN **node){
    *node = (dmMN *) malloc(sizeof(dmMN));
    (*node)->priorX = NULL;
    (*node)->nextX = NULL;
    (*node)->priorY = NULL;
    (*node)->nextY = NULL;
    return dmTrue;
}
static int __dmMN_next(dmMN **node, int axys){
    if(node == NULL)
        return dmNull;
    if(axys < dmAxysX || axys > dmAxysY)
        return dmWrongAxys;
    dmMN *initialNode = (*node);
    if(axys == dmAxysX && (*node)->nextX != NULL)
        *node = (*node)->nextX;
    else if(axys == dmAxysY && (*node)->nextY != NULL)
        *node = (*node)->nextY;
    return (*node != initialNode ? dmTrue : dmEON);
}
static int __dmMN_prior(dmMN **node, int axys){
    if(node == NULL)
        return dmNull;
    if(axys < dmAxysX || axys > dmAxysY)
        return dmWrongAxys;
    dmMN *initialNode = (*node);
    if(axys == dmAxysX && (*node)->priorX != NULL)
        *node = (*node)->priorX;
    else if(axys == dmAxysY && (*node)->priorY != NULL)
        *node = (*node)->priorY;
    return (*node != initialNode ? dmTrue : dmEON);
}
static int __dmMN_remove(dmMN **node){
    if(node == NULL)
        return dmNull;
    dmMN *returnNode = NULL;
    if((*node)->priorX != NULL){
        ((*node)->priorX)->nextX = (*node)->nextX;
        returnNode = (*node)->priorX;
    }
    if((*node)->nextX != NULL){
        ((*node)->nextX)->priorX = (*node)->priorX;
        returnNode = (*node)->nextX;
    }
    if((*node)->priorY != NULL){
        ((*node)->priorY)->nextY = (*node)->nextY;
        returnNode = (*node)->priorY;
    }
    if((*node)->nextY != NULL){
        ((*node)->nextY)->priorY = (*node)->priorY;
        returnNode = (*node)->nextY;
    }
    free((*node));
    *node = returnNode;
    return dmTrue;
}
#define ___dm__dmMatrixNode_Functions
#endif
