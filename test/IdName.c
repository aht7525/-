#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

typedef struct idn {
    char *id;
    char *name;
} IdName;

#define HASHSIZE 2503
#define MAXLINE 1000
#define MAXWORD 100
#define MAXARGS 3
#define MAXNAMEID 20000

static char *getName(void *object);
static char *getId(void *object);
static void addStudent(char *id, char *name);
static void removeStudent(IdName *pIdName);
static HashTable *ByName, *ById;

static int NumStudents = 0;
static IdName Students[MAXNAMEID];

int main(int argc, char *argv[]){

    char line[MAXLINE];
    char arg[MAXARGS][MAXWORD];
    int n, i;

    IdName *pIdName;
    FILE *fp;

    ByName = createHash(HASHSIZE, getName);
    ById = createHash(HASHSIZE, getId);

    while(fgets(line, MAXLINE, stdin) != (char *) NULL){
        n = sscanf(line,"%s%s%s",arg[0],arg[1],arg[2]);
        if(n < 1) continue;
        if(strcmp(arg[0],"read") == 0){
            if(n != 2){
                printf("read a file name expected.\n"); continue;
            }
            if((fp = fopen(arg[1],"r")) == (FILE *) NULL){
                printf("read : can't open file \"%s\".\n",arg[1]); continue;
            }
            for(i = 1; fgets(line,MAXLINE,fp) != (char *) NULL; i++){
                if((n = sscanf(line,"%s%s",arg[0],arg[1])) != 2){
                    printf("read : format error in line %d.\n",i);continue;
                }
                //printf("%s %s\n",arg[0],arg[1]);
                addStudent(arg[0],arg[1]);
            }
            fclose(fp);
        }else if(strcmp(arg[0],"write") == 0){
            if(n != 2){
                printf("write : a file name expected.\n");
                continue;
            }
            if((fp = fopen(arg[1],"w")) == (FILE *) NULL){
                printf("write : can't open file \"%s\".\n", arg[1]);
            }
            for(pIdName = Students; pIdName < Students + NumStudents; pIdName++){
                fprintf(fp, "%s\t%s\n", pIdName->id, pIdName->name);
            }
            fclose(fp);
        }else if(!strcmp(arg[0],"name")){
            if(n != 2){
                printf("name : a name expected.\n"); continue;
            }
            if(!(pIdName = (IdName *) lookUpHash(ByName, arg[1]))){
                printf("name : unknown name \"%s\".\n",arg[1]); continue;
            }
            printf("%s\t%s\n",pIdName->id,pIdName->name);
        }else if(!strcmp(arg[0], "id")){
             if(n != 2){
                printf("id : a id expected.\n"); continue;
            }
            if(!(pIdName = (IdName *)lookUpHash(ById, arg[1]))){
                printf("id : unknown id \"%s\".\n",arg[1]); continue;
            }  
            printf("%s\t%s\n",pIdName->id,pIdName->name);
        }else if(!strcmp(arg[0],"add")){
            if(n != 3){
                printf("add : an id-name pair expected.\n");
                continue;
            }
            addStudent(arg[1], arg[2]);
        }else if(!strcmp(arg[0],"remove")){
            if(n != 3){
                printf("remove : usage : remove (name|id) pattern\n"); continue;
            }
            if(!strcmp(arg[1], "id")){
                if(!(pIdName = (IdName *)lookUpHash(ById, arg[2]))){
                    printf("remove : unknown id \"%s\".\n", arg[2]);continue;
                }
                removeStudent(pIdName);
            }
            if(!strcmp(arg[1], "name")){
                if(!(pIdName = (IdName *) lookUpHash(ByName, arg[2]))){
                    printf("remove : unknown name \"%s\".\n", arg[2]);continue;
                }
                removeStudent(pIdName);
            } 
        }else if(!strcmp(arg[0], "quit")){
            break;
        }else if(!strcmp(arg[0], "exit"))
            break;
        else{
            printf("Unknown command.\nCommand : read, write, name, id, add, remove\n");
        }
    }
}

static void addStudent(char *id, char *name){
    IdName *pIdName;

    if(lookUpHash(ById, id)){
        printf("add : id %s already exists.\n", id); return;
    }
    if(lookUpHash(ByName, name)){
        printf("add : name %s already exists.\n", name); return;
    }

    pIdName = Students + NumStudents++;
    pIdName->id = strdup(id);
    pIdName->name = strdup(name);
    installHash(ByName, (void *) pIdName);
    installHash(ById, (void *) pIdName);
}

static void removeStudent(IdName *pIdName){
    IdName *pIdName2;

    uninstallHash(ByName, pIdName->name);
    uninstallHash(ById, pIdName->id);
    free((void *) pIdName->name);
    free((void *) pIdName->id);
    pIdName2 = Students + --NumStudents;
    pIdName->name = pIdName2->name;
    pIdName->id = pIdName2->id;
}

static char *getName(void *object){
    return(((IdName *) object)->name);
}

static char *getId(void *object){
    return(((IdName *) object)->id);
}