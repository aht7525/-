#include <stdio.h>

void writeLines(char *lines[], int n){
    while(n-- > 0)
        printf("%s\n",*lines++);
}

void writeLines2(char *lines[], int n){
    int i;

    for(i = 0; i < n; i++)
        printf("%s\n",lines[i]);
}