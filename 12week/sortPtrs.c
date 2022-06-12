#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXLINE 5000

int readLines(char *lines[], int max);
void writeLines(char *lines[], int n);
void qSort(void *lines[], int left, int right, int (*cmp) (const void *, const void *));

static int punctUpCmp(const char *s1, const char *s2);
static int punctDownCmp(const char *s1, const char *s2);
static int lenUpCmp(const char *s1, const char *s2);
static int lenDownCmp(const char *s1, const char *s2);

int main(int argc, char *argv[]){
    char *lines[MAXLINE];
    int n, c, down = 0, punct = 0;
    
    int (* cmp) (const char *s1, const char *s2);

    while(--argc > 0 && (*++argv)[0] == '-')
        while(c = *++argv[0])
            switch(c){
                case 'd' : down = 1; break;
                case 'p' : punct = 1; break;
                default : printf("sortPtrs : illegal option %c\n", c); break;
            }
    if(argc != 0)
        printf("Usage : sortPtrs [-d] [-p]\n");
    else{
        if(punct) cmp = down ? punctDownCmp : punctUpCmp;
        else cmp = down ? lenDownCmp : lenUpCmp;
    }

    if((n = readLines(lines, MAXLINE)) >= 0){
        qSort((void **) lines, 0, n - 1, (int (*) (const void *, const void *)) cmp);
        writeLines(lines, n);
        return 0;
    }else{
        printf("Error : input too big to sort\n");
        return 1;
    }
}

static int punctUpCmp(const char *s1, const char *s2){
    int n1 = 0, n2 = 0;
    while(*s1) {if(ispunct(*s1)) n1++; s1++; }
    while(*s2) {if(ispunct(*s2)) n2++; s2++; }
    return(n1 - n2);
}

static int punctDownCmp(const char *s1, const char *s2){
    int n1 = 0, n2 = 0;
    while(*s1) { if(ispunct(*s1)) n1++; s1++; }
    while(*s2) { if(ispunct(*s2)) n2++; s2++; }
    return(n2 - n1);
}

static int lenUpCmp(const char *s1, const char *s2){
    return strlen(s1) - strlen(s2);
}

static int lenDownCmp(const char *s1, const char *s2){
    return strlen(s2) - strlen(s1);
}