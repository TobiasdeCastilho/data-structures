#include <stdio.h>
#include <string.h>

#include "../src/structure.h"

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
	else{
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
	printf("%d data added\n", controller->length);
	
	void *x;
	int sum = 0, i = 1;	
	while(!pop(controller, &x)){
		if(i & 2 == 2)
			sum += *(int *)(x);			
		else
			sum -= *(int *)(x);						
		i++;
	}
				
	printf("%d\n", sum);
	
	return 0;
}

int shift(strucuture_controller *controller, void **data){
	if(controller->length == 0)
		return 1;
	
	structure_node *node = controller->first;
	*data = node->data;
	controller->first = node->next;
	if(controller->first != NULL)
		controller->first->prior = NULL;
	free(node);
	controller->length--;
	return 0;
}