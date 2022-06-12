#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binTree.h"

struct tnode * addTree(struct tnode *p, char *w){
    int cond;

    if(p == NULL){
        p = (struct tnode *) malloc(sizeof(struct tnode));
        p->word = (char *) malloc(strlen(w) + 1);
        strcpy(p->word, w);
        p->count = 1;
        p->left = p->right = NULL;
    }else if((cond = strcmp(w, p->word)) == 0) p->count++;
    else if(cond < 0) p->left = addTree(p->left, w);
    else p->right = addTree(p->right, w);

    return p;
}

void treePrint(struct tnode *p){
    if(p != NULL){
        treePrint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treePrint(p->right);
    }
}