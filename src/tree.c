#include "tree.h"

int tree_init(tree_controller **controller){
	*controller = (tree_controller *)malloc(sizeof(tree_controller));
	(*controller)->length = 0;
	(*controller)->height = 0;
	(*controller)->rule = NULL;
	(*controller)->root = NULL;
	return 0;
}

int tree_set_rule(tree_controller *controller, tree_rule rule){
	controller->rule = rule;
	return 0;
}

int tree_push(tree_controller *controller, void *data){
	if(controller->rule == NULL)
		exit(102);
	
	tree_node *node = (tree_node *)malloc(sizeof(tree_node));
	node->data = data;
	node->depth = 0;
	node->left = NULL;
	node->right = NULL;
	
	if(controller->root == NULL){
		controller->root = node;
		controller->height = 1;
		return 0;
	}

	tree_node *current = controller->root;
	tree_node *parent = NULL;
	node->depth = 1;
	while(current != NULL){
		parent = current;		
		current = (controller->rule(data, current->data) < 0) ? current->left : current->right;		
		node->depth++;
	}	


	if(node->depth > controller->height)
		controller->height = node->depth;
		
	if(controller->rule(data, parent->data) < 0)
		parent->left = node;
	else
		parent->right = node;
	
	controller->length++;
	return 0;
}
