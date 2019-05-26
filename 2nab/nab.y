%{
#include<stdio.h>
#include<stdlib.h>
int c=0;
int n;
%}
%token A B;
%%
expr:inp B;
inp:inp A {c++;}
|
;
%%
int yyerror()
{
    printf("\nInvalid! Not a part of language\n");
    exit(0);
}
int main()
{
    printf("\nEnter the string:\n");
    yyparse();
    printf("\nEnter the n value:\n");
    scanf("%d",&n);
    if(c==n)
    printf("\nValid\n");
    else
    printf("\nInvalid\n");
    return 0;
}
