#include "dmConstants.h"
#include <stdio.h>
#include <stdlib.h>
#define __dm_included
#define __dm_tridimensional
typedef struct dmMatrixNode{
    struct dmMatrixNode *priorX, *nextX;
    int posX;
    struct dmMatrixNode *priorY, *nextY;
    int posY;
    int value;
} dmMN;
#define __dm_dmMatrixNode
typedef struct dmChainedList{
    struct dmChainedList *next, *prior;
    dmMN *nodeValue, *nodeFirst, *nodeLast;
    int position;
} dmCL;
#define __dm_dmChainedList
typedef struct dynamicMatrix{
    dmCL *axysX, *axysXFirst, *axysXLast;
    dmCL *axysY, *axysYFirst, *axysYLast;
    dmMN *nodeValue;
} dMatrix;
#define __dm_dynamicMatrix
#define __dm_included
static int __dmMN_create(dmMN **node);
static int __dmMN_next(dmMN **node, int axys);
static int __dmMN_prior(dmMN **node, int axys);
static int __dmMN_remove(dmMN **node);
#define __dm_dmMNDefinitions
#include "dmMatrixNodeFunctions.h"
static int __dmCL_clear(dmCL **node);
static int __dmCL_freeNode(dmCL **node);
static int __dmCL_goToNearestNode(dmCL **node, int position, int axys);
static int __dmCL_goToNearestPos(dmCL **node, int position);
static int __dmCL_initializer(dmCL **node);
static int __dmCL_insert(dmCL **node, int position);
static int __dmCL_next(dmCL **node);
static int __dmCL_prepareNode(dmCL **node);
static int __dmCL_prior(dmCL **node);
#define __dm_dmCLDefinitions
#include "dmChainedListFunctions.h"
static int __dMatrix_clear(dMatrix *matrix);
static int __dMatrix_first(dMatrix *matrix, int axys);
static int __dMatrix_insert(dMatrix *matrix, int value, int position[2]);
static int __dMatrix_initializer(dMatrix *matrix);
static int __dMatrix_remove(dMatrix *matrix);
static int __dMatrix_goTo(dMatrix *matrix, int position[2]);
#define __dm_DinamycMatrixDefinitions
#include "dmDinamycMatrixFunctions.h"
int dmDown(dMatrix *matrix);
int dmInitializer(dMatrix *matrix);
int dmInsert(dMatrix *matrix, int value, int position[2]);
int dmGetPosistion(dMatrix matrix, int *position[2]);
int dmGetValue(dMatrix matrix, int *result);
int dmLeft(dMatrix *matrix);
int dmPosition(dMatrix *matrix, int posision[2]);
int dmRemove(dMatrix *matrix, int posision[2]);
int dmRemoveCurrent(dMatrix *matrix);
int dmRigth(dMatrix *matrix);
int dmUp(dMatrix *matrix);
#define __dm_DynamicMatrixUsualFunctions
#include "dmDynamicMatrixUsualFunctions.h"