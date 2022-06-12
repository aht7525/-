#include <stdio.h>
#include <string.h>

static void swap(char *v[], int i, int j);
static int strsumcmp(char *sl, char *s2);

void qSort(char *v[], int left, int right){
    int last, i;

    if(left >= right) return;

    swap(v, left, (left + right) / 2);
    last = left;

    for(i = left + 1; i <= right; i++)
        if(strsumcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qSort(v, left, last - 1);
    qSort(v, last + 1, right);
}

static void swap(char *v[], int i, int j){
    char *t;

    t = v[i];
    v[i] = v[j];
    v[j] = t;
}

static int strsumcmp(char *s1, char *s2){
    int sum1 = 0, sum2 = 0;
    while(*s1) sum1 += *s1++;
    while(*s2) sum2 += *s2++;
    return sum1 - sum2;
}