# SSOS-Lab
Programs for the System Software and Operating Systems Laboratory.
Tools/Languages:
- Lex
- Yacc
- C/C++
- Java

## Lex:
- lex pgm.l
- gcc lex.yy.c -ll
- .a/.out

## Yacc
- yacc -d pgm.y
- lex pgm.l
- gcc lex.yy.c y.tab.c -ll
- ./a.out
