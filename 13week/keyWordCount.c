#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "binTree.h"

#define MAXWORD 1000

struct key{
    char *word;
    int count;
} keytab[] = {
    {"auto", 0}
};//skip

#define NKEYS (sizeof keytab / sizeof(struct key))

int getWord(char *word, int lim);
struct key *binSearch(char *word, struct key tab[], int n);

int main(void){
    char word[MAXWORD];
    struct key *p;

    while(getWord(word, MAXWORD) != EOF){
        if(isalpha(word[0]) && ((p = binSearch(word, keytab, NKEYS)) == NULL)) p->count++;
    }
    for(p = keytab; p < keytab + NKEYS; p++)
        if(p->count > 0)
            printf("%4d %s\n", p->count, p->word);

    return 0;
}

struct key * binSearch(char *word, struct key tab[], int n){
    struct key *low = &tab[0];
    struct key *high = &tab[n];
    struct key *mid;
    int cond;

    while(low < high){
        mid = low + (high - low) / 2;
        if((cond = strcmp(word, mid->word)) < 0) high = mid;
        else if(cond > 0) low = mid + 1;
        else return mid;
    }

    return NULL;
}

int binSearch2(char *word, struct key tab[], int n){
    int low, high, mid;
    int cond;

    low = 0;
    high = n - 1;
    while(low <= high){
        mid = (low + high) / 2;
        if((cond = strcmp(word, tab[mid].word)) < 0) high = mid;
        else if(cond > 0) low = mid + 1;
        else return mid;
    }

    return -1;
}