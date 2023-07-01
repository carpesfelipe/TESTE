
#include "deque.h"
#include "types.h"
#include "fila_circular.h"
#include <stdlib.h>
#include <stdio.h>
struct Deque
{
    FilaCircular * fila;
};
#define MAX_TAM 100
// criacao do deque
Deque *deque_construct(){
    Deque * d=calloc(1,sizeof(Deque));
    d->fila=fila_circular_constroi(MAX_TAM);
    return d;
}

// funcoes para insercao na direita e esquerda (devem ser feitas em O(1), com eventual realloc)
void deque_push_back(Deque *d, void *val){
    fila_circular_push_back(d->fila,val);
}
void deque_push_front(Deque *d, void *val){
    fila_circular_push_front(d->fila,val);
}

// funcoes para remocao na direita e esquerda (devem ser feitas em O(1))
void *deque_pop_back(Deque *d){
    return fila_circular_pop_back(d->fila);
}
void *deque_pop_front(Deque *d){
    return fila_circular_pop_back(d->fila);

}

// numero de elementos
int deque_size(Deque *d){
    return fila_circular_size(d->fila);
}

// obtem o i-esimo elemento
void *deque_get(Deque *d, int idx){
    return fila_circular_get(d->fila,idx);
}

// libera o espaco alocado para o deque
void deque_destroy(Deque *d){
    fila_circular_destroi(d->fila);
    free(d);
}