#include <stdio.h>

void push(double f);
double pop(void);

#define MAXVAL 100

static int sp = 0;
static double val[MAXVAL];

void push(double f){
    if(sp < MAXVAL)
        val[sp++] = f;
    else
        printf("Error : stack full, can't push %g\n",f);
}

double pop(void){
    if(sp > 0)
        return(val[--sp]);
    else{
        printf("Error : stack empty\n");
        return 0.0;
    }
}