#include "forward_list.h"
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    data_type value;
    struct Node *next;
};
Node *node_construct(data_type value, Node *next)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->value = value;
    n->next = next;
    return n;
}

void node_destroy(Node *n)
{
    free(n);
}
struct ForwardList
{
    Node *head;
    Node *last;
    int size;
};
struct ListIterator
{
    Node * current;
};


// cria uma lista
ForwardList *forward_list_construct()
{
    ForwardList *list = calloc(1, sizeof(ForwardList));
    list->size = 0;
    list->head =list->last=NULL;
    return list;
}
// retorna o número de elementos na lista
int forward_list_size(ForwardList *l)
{
    return l->size;
}
// adiciona um item no início da lista
void forward_list_push_front(ForwardList *l, data_type val)
{
    Node *n = node_construct(val, l->head);
    l->head = n;
    l->size++;
}
//adiciona um item ao final da lista;
void forward_list_push_back(ForwardList *l, data_type val){
    Node *n=node_construct(val,NULL);
    if(l->size==0){
        l->last=l->head=n;
    }else{
        l->last->next=n;
        l->last=n;
    }
    l->size++;
}
// mostra a lista na tela
void forward_list_print(ForwardList *l, void (*print_fn)(data_type))
{
    Node *n = l->head;
    printf("[");
    while (n != NULL)
    {
        print_fn(n->value);
        if (n->next != NULL)
        {
            printf(", ");
        }
        n = n->next;
    }
    printf("]");
}
// retorna o i-ésimo elemento da lista
data_type forward_list_get(ForwardList *l, int i)
{
    int x = 0;
    if (i < 0 || i >= l->size)
    {
        printf("Indice inválido!");
        exit(1);
    }
    data_type value;
    Node *n = l->head;
    while (n != NULL)
    {
        if (x == i)
        {
            value = n->value;
        }
        x++;
        n = n->next;
    }
    return value;
}
// remove o primeiro elemento
data_type forward_list_pop_front(ForwardList *l)
{
    Node *next_n = l->head->next;
    data_type value = l->head->value;
    node_destroy(l->head);
    l->head = next_n;
    l->size--;
    return value;
}
data_type forward_list_pop_back(ForwardList *l)
{
    Node *next_n = l->last->next;
    data_type value = l->last->value;
    node_destroy(l->last);
    l->last = next_n;
    l->size--;
    return value;
}
Node * node_get_next(Node * n){
    return n->next;
}
void * node_get_value(Node * n){
    return n->value;
}
Node * forward_list_get_head(ForwardList * l){
    return l->head;
}
// retorna uma lista contendo o reverso de outra
ForwardList *forward_list_reverse(ForwardList *l)
{
    ForwardList *l_reversed = forward_list_construct();
    Node *n = l->head;
    while (n != NULL)
    {
        forward_list_push_front(l_reversed, n->value);
        n = n->next;
    }
    return l_reversed;
}
void forward_list_clear(ForwardList *l)
{
    if (l->size == 0)
        return;

    Node *n = l->head;
    Node *next_node = n->next;
    while (n != NULL)
    {
        next_node = n->next;
        node_destroy(n);
        n = next_node;
        l->size--;
    }
}
void forward_list_remove(ForwardList *l, data_type val)
{
    if (l->size == 0)
    {
        return;
    }
    Node *n = l->head;
    Node *previous_node = NULL;
    Node *next_node = NULL;
    while (n != NULL)
    {
        if (n->value == val)
        {
            if (previous_node == NULL)
            {
                next_node = n->next;
                node_destroy(n);
                l->head = next_node;
            }
            else
            {
                previous_node->next = next_node = n->next;
                node_destroy(n);
            }
            n = next_node;
            l->size--;
        }
        else
        {
            previous_node = n;
            n = n->next;
        }
    }
}
ListIterator *list_front_iterator(ForwardList *l){
    ListIterator * it=calloc(1,sizeof(ListIterator));
    it->current=l->head;
    return it;
}
data_type *list_iterator_next(ListIterator *it){
    data_type * value=&(it->current->value);
    it->current=it->current->next;
    return value;
}

void * list_iterator_get_value(ListIterator * it){
    return it->current->value;
}
int list_iterator_is_over(ListIterator *it){
    if(it->current==NULL){
        return 1;
    }else{
        return 0;
    }
}
void list_iterator_destroy(ListIterator *it){
    node_destroy(it->current);
    free(it);
}
void forward_list_destroy(ForwardList *l)
{
    if (l->size == 0)
    {
        free(l);
        return;
    }
    Node *n = l->head;
    Node *next_node = n->next;
    while (n != NULL)
    {
        next_node = n->next;
        node_destroy(n);
        n = next_node;
    }
    free(l);
}