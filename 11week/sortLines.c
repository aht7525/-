#include <stdio.h>
#include <string.h>

#define MAXLINE 5000

int readLines(char *lines[], int max);
void writeLines(char *lines[], int n);
void qSort(char *lines[], int left, int right);

int main(void){
    char *lines[MAXLINE];
    int n;

    if((n = readLines(lines, MAXLINE)) >= 0){
        qSort(lines, 0, n - 1);
        writeLines(lines, n);
        return 0;
    }else{
        printf("Error : input too big to sort\n");
        return -1;
    }
}