
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include "forward_list.h"
#include "stack.h"
#include "types.h"

struct Stack
{
    ForwardList * list;
};


Stack *stack_construct(){
    Stack * stack=calloc(1,sizeof(struct Stack));
    stack->list=forward_list_construct();
    return stack;
}

void stack_push(Stack *s, data_type val){
    forward_list_push_front(s->list,val);
}

data_type stack_pop(Stack *s){
    data_type val=forward_list_pop_front(s->list);
    return val;
}

bool stack_empty(Stack *s){
    if(forward_list_size(s->list)==0){
        return 1;
    }else{
        return 0;
    }
}

void stack_destroy(Stack *s){
    forward_list_destroy(s->list);
    free(s);
} 
