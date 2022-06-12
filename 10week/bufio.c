#include <stdio.h>

int getch(void);
void ungetch(int c);


#define BUFSIZE 100

static int bufp = 0;
static char buf[BUFSIZE];

int getch(void){
    return((bufp > 0) ? buf[--bufp] : getchar());
}

void ungetch(int c){
    if(bufp < BUFSIZE)
        buf[bufp++] = c;
    else
        printf("ungetch: too many characters\n");
}