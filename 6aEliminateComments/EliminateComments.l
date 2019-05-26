%{
#include<stdio.h>
int sl=0, ml=0;    
%}
%%
"/*"['//'a-zA-Z0-9' '\t\n]+"*/" {ml++;}
"//".* {sl++;}
%%
int main(int argc, char *argv[])
{
    yyin = fopen(argv[1],"r");
    yyout = fopen(argv[2],"w");
    yylex();
    fclose(yyin);
    fclose(yyout);
    printf("\nNumber of single line comments: %d\n",sl);
    printf("\nNumber of multi line comments: %d\n",ml);
    return 0;
}