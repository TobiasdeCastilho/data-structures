#ifdef __dm_DynamicMatrixUsualFunctions
int dmDown(dMatrix *matrix){
    int result = dmTrue;
    if((result = __dmMN_next(&(matrix->nodeValue), dmAxysY)) != dmTrue)
        return result;
    if((result = __dmCL_goToNearestPos(&(matrix->axysY), (matrix->nodeValue)->posY)) != dmTrue)
        return result;
    return result;
}
int dmInsert(dMatrix *matrix, int value, int position[2]){
    return __dMatrix_insert(matrix, value, position);
}
int dmInitializer(dMatrix *matrix){
    return __dMatrix_initializer(matrix);
}
int dmGetPosistion(dMatrix matrix, int *position[2]){
    if(matrix.nodeValue != NULL){
        (*position)[0] = (matrix.nodeValue)->posX;
        (*position)[1] = (matrix.nodeValue)->posY;
        return dmTrue;
    }
    return dmFalse;
}
int dmGetValue(dMatrix matrix, int *result){
    if(matrix.nodeValue != NULL){
        *result = (matrix.nodeValue)->value;
        return dmTrue;
    }
    return dmFalse;
}
int dmLeft(dMatrix *matrix){
    int result = dmTrue;
    if((result = __dmMN_prior(&(matrix->nodeValue), dmAxysX)) != dmTrue)
        return result;
    if((result = __dmCL_goToNearestPos(&(matrix->axysX), (matrix->nodeValue)->posX)) != dmTrue)
       return result;
    return result;
}
int dmPosition(dMatrix *matrix, int position[2]){
    return __dMatrix_goTo(matrix, position);
}
int dmRemove(dMatrix *matrix, int position[2]){
    int result;
    if((result = dmPosition(matrix,position)) != dmTrue)
        return result;
    return dmRemoveCurrent(matrix);
}
int dmRemoveCurrent(dMatrix *matrix){
    return __dMatrix_remove(matrix);
}
int dmRigth(dMatrix *matrix){
    int result = dmTrue;
    if((result = __dmMN_next(&(matrix->nodeValue), dmAxysX)) != dmTrue)
        return result;
    if((result = __dmCL_goToNearestPos(&(matrix->axysX), (matrix->nodeValue)->posX)) != dmTrue)
        return result;
    return result;
}
int dmUp(dMatrix *matrix){
    int result = dmTrue;
    if((result = __dmMN_prior(&(matrix->nodeValue), dmAxysY)) != dmTrue)
        return result;
    if((result = __dmCL_goToNearestPos(&(matrix->axysY), (matrix->nodeValue)->posY)) != dmTrue)
        return result;
    return result;
}
#endif