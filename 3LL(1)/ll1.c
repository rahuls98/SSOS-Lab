//include libraries
#include<stdio.h>
#include<string.h>

//structure for each terminal : (2 rules, First, Follow, M)
typedef struct Terminal{
    char r1[10];
    char r2[10];
    char first[10];
    char follow[10];
    char M[2][10];
} Term;

//structure for 2 terminals : (A,B)
Term r[2];

//for stack operations
char* ip="abba$";
int ipr = 0;
char stack[20];
int stop=-1;

//returns true if character is a non terminal : (a,b,3)
int isterminal(char c){
    int comp = (int)c;
    if((comp>=97 && comp<=122) || comp==51)
        return 1;
    return 0;
}

//returns the character terminal based on loop index
char retT(int ind){
    if(ind==0)
        return 'a';
    else
        return 'b';
}

//returns the character non terminal based on loop index
char retNT(int ind){
    if(ind==0)
        return 'A';
    else
        return 'B';
}

//Find First(NT) : for r1 and r2 of each NT, check is there is a first.
void findFirsts(int rno){
    int j=0;
    //check if NT.r1 has a terminal after '='
    if(isterminal(r[rno].r1[2]))
        r[rno].first[j] = r[rno].r1[2];
        r[rno].first[j+1] = '\0';

    //check if NT.r2 has a terminal after '='
    if(isterminal(r[rno].r2[2]))
        r[rno].first[++j] = r[rno].r2[2];
        r[rno].first[j+1] = '\0';
}

//Find Follow(NT) : Append for the start symbol and find B in the body.
void findFollows(int rno){
    int j, i=0;

    if(rno==0)
    {
        //if rno => head
        r[rno].follow[i] = '$';
        r[rno].follow[i+1] = '\0';

        //go through body of A.r1 to find 'B'
        for(j=2; r[rno].r1[j]!='\0'; j++)
        {
            if(r[rno].r1[j] == 'B')
            {
                //check if character following the found B is a terminal
                if(isterminal(r[rno].r1[j+1]))
                {
                    //follow(B) = previously checked character
                    r[1].follow[i] = r[rno].r1[j+1];
                    r[1].follow[i+1] = '\0';
                }
            }
        }
    }
}

//To create the M table
void method(){
    int i,j;

    //for each NT and its 2 rules
    for(i=0; i<2; i++)
    {
        for(j=0; r[i].first[j]!='\0'; j++)
        {
            //for A, order : r1, r2
            if(i==0){
                //copy the corresponding rule according to the T
                if(j==0)
                    strcpy(r[i].M[j] , r[i].r1);
                else
                    strcpy(r[i].M[j] , r[i].r2);
            }
            //for B, order : r2, r1
            else{
                if(j==0)
                    strcpy(r[i].M[j] , r[i].r2);
                else
                    strcpy(r[i].M[j] , r[i].r1);
            }
        }
    }
}

//Print contents of symbol stack
void printstck(){
    int i;
    for(i=stop;i>=0;i--)
    {
        printf("%c",stack[i]);
    }
}

//perform the parsing operations using the stack
void stackcall(){
    int j,J;
    //until only '$' is left in both
    while(!(stack[stop]=='$' && ip[ipr]=='$'))
    {
        //print symbol stack
        printf("Stack: ");
        printstck();
        //print input
        printf("\tinput %s\t",ip+ipr);
        //M[A,a] copied onto symbol stack character wise
        if(ip[ipr]=='a' && stack[stop]=='A')
        {
            printf("prod: %s\n",r[0].r1);
            stop--;
            stack[++stop]='a';stack[++stop]='B';stack[++stop]='a';
        }
        //M[B,b] copied onto symbol stack character wise
        else if(stack[stop]=='B' && ip[ipr]=='b')
        {
            printf("prod: %s\n",r[1].r1);
            stop--;
            stack[++stop]='B';stack[++stop]='b';
        }
        //M[B,a] : epsilon so no need to copy onto stack
        else if(stack[stop]=='B' && ip[ipr]=='a')
        {
            printf("prod: %s\n",r[1].r2);
            stop--;
        }
        //check if tops are the same and not the end of symbol stack
        if((stack[stop]==ip[ipr])&&stack[stop]!='$')
        {
            stop--;
            ipr++;
        }
    }
    printf("Stack: $\tinput: $\tprod: \n");
    printf("String accepted.\n");
}

void display(){
    int i=0, j=0, k=0;
    //print First(NT)
    for(i=0;i<2;i++){
    printf("First(%c) : ",retNT(i));
        for(j=0; r[i].first[j]!='\0'; j++){
            printf("%c ",r[i].first[j]);
        }
        printf("\n");
    }

    //print FOllow(NT)
    printf("\n");
    for(i=0;i<2;i++){
    printf("Follow(%c) : ",retNT(i));
        for(j=0; r[i].follow[j]!='\0'; j++){
            printf("%c ",r[i].follow[j]);
        }
        printf("\n");
    }

    //Print M[NT,T]
    printf("\n");
    for(i=0;i<2;i++){
        for(j=0; j<2; j++){
            printf("M[%c,%c] : ", retNT(i), retT(j));
            printf("%s",r[i].M[j]);
            printf("\n");
        }
    }
    printf("\n");

}

void main(){
    int i = 0;
    //Load rules
    strcpy(r[0].r1 , "A=aBa");
    strcpy(r[0].r2,"\0");
    strcpy(r[1].r1 , "B=bB");
    strcpy(r[1].r2,"B=3");

    for(i=0; i<2; i++)
        findFirsts(i);
    
    for(i=0; i<2; i++)
        findFollows(i);

    method();
    display();

    //Load symbol stack
    stack[++stop]='$';
    stack[++stop]='A';
    stackcall();
}

