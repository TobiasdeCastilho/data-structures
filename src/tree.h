#ifndef TREE_H

typedef enum _tree_travel_type{
	pre_order,
	in_order,
	post_order,	
} tree_travel_type;

typedef struct _tree_node{
	void *data;
	int depth;
	struct _tree_node *left, *right;
} tree_node;

typedef int (tree_rule)(void *, void *);

typedef struct _tree_controller{
	int length, height;
	tree_rule *rule;
	tree_node *root;	
} tree_controller;

int tree_init(tree_controller **controller);
int tree_set_rule(tree_controller *controller, tree_rule rule);
int tree_push(tree_controller *controller, void *data);

#define TREE_H

#include <stdlib.h>
#include "tree.c"

#endif