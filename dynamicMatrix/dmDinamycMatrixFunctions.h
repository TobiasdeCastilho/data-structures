#ifdef __dm_DinamycMatrixDefinitions
static int __dMatrix_clear(dMatrix *matrix){
    int result;
    matrix->axysX = matrix->axysXFirst;
    while(matrix->axysX != NULL){
        if((result = __dmMN_clear(&((matrix->axysX)->nodeValue),dmAxysX)) != dmTrue)
            return result;
        if(result = __dmCL_next(&(matrix->axysX)) != dmTrue)
            return result;
    }
    if(matrix->axysY != NULL)
        if(result = __dmCL_clear(&(matrix->axysX)) != dmTrue)
            return result;
    matrix->nodeValue = NULL;
    return dmTrue;
}
static int __dMatrix_first(dMatrix *matrix, int axys){
    dmMN *dMAux = (axys == dmAxysX ? (matrix->axysX)->nodeFirst : (axys == dmAxysY ? (matrix->axysY)->nodeFirst : NULL));
    if(dMAux == NULL)
        return dmFalse;
    else{
        matrix->nodeValue = dMAux;
        return dmTrue;
    }
}
static int __dMatrix_insert(dMatrix *matrix, int value, int position[2]){
    int result;
    dmMN *node = NULL;
    if(result = __dmMN_create(&node) != dmTrue)
        return result;
    node->posX = position[0];
    node->posY = position[1];
    node->value = value;
    if(__dmCL_insert(&(matrix->axysX), position[0]) != dmTrue){
        __dmCL_goToNearestNode(&(matrix->axysX), position[1], dmAxysY);
        if(((matrix->axysX)->nodeValue)->posX == position[0] && ((matrix->axysX)->nodeValue)->posY == position[1])
            return dmFalse;
        if(((matrix->axysX)->nodeValue)->posY > position[1]){
            node->priorY = ((matrix->axysX)->nodeValue)->priorY;
            node->nextY = (matrix->axysX)->nodeValue;
            if(((matrix->axysX)->nodeValue)->priorY != NULL)
                (((matrix->axysX)->nodeValue)->priorY)->nextY = node;
            ((matrix->axysX)->nodeValue)->priorY = node;
        }else{
            node->nextY = ((matrix->axysX)->nodeValue)->nextY;
            node->priorY = (matrix->axysX)->nodeValue;
            if(((matrix->axysX)->nodeValue)->nextY != NULL)
                (((matrix->axysX)->nodeValue)->nextY)->priorY = node;
            ((matrix->axysX)->nodeValue)->nextY = node;
        }
        if((matrix->axysX)->nodeFirst->posX > node->posX)
            (matrix->axysX)->nodeFirst = node;
        else if(((matrix->axysX)->nodeLast)->posX < node->posX)
            (matrix->axysX)->nodeLast = node;
    }else{
        (matrix->axysX)->nodeFirst = node;
        (matrix->axysX)->nodeValue = node;
        (matrix->axysX)->nodeLast = node;
    }
    if(__dmCL_insert(&(matrix->axysY), position[1]) != dmTrue){
        __dmCL_goToNearestNode(&(matrix->axysY), position[0], dmAxysX);    
        if(((matrix->axysY)->nodeValue)->posX > position[0]){
            node->priorX = ((matrix->axysY)->nodeValue)->priorX;
            node->nextX = (matrix->axysY)->nodeValue;
            if(((matrix->axysY)->nodeValue)->priorX != NULL)
                (((matrix->axysY)->nodeValue)->priorX)->nextX = node;
            ((matrix->axysY)->nodeValue)->priorX = node;
        }else{
            node->nextX = ((matrix->axysY)->nodeValue)->nextX;
            node->priorX = (matrix->axysY)->nodeValue;
            if(((matrix->axysY)->nodeValue)->nextX != NULL)
                (((matrix->axysY)->nodeValue)->nextX)->priorX = node;
            ((matrix->axysY)->nodeValue)->nextX = node;
        }
        if((matrix->axysY)->nodeFirst->posY > node->posY)
            (matrix->axysY)->nodeFirst = node;
        else if(((matrix->axysY)->nodeLast)->posY < node->posX)
            (matrix->axysY)->nodeLast = node;
    }else{
        (matrix->axysY)->nodeFirst = node;
        (matrix->axysY)->nodeValue = node;
        (matrix->axysY)->nodeLast = node;
    }
    matrix->nodeValue = node;
    (matrix->axysX)->nodeValue = node;
    (matrix->axysY)->nodeValue = node;
    if(matrix->axysXFirst == NULL){
        matrix->axysXFirst = matrix->axysX;
        matrix->axysXLast = matrix->axysX;
    }else if((matrix->axysX)->position < (matrix->axysXFirst)->position)
        matrix->axysXFirst = matrix->axysX;
    else if((matrix->axysX)->position > (matrix->axysXLast)->position)
        matrix->axysXLast = matrix->axysX;
    if(matrix->axysYFirst == NULL){
        matrix->axysYFirst = matrix->axysY;
        matrix->axysYLast = matrix->axysY;
    }else if((matrix->axysY)->position < (matrix->axysYFirst)->position)
        matrix->axysYFirst = matrix->axysY;
    else if((matrix->axysY)->position > (matrix->axysYLast)->position)
        matrix->axysYLast = matrix->axysY;        
    return dmTrue;
}
static int __dMatrix_initializer(dMatrix *matrix){
    matrix->axysXFirst = NULL;
    matrix->axysXLast = NULL;
    matrix->axysYFirst = NULL;
    matrix->axysYLast = NULL;
    matrix->axysX = NULL;
    matrix->axysY = NULL;
    matrix->nodeValue = NULL;
    return dmTrue;
}
static int __dMatrix_remove(dMatrix *matrix){
    int result;
    int positions[2] = {(matrix->nodeValue)->posX, (matrix->nodeValue)->posY};
    if((result = __dMatrix_goTo(matrix, positions)) != dmTrue)
        return result;
    if((matrix->nodeValue)->nextY == NULL && (matrix->nodeValue)->priorY == NULL)
        if((result = __dmCL_freeNode(&(matrix->axysX))) != dmTrue)
            return result;
    if((matrix->nodeValue)->nextX == NULL && (matrix->nodeValue)->priorX == NULL)
        if((result = __dmCL_freeNode(&(matrix->axysY))) != dmTrue)
            return result;
    if((result = __dmMN_remove(&(matrix->nodeValue))) != dmTrue)
        return result;
    if((result = __dMatrix_goTo(matrix, positions)) != dmTrue)
        return result;
    return dmTrue;
}
static int __dMatrix_goTo(dMatrix *matrix, int position[2]){
    int result;
    dmCL *clAux = matrix->axysX;
    if(result = __dmCL_goToNearestPos(&clAux,position[0]) != dmTrue)
        return result;
    if((result = __dmCL_goToNearestNode(&clAux,position[1],dmAxysY)) != dmTrue)
        return result;
    if((result = __dmCL_goToNearestPos(&(matrix->axysY),position[1])) != dmTrue)
        return result;
    if((result = __dmCL_goToNearestNode(&(matrix->axysY),position[0],dmAxysX)) != dmTrue)
        return result;
    matrix->axysX = clAux;
    matrix->nodeValue = clAux->nodeValue;
    return dmTrue;
}
#endif