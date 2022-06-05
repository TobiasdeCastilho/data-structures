#include <stdlib.h>

typedef struct les
{
    struct les *next;
    int value;
} ls;

int initializer(ls *l){
    if(l != NULL)
        freeList(l);
    l = NULL;
    return 0;
}

int freeList(ls *l){
    ls *prior;
    while(l != NULL){
        prior = l;
        next(&l);
        free(prior);
    }
    return 0;
}

int insert(ls **l,const int v){
    ls *nL = (ls *) malloc(sizeof(ls));
    nL->value = v;
    nL->next = NULL;
    ls *current = *l;
    if(*l != NULL) 
        if((*l)->value >= v){
            nL->next = (*l);
        }else{
            ls *prior;
            while(current != NULL){
                prior = current;
                if(current->value > v){
                    nL->next = current;
                    break;
                }
                next(&current);
            }
            if(nL->next == NULL)
                prior->next = nL;
        }
    if(current == (*l))
        (*l) = nL;
    return 0;
}

int next(ls **l){
    if((*l) != NULL)
        (*l) = (*l)->next;
    return 0;
}   