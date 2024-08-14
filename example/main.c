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
 	else {
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
	
	void *x;
	int sum = 0, i = 1;	
	while(!pop(controller, &x)){
		printf("Popped %d\n", *(int *)(x));	
		if(i & 2 == 2)
			sum += *(int *)(x);		
		else
			sum -= *(int *)(x);						
		i++;
		free(x);		
	}
	
	printf("%d\n", sum);
	return 0;
}