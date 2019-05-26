%{
#include<stdio.h>
#include "y.tab.h"
extern yylval;    
%}
%%
[\t] ;
[+|-|*|/|=|<|>] {printf("\nOperator: "); ECHO; return OP;}
int|char|bool|float|void|for|do|while|if|else|return|include|main|printf {printf("\nKeyword: "); ECHO; return KEY;}
[0-9a-zA-Z]+ {printf("\nIdentifier: "); ECHO; return ID;}
. {;}
%%