
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include "forward_list.h"
#include "types.h"

struct Queue
{
    ForwardList * list;
};


Queue *queue_construct(){
    Queue * queue=calloc(1,sizeof(struct Queue));
    queue->list=forward_list_construct();
    return queue;
}

void stack_push(Queue *q, data_type val){
    forward_list_push_back(q->list,val);
}

data_type queue_pop(Queue *q){
    data_type val=forward_list_pop_front(q->list);
    return val;
}

bool queue_empty(Queue *q){
    if(forward_list_size(q->list)==0){
        return 1;
    }else{
        return 0;
    }
}

void stack_destroy(Queue *q){
    forward_list_destroy(q->list);
    free(q);
} 
