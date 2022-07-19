#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc,char* argv[]){
    if(argc == 3){
        FILE* fp = fopen(argv[1],"r");
        FILE* fp2 = fopen(argv[2],"r");
        unsigned char s1[100];
        unsigned char s2[100];
        uint32_t num1,num2;
        if(fp == NULL || fp2 == NULL){
            printf("스트림 생성시 오류 발생");
            return 1;
        }
        if(fread(s1,4,1,fp)!=1){
            printf("read error!\n");
            return 1;
        }
        if(fread(s2,4,1,fp2)!=1){
            printf("read error!\n");
            return 1;
        }
        num1 = s1[3]+s1[2]*0x100u+s1[1]*0x10000u+s1[0]*0x1000000u;
        num2 = s2[3]+s2[2]*0x100u+s2[1]*0x10000u+s2[0]*0x1000000u;
        printf("%d(%#x) + %d(%#x) = %d(%#x)",num1,num1,num2,num2,num1+num2,num1+num2);
    }else{
        printf("Usage : ./add-nbo txt1 txt2\n");
    }
    return 0;
}