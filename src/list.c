#include "list.h"

int list_init(list_controller **controller){
	*controller = (list_controller *)malloc(sizeof(list_controller));
	(*controller)->length = 0;
	(*controller)->first = NULL;
	(*controller)->last = NULL;
	return 0;
}

int list_push(list_controller *controller, void *data, structure_type type){
	list_node *node = (list_node *)malloc(sizeof(list_node));
	node->data = data;	
	node->next = NULL;	
	
	switch (type)
	{
		case stack:		
			node->next = controller->first;		
			if(controller->last == NULL)
				controller->last = node;			
			controller->first = node;
		break;	
		case queue:
			node->next = controller->last;	
			if(controller->first == NULL)
				controller->first = node;			
			controller->last = node;
		break;
		default: exit(INVALID_STRUCTURE_TYPE);		
	}	
	
	controller->length++;
	return 0;
}

int list_pop(list_controller *controller, void **data, structure_type type){	
	if(controller->length == 0)
		return 1;
	
	list_node *node = NULL;
	switch (type)
	{
		case stack:		
			node = controller->first;						
			if((controller->first = node->next) == NULL)
				controller->last = NULL;			
		break;	
		case queue:
			node = controller->last;						
			if((controller->last = node->next) == NULL)
				controller->first = NULL;
		break;
		default: 
			exit(INVALID_STRUCTURE_TYPE);		
	}

	*data = node->data;	
	free(node);
	
	controller->length--;	
	return 0;
}
