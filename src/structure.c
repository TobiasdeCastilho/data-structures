#include <stdlib.h>

#include "structure.h"

int init(strucuture_controller **controller, structure_type type){
	*controller = (strucuture_controller *)malloc(sizeof(strucuture_controller));
	(*controller)->type = type;
	(*controller)->length = 0;
	(*controller)->first = NULL;
	(*controller)->last = NULL;
	return 0;
}

int push(strucuture_controller *controller, void *data){		
	structure_node *node = (structure_node *)malloc(sizeof(structure_node));
	node->data = data;
	node->prior = NULL;
	node->next = NULL;	
	switch (controller->type)
	{
		case stack:		
			node->next = controller->first;		
			if(controller->last == NULL)
				controller->last = node;			
			else 
				controller->first->prior = node;						
			controller->first = node;
		break;	
		case queue:
			node->prior = controller->last;		
			if(controller->first == NULL)
				controller->first = node;			
			else 
				controller->last->next = node;						
			controller->last = node;
		break;
		default: exit(INVALID_STRUCTURE_TYPE);		
	}
	
	controller->length++;
	return 0;
}

int pop(strucuture_controller *controller, void **data){		
	if(controller->length == 0)
		return 1;

	structure_node *node;		
	switch (controller->type)
	{
		case stack:			
		case queue:
			node = controller->first;
			controller->first = controller->first->next;			
		break;
		default: exit(INVALID_STRUCTURE_TYPE);		
	}	
	*data = node->data;	

	free(node);	
	
	controller->length--;	
	return 0;
}