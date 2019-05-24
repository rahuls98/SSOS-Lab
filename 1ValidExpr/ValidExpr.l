%{
#include<stdio.h>
int v=0, op=0, id=0, flag=0;
%}
%%
[0-9]+ {id++; printf("\nIdentifier: "); ECHO;}
[\+\*] {op++; printf("\nOperator: "); ECHO;}
"(" {v++;}
")" {v--;}
.|\n {;}
';' {flag=1;}
%%
void main()
{
    printf("Enter the expression: ");
    yylex();
    printf("\n\nNumber of identifiers = %d",id);
    printf("\nNumber of operators = %d",op);
    if((op+1)==id && v==0 &&flag==0)
        printf("\nExpression is valid\n");
    else
        printf("\nExpression is invalid\n");
}