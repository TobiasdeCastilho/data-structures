#ifndef _datastructure_structure_h

#define _datastructure_structure_h

#define INVALID_STRUCTURE_TYPE 100

typedef enum _structure_type {
	stack,
	queue,	
} structure_type; 

typedef struct _structure_node {	
	void *data;
	struct _structure_node *prior, *next;
} structure_node;

typedef struct _strucuture_controller {
	structure_type type;		
	int length;
	structure_node *first, *last;
} strucuture_controller;

int init(strucuture_controller **controller, structure_type type);
int push(strucuture_controller *controller, void *data);
int pop(strucuture_controller *controller, void **data);
int shift(strucuture_controller *controller, void **data);

#include "structure.c"

#endif