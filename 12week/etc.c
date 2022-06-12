#include <stdio.h>

int strlen(char s[]);
int strlen(char s[]){
    int i = 0;
    while(s[i] != '\0')
        i++;
    return i;
}
int strlen2(char *s){
    int n;
    for(n = 0; *s != '\0'; s++)
        n++;
    return n;
}

int strcmp(char *s, char *t){
    int i;
    for(i = 0; s[i] == t[i]; i++)
        if(s[i] == '\0')
            return 0;
    return s[i] - t[i];
}

void strcpy(char *s, char *t){
    int i;
    i = 0;
    while((s[i] = t[i]) != '\0')
        i++;
}

void strcpy2(char *s, char *t){
    while((*s = *t) != '\0'){
        s++;
        t++;
    }
}

int main(int argc, char *argv[]){
    while(--argc > 0)
        printf("%s%s", *++argv, (argc > 1) ? " " : "");
}

int main(int argc, char *argv[]){
    int i;
    for(i = 1; i < argc; i++)
        printf("%s%s", argv[i], (i < argc - 1) ? " " : "");
}


#define MAXCHAR 1000
int main(int argc, char *argv[]){
    char line[MAXCHAR];
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;

    while(--argc > 0 && (*++argv)[0] == '-')
        while(c = *++argv[0]){
            switch(c){
                case 'x' : except = 1; break;
                case 'n' : number = 1; break;
                default:
                    printf("Find : illegal option %c\n",c);
                    argc = 0; found = -1; break;
            }
        }
    if(argc != 1)
        printf("Usage : find [-x -n] pattern\n");
    else
        while(fgets(line, MAXCHAR, stdin) != (char *) NULL){
            lineno++;
            if(((strstr(line, *argv)) != (char *) NULL) != except){
                if(number) printf("%ld:", lineno);
                printf("%s",line);
                found++;
            }
        }
    return(found);
}

int strIndex(char s[], char t[]){
    int i, j, k;
    for(i = 0; s[i] != '\0'; i++){
        for(j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
        if(k > 0 && t[k] == '\0') return i;
    }
}


#define MAXLINE 5000
int main(int argc, char *argv[]){
    char *lines[MAXLINE];
    int n, numeric = 0;

    if(argc > 1 && strcmp(argv[1], "-n") == 0) numeric = 1;
    if(n = readLines(lines, MAXLINE) >= 0){
        qSort((void **) lines, 0, n - 1, (int (*) (const char *, const char *)) (numeric ? numcmp : strcmp));
        writeLines(lines, n);
        return 0;
    }else{
        printf("Error : input too big to sort\n");
        return 1;
    }
}
static int numcmp(const char *s1, const char *s2){
    double v1, v2;
    
    v1 = atof(s1);
    v2 = atof(s2);
    if(v1 < v2) return -1;
    else if(v1 > v2) return 1;
    else return 0;
}