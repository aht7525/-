#include <stdio.h>
#include <string.h>
#include <math.h>


#define MAXOP 100
#define NUMBER '0'
#define IDENTIFIER 'a'

double atof(char s[]);
int getop(char s[]);
void push(double f);
double pop(void);

int main(void){
    int type;
    char s[MAXOP];
    float op2;

    while((type = getop(s)) != EOF){
        switch(type){
            case NUMBER:
                push(atof(s));
            case IDENTIFIER:
                if(strcmp(s, "sin") == 0)
                    push(sin(pop()));
                else if((strcmp(s, "cos")) == 0)
                    push(cos(pop()));
                else if((strcmp(s, "exp")) == 0)
                    push(exp(pop()));
                else if((strcmp(s, "pow")) == 0){
                    op2 = pop();
                    push(pow(pop(), op2));
                } else
                    printf("%s is not a supported function.\n", s);
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if(op2 != 0.0)
                    push(pop() - op2);
                else
                    printf("Error : zero divisor\n");
                break;
            case '\n':
                printf("%.8g\n", pop());
                break;
            default:
                printf("Error : Unknown Command %s\n",s);
                break;
        }
    }
    return 0;
}