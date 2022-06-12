#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

HashTable *createHash(int size, char *(* getSymbol) (void *));
void destroyHash(HashTable *table);
void *installHash(HashTable *table, void *object);
void *uninstallHash(HashTable *table, char *symbol);
static unsigned hash(HashTable *table, char *symbol);

HashTable *createHash(int size, char *(* getSymbol) (void *)){
    HashTable *table;

    table = (struct htab *) malloc(sizeof(HashTable));
    table->size = size;
    table->table = (struct hlink **) calloc(size, sizeof(HashLink *));
    table->getSymbol = getSymbol;
}

void destroyHash(HashTable *table){
    HashLink *link, *next;
    int i;

    for(i = 0; i < table->size; i++){
        for(link = table->table[i]; link != NULL; link = link->next){
            next = link->next;
            free((void *) link);
        }
    }
    free((void *) table->table);
    free((void *) table);
}

void *installHash(HashTable *table, void *object){
    HashLink *link;
    char *symbol;
    unsigned hashVal;
    void *old = NULL;

    symbol = (* table->getSymbol)(object);
    hashVal = hash(table, symbol);

    for(link = table->table[hashVal]; link != NULL; link = link->next)
        if(strcmp(table->getSymbol(link->object), symbol) == 0) break;
    if(link == NULL){
        link = (struct hlink *) malloc(sizeof(HashLink));
        link->next = table->table[hashVal];
        table->table[hashVal] = link;
    }else{
        old = link->object;
    }
    link->object = object;
    return(old);
}

void *uninstallHash(HashTable *table, char *symbol){
    HashLink *link, **pLink;
    unsigned hashVal;
    void *object;

    hashVal = hash(table, symbol);
    for(pLink = &(table->table[hashVal]); link = *pLink; pLink = &(link->next))
        if(strcmp(table->getSymbol(link->object),symbol) == 0) break;
    if(link == NULL) return((void *) NULL);
    else{
        *pLink = link->next;
        object = link->object;
        free((void *) link);
        return(object);
    }
}

static unsigned hash(HashTable *table, char *symbol){
    unsigned hashVal;

    for(hashVal = 0; *symbol != '\0'; symbol++){
        hashVal = *symbol + 31 * hashVal;
    }

    return(hashVal % table->size);
}

void *lookUpHash(HashTable *table, char *symbol){
    HashLink *link;

    for(link = table->table[hash(table, symbol)]; link != NULL; link = link->next){
        if(strcmp(table->getSymbol(link->object),symbol) == 0){
            return link->object;
        }
    }
    
    return NULL;
}