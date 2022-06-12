#include <stdio.h>

void writeLines(char *lines[], int n){
    while(n-- > 0)
        printf("%s\n",*lines++);
}