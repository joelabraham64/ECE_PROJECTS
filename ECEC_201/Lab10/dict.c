#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dict.h"

/* Code within #if DEBUG ... #endif blocks will not be compiled
 * when DEBUG set to zero (it will be removed by the C preprocessor).
 *
 * set to 1 to ENABLE  bin fill display & pause for 1sec upon rehash *
 * set to 0 to DISABLE bin fill display & pause upon rehash          */
#define DEBUG 1


/* the infamous djb2 hashing function */
static unsigned long _hash(const char *key)
{
    int c;

    unsigned long hash = 5381;

    while ( (c = *key++) )
        hash = hash * 33 + c;

    return hash;
}


#if DEBUG
static void dict_debug_bin_fill(struct dict *D)
{
    unsigned int idx;
    unsigned long int n;
    struct list *cur;

    for (idx=0, n=0; idx<D->nbins; idx++, n=0) {
        for(cur=D->bins[idx]; cur; cur=cur->next)
            n++;

        fprintf(stderr, "bin[%d]: %lu\n", idx, n);
    }

    fprintf(stderr, "Rehashing...\n");
    /* pause for 1 second */
    sleep(1);
}
#else
#define dict_debug_bin_fill(D)
#endif


static int dict_rehash(struct dict *D)
{
    unsigned int new_size = D->nbins * 2;
    struct list **new_bins = malloc(new_size * sizeof(struct list *));
    if (!new_bins) {
        return 0;
    }

    /*Initialize the new bin array with NULL pointers*/
    unsigned int i;
    for (i = 0; i < new_size; i++)
        new_bins[i] = NULL;

    /*Migrate items from current bin array to the new bin array*/
    for (i = 0; i < D->nbins; i++) {
        struct list *cur = D->bins[i];
        while (cur) {
            struct list *next = cur->next;            
            unsigned int new_idx = cur->hash % new_size;
            cur->next = new_bins[new_idx];
            new_bins[new_idx] = cur;
            cur = next;
        }
    }

    /* Free the memory allocated for the old bin array*/
    free(D->bins);

    D->bins = new_bins;
    D->nbins = new_size;

    return 1; 
}


int dict_init(struct dict *D, void (*deleter)(void* user_data))
{
    int i;

    D->nbins = 6;
    D->bins = malloc(D->nbins*sizeof(*D->bins));
    if (!D->bins)
        return 0;

    for (i=0; i<D->nbins; i++)
        D->bins[i] = NULL;

    D->deleter = deleter;
    D->count = 0;   /* this line is new */

    return 1;
}


void dict_destroy(struct dict *D)
{
    unsigned int idx;
    struct list *cur;

    for (idx=0; idx<D->nbins; idx++) {
        while(D->bins[idx]) {
            cur = D->bins[idx];
            D->bins[idx] = cur->next;

            if (D->deleter)
                D->deleter(cur->user_data);

            free(cur->key);
            free(cur);
        }
    }

    free(D->bins);
}


int dict_insert(struct dict *D, const char *key, void *user_data)
{
    float load = (float)(D->count + 1) / D->nbins;
    unsigned int idx = _hash(key) % D->nbins;
    struct list *item;

    /* Rehash if load factor is not less than 0.75 ***********/
    if (load >= 0.75) {
        dict_debug_bin_fill(D);
        if (!dict_rehash(D))
            return 0;  /* rehash (& insertion) failed */
    }
    /*********************************************************/

    item = malloc(sizeof(*item));

    if (!item) {
        fprintf(stderr, "Insert Failed\n");
        return 0;
    }

    item->key = malloc(strlen(key)+1);
    if (!item->key) {
        fprintf(stderr, "Insert Failed\n");
        free(item);
        return 0;
    }

    strcpy(item->key, key);

    item->hash = _hash(key);
    item->user_data = user_data;

    item->next = D->bins[idx];
    D->bins[idx] = item;
    D->count++;     /* this line is new */

    return 1;
}


void dict_delete(struct dict *D, const char *key)
{
    void *user_data;

    if (D->deleter && (user_data = dict_pop(D, key)))
        D->deleter(user_data);
}


void *dict_peek(struct dict *D, const char *key)
{
    struct list *cur;

    unsigned long hash = _hash(key);
    unsigned int idx = hash % D->nbins;

    for (cur=D->bins[idx]; cur; cur=cur->next)
        if (hash == cur->hash)
            if (!strcmp(cur->key, key))
                return cur->user_data;

    return NULL;
}


void *dict_pop(struct dict *D, const char *key)
{
    struct list *cur;
    void *user_data;

    unsigned long hash = _hash(key);
    unsigned int idx = hash % D->nbins;
    struct list **prev_next = &D->bins[idx];

    for (cur=D->bins[idx]; cur; cur=cur->next) {
        if (hash == cur->hash)
            if (!strcmp(cur->key, key)) {
                *prev_next = cur->next;
                user_data = cur->user_data;
                free(cur->key);
                free(cur);
                D->count--;     /* this line is new */
                return user_data;
            }

        prev_next = &cur->next;
    }

    return NULL;
}


/* this function is new */
float dict_loadfactor(struct dict *D)
{
    return (float)D->count / D->nbins;
}
