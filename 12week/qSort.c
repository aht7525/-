#include <stdio.h>
#include <string.h>

static void swap(void *v[], int i, int j);

void qSort(void *v[], int left, int right, int (*cmp) (const char *, const char *)){
    int last, i;

    if(left >= right) return;

    swap(v, left, (left + right) / 2)
    last = left;
    for(i = left + 1; i <= right; i++)
        if((* cmp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qSort(v, left, last - 1, cmp);
    qSort(v, last + 1, right, cmp);
}

static void swap(void *v[], int i, int j){
    char *t;

    t = v[i];
    v[i] = v[j];
    v[j] = t;
}