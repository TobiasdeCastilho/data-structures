#include <stdlib.h>

#include "structure.h"

int init(strucuture_controller **controller, structure_type type){
	*controller = (strucuture_controller *)malloc(sizeof(strucuture_controller));
	(*controller)->type = type;
	switch (type)
	{
		case queue:
		case stack:
			list_init((list_controller **) &(*controller)->_struct);
		break;
		case binary_tree:
		break;
		default:
		break;
	}
	return 0;
}

int push(strucuture_controller *controller, void *data){			
	switch (controller->type){
		case stack:			
		case queue:
			return list_push(controller->_struct, data, controller->type);			
		default:
		 	exit(INVALID_STRUCTURE_TYPE);
	}	
}

int pop(strucuture_controller *controller, void **data){		
	switch (controller->type){
		case stack:			
		case queue:
			return list_pop(controller->_struct, data, controller->type);
		default:
			exit(INVALID_STRUCTURE_TYPE);
	}			
}