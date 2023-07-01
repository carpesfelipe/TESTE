
#include <stdlib.h>

#include "hash.h"
#include "forward_list.h"

struct HashTable
{
    ForwardList **buckets;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
    int table_size;
    int n_elements;
};
struct HashTableIterator
{
    HashTable *h;
    int idx_bucket;
    Node *current;
};
typedef struct
{
    void *key;
    void *val;
} HashTableItem;

HashTableItem *_hash_pair_construct(void *key, void *val)
{
    HashTableItem *p = calloc(1, sizeof(HashTableItem));
    p->key = key;
    p->val = val;
    return p;
}

void _hash_pair_destroy(HashTableItem *p)
{
    free(p);
}

HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn)
{
    HashTable *hash_tbl = calloc(1, sizeof(HashTable));

    hash_tbl->table_size = table_size;
    hash_tbl->hash_fn = hash_fn;
    hash_tbl->cmp_fn = cmp_fn;
    hash_tbl->buckets = calloc(table_size, sizeof(ForwardList *));
    hash_tbl->n_elements = 0;

    return hash_tbl;
}

void *hash_table_set(HashTable *h, void *key, void *val)
{
    if (h == NULL || key == NULL || val == NULL)
    {
        return NULL;
    }
    int idx = h->hash_fn(h, key) % h->table_size;
    HashTableItem *item = _hash_pair_construct(key, val);
    if (h->buckets[idx] == NULL)
    {
        h->buckets[idx] = forward_list_construct();
        forward_list_push_front(h->buckets[idx], item);
    }
    else
    {
        ListIterator *it = list_front_iterator(h->buckets[idx]);
        while (!list_iterator_is_over(it))
        {
            data_type *curr = list_iterator_next(it);
            if (!h->cmp_fn(key, _hash_pair_get_key((HashTableItem *)curr)))
            {
                void *old_value = _hash_pair_get_value((HashTableItem *)curr);
                curr = item;
                free(it);
                return old_value;
            }
        }
        free(it);
        forward_list_push_back(h->buckets[idx], item);
    }
    h->n_elements++;
    return NULL;
}
void *_hash_pair_get_key(HashTableItem *item)
{
    return item->key;
}
void *_hash_pair_get_value(HashTableItem *item)
{
    return item->val;
}
void *hash_table_get(HashTable *h, void *key)
{
    int idx = h->hash_fn(h, key) % h->table_size;
    if (h->buckets[idx] == NULL)
    {
        return NULL;
    }
    ListIterator *it = list_front_iterator(h->buckets[idx]);
    while (!list_iterator_is_over(it))
    {
        data_type *curr = list_iterator_next(it);
        if (!h->cmp_fn(key, _hash_pair_get_key((HashTableItem *)curr)))
        {
            free(it);
            return curr;
        }
    }
    free(it);
    return NULL;
}

void *hash_table_pop(HashTable *h, void *key)
{
    int idx = h->hash_fn(h, key) % h->table_size;
    if (h->buckets[idx] == NULL)
    {
        return NULL;
    }
    ListIterator *it = list_front_iterator(h->buckets[idx]);
    ListIterator *prev = NULL;
    while (!list_iterator_is_over(it))
    {
        data_type * curr=list_iterator_get_value(it); 
        if (!h->cmp_fn(key, _hash_pair_get_key((HashTableItem *)curr)))
        {
            
            if (prev == NULL)
            {
                curr=forward_list_pop_front(h->buckets[idx]);
            }
            else
            {
                //salvar valor para retornar
                //o ponteiro pro proximo do anterior, tem q ser o proximo do atual
                //prev->next=current->next, pois o current sera deletado(free no No e nao no valor)
                node_get_next(list)
                curr=list_iterator_get_value(it);

                list_iterator_next(prev);
                prev = ;
            }
            return curr;
        }
        prev=it;
        list_iterator_next(it);
    }
    list_iterator_destroy(it);

    return NULL;
}

int hash_table_size(HashTable *h)
{
    return h->table_size;
}

int hash_table_num_elems(HashTable *h)
{
    return h->n_elements;
}

void hash_table_destroy(HashTable *h)
{
    for (int i = 0; i < h->table_size; i++)
    {
        if (h->buckets[i] != NULL)
        {
            HashTableIterator *it = hash_table_iterator(h);

            while (!hash_table_iterator_is_over(it))
            {
                HashTableItem *pair = it->current;
                _hash_pair_destroy(pair);
                it = hash_table_iterator_next(it);
            }

            forward_list_destroy(h->buckets[i]);
        }
    }

    free(h->buckets);
    free(h);
}
HashTableIterator *hash_table_iterator(HashTable *h)
{
    if (h == NULL)
        return NULL;
    HashTableIterator *it = calloc(1, sizeof(HashTableIterator));
    it->h = h;
    it->idx_bucket = 0;
    it->current = h->buckets[0];
    return it;
}

int hash_table_iterator_is_over(HashTableIterator *it)
{
}

HashTableItem *hash_table_iterator_next(HashTableIterator *it)
{
}

void hash_table_iterator_destroy(HashTableIterator *it)
{
}
