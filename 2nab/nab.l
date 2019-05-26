%{
#include "y.tab.h"
extern int yylval;
%}
%%
[a] {yylval=yytext[0]; return A;}
[b] {yylval=yytext[0]; return B;}
\n {return 0;}
. {return yytext[0];}
%% 