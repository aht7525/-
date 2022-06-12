#include <stdio.h>
#include <ctype.h>

#define NUMBER '0'
#define IDENTIFIER 'a'

int getch(void);
void ungetch(int);

int getop(char s[]){
    int i, c;

    while(((s[0] = c = getch()) == ' ') || (c == '\t'));
    s[1] = '\0';
    if(isalpha(c)){
        i = 0;
        while(isalpha(s[++i] = c = getch()));
        s[i] = '\0';
        if(c != EOF) ungetch(c);
        return IDENTIFIER;
    }
    if(!isdigit(c) && c != '.') return c;

    i = 0;
    if(isdigit(c))
        while(isdigit(s[++i] = c = getch()));
    if(c == '.')
        while(isdigit(s[++i] = c = getch()));
    s[i] = '\0';

    if(c != EOF) ungetch(c);

    return NUMBER;
}

int getint(int *pn){
    int c, sign;

    while(isspace(c = getch()))
        ;
    if(!isspace(c) && c != EOF && c != '+' && c != '-'){
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if(c == '+' || c == '-')
        c = getch();
    for(*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if(c != EOF)
        ungetch(c);
    return c;
}