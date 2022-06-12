#include <stdio.h>
#include <ctype.h>

#define MAXNUMBER 65535

void selectionsort(int v[], int n);
void insertionsort(int v[], int n);
void shellsort(int v[], int n);
void itoa(int n, char s[]);
void reverse(char s[]);
int atoi(char s[]);
int trim(char s[]);

int rand(void);
void srand(unsigned int seed);

int main(void){

}

unsigned long int next = 1;
int rand(void){
    next = next * 1103515245 + 12345;
    return (unsigned int) (next / 65536) % 32768;
}

void srand(unsigned int seed){
    next = seed;
}

void selectionsort(int v[], int n){
    int i,j,t,min;

    for(i = 0; i < n; i++){
        min = i;
        for(j = i + 1; j < n; j++)
            if(v[j] < v[min]) min = j;
        t = v[i];
        v[i] = v[min];
        v[min] = t;
    }
}

void insertionsort(int v[], int n){
    int i, j, t;

    for(i = 1; i < n; i++){
        for(j = i - 1; j >= 0 && v[j] > v[j + 1]; j--){
            t = v[j];
            v[j] = v[j + 1];
            v[j + 1] = t;
        }
    }
}

void shellsort(int v[], int n){
    int i, j, t, gap;

    for(gap = n / 2; gap > 0; gap /= 2)
        for(i = gap; i < n; i++)
            for(j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap){
                t = v[j];
                v[j] = v[j + gap];
                v[j + gap] = t;
            }
}

void itoa(int n, char s[]){
    int i, sign;
    if((sign = n) < 0)
        n = -n;
    i = 0;
    do{
        s[i++] = n % 10 + '0';
    }while((n /= 10) > 0);
    if(sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int trim(char s[]){
    int n;
    for(n = strlen(s) - 1; n >= 0; n--){
        if(s[n] != ' ' && s[n] != '\t'&& s[n] != '\n')
            break;
    }
    s[n+1] = '\0';
}

int atoi(char s[]){
    int i, n, sign;

    for(i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if(s[i] == '+' || s[i] == '-')
        i++;
    for(n = 0; isdigit(s[i]); i++)
        n = 10 * n + (s[i] - '0');
    return sign * n;
}

void reverse(char s[]){
    int c, i, j;

    for(i = 0, j = strlen(s) - 1; i < j; i++, j--){
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}