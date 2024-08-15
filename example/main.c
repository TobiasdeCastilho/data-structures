#include <stdio.h>
#include <string.h>

#include "../src/structure.h"

int travel(tree_node *node);
int compare(void *a, void *b);

int main(int argc, char const *argv[]){
	if(argc < 3){
		printf("Usage: %s <type> <data>\n", argv[0]);
		return 1;
	}

	strucuture_controller *controller;

	structure_type s_type;		
	const char *type = argv[1];
	printf("Trying to start the %s structure\n", type);
	if(strcmp(type, "stack") == 0)
		init(&controller, stack);		
	else if(strcmp(type, "queue") == 0)
		init(&controller, queue);
	else if(strcmp(type, "tree") == 0){
		init(&controller, binary_tree);
		tree_set_rule(((tree_controller *) controller->_struct), &compare);
	} else {
		printf("Invalid type\n");
		exit(INVALID_STRUCTURE_TYPE);		
	}		
	printf("Structure started\n");

	printf("Pushing data...\n");
	for (int i = 2; i < argc; i++){
		int *data = (int *)malloc(sizeof(int));
		*data = atoi(argv[i]);
		push(controller, data);
	}		
	printf("Data pushed\n");
	

	if(controller->type == binary_tree){
		travel(((tree_controller *) controller->_struct)->root);
		printf("\n");
	} else {
		void *x;
		int sum = 0, i = 1;	
		while(!pop(controller, &x)){		
			if(i & 2 == 2)
				sum += *(int *)(x);		
			else
				sum -= *(int *)(x);						
			i++;
			free(x);		
		}
	
		printf("%d\n", sum);
	}
	return 0;
}

int travel(tree_node *node){
	if(node == NULL)
		return 0;

	travel(node->left);
	printf("%d ", *(int *)node->data);
	travel(node->right);
	return 0;
}

int compare(void *a, void *b){
	int _a = *(int *)a;
	int _b = *(int *)b;

	return _a > _b ? 1 : -1;
}