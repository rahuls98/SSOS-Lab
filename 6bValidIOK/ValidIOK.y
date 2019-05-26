%{
#include<stdio.h>
#include<stdlib.h>
int id=0,op=0,key=0;    
%}
%token ID OP KEY
%%
input:ID input {id++;}
|OP input {op++;}
|KEY input {key++;}
|ID {id++;}
|OP {op++;}
|KEY {key++;}
;
%%
extern FILE* yyin;

int yyerror()
{
    printf("\nParse Error!");
    exit(0);
}
int main()
{
    FILE* myfile = fopen("in.c","r");
    if(!myfile){
        printf("Can't open file!!");
        return -1;
    }
    yyin = myfile;
    do{
        yyparse();
    }
    while(!feof(yyin));

    printf("\nIdentifiers:%d\nOperators:%d\nKeywords:%d\n",id,op,key);
    return 0;
}