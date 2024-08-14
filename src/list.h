#ifndef LIST_H

#include "structure.h"

typedef struct _list_node{
	void *data;
	struct _list_node *next;
} list_node;

typedef struct _list_controller{
	int length;
	list_node *first, *last;
} list_controller;

int list_init(list_controller **controller);
int list_push(list_controller *controller, void *data, structure_type type);
int list_pop(list_controller *controller, void **data, structure_type type);

#define LIST_H

#include "list.c"

#endif