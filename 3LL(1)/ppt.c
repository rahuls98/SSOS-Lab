#include <stdio.h>
#include <string.h>

typedef struct Terminal
{
    char r1[10];
    char r2[10];
    char first[10];
    char follow[10];
    int ft;
    int fot;
    char table[2][10];
} Term;

Term r[2];
char* ip="abba$";
int ipr = 0;
char stack[20];
int stop=-1;

int isterminal(char c)
{
    int comp = (int)c;
    if((comp>=97 && comp<=122) || comp==51)
        return 1;
    return 0;
}

void calfirst(int rno)
{
    int i;
    for(i=2;r[rno].r1[i]!='\0';i++)
    {
        if(isterminal(r[rno].r1[i]))
        {
            r[rno].ft++;
            r[rno].first[r[rno].ft]=r[rno].r1[i];
            r[rno].first[r[rno].ft+1]='\0';
            break;
        }
    }
    if (rno==1)
    {
        for(i=2;r[rno].r2[i]!='\0';i++)
        {
            if(isterminal(r[rno].r2[i]))
            {
                r[rno].ft++;
                r[rno].first[r[rno].ft]=r[rno].r2[i];
                r[rno].first[r[rno].ft+1]='\0';
                break;
            }
        }
    }
}

void calfollow(int rno)
{
    int i,j;
    if(rno==0)
    {
        r[rno].follow[++r[rno].fot]='$';
        r[rno].follow[r[rno].fot+1]='\0';
    }
    for(i=2;r[rno].r1[i]!='\0';i++)
    {
        if(r[rno].r1[i]=='A')
            j=0;
        if(r[rno].r1[i]=='B')
            j=1;
        if(r[rno].r1[i]=='A'||r[rno].r1[i]=='B')
        {
            if(isterminal(r[rno].r1[i+1]) && r[rno].r1[i+1]!='3')
            {
                r[j].follow[++r[j].fot]=r[rno].r1[i+1];
            }
            else
            {
                if(r[rno].r1[i+1]=='A')
                    strcat(r[j].follow,r[0].first);
                if(r[rno].r1[i+1]=='B')
                    strcat(r[j].follow,r[1].first);                
            }  
        }
    }
    for(i=2;r[rno].r2[i]!='\0';i++)
    {
         if(r[rno].r1[i]=='A')
            j=0;
        if(r[rno].r1[i]=='B')
            j=1;
        if(r[rno].r1[i]=='A'||r[rno].r1[i]=='B')
        {
            if(isterminal(r[rno].r2[i+1]) && r[rno].r2[i+1]!='3')
            {
                r[j].follow[++r[j].fot]=r[rno].r2[i+1];
            }
            else
            {
                if(r[rno].r2[i+1]=='A')
                    strcat(r[j].follow,r[0].first);
                if(r[rno].r2[i+1]=='B')
                    strcat(r[j].follow,r[1].first);                
            }  
        }
    }
}

void maketable(int rno)
{
    int i,j;
    for(i=0;r[rno].first[i]!='\0';i++)
    {
        switch(r[rno].first[i])
        {
            case 'a': j=0;
                    break;
            case 'b': j=1;
                    break;
            case '3': j=0;
        }
        if(r[rno].first[i]=='3')
        {
            strcpy(r[rno].table[j],r[rno].r2);
        }
        else
            strcpy(r[rno].table[j],r[rno].r1);
    }
}

void printstck()
{
    int i;
    for(i=stop;i>=0;i--)
    {
        printf("%c",stack[i]);
    }
}

void stackcall()
{
    int j,J;
    while(!(stack[stop]=='$' && ip[ipr]=='$'))
    {
        printf("Stack: ");
        printstck();
        printf("\tinput %s\t",ip+ipr);
        if(ip[ipr]=='a' && stack[stop]=='A')
        {
            printf("prod: %s\n",r[0].r1);
            stop--;
            stack[++stop]='a';stack[++stop]='B';stack[++stop]='a';
        }
        else if(stack[stop]=='B' && ip[ipr]=='b')
        {
            printf("prod: %s\n",r[1].r1);
            stop--;
            stack[++stop]='B';stack[++stop]='b';
        }
        else if(stack[stop]=='B' && ip[ipr]=='a')
        {
            printf("prod: %s\n",r[1].r2);
            stop--;
        }
        if((stack[stop]==ip[ipr])&&stack[stop]!='$')
        {
            stop--;
            ipr++;
        }
    }
    printf("Stack: $\tinput: $\tprod: \n");
    printf("String accepted.\n");
}

void main()
{
    strcpy(r[0].r1,"A=aBa");
    strcpy(r[1].r1,"B=bB");
    strcpy(r[1].r2,"B=3");
    strcpy(r[0].r2,"");
    r[0].fot=r[0].ft=r[1].fot=r[1].ft=-1;
    int i;
    for(i=0;i<2;i++)
    {
        calfirst(i);
    }
    printf("First of A %s \n",r[0].first);
    printf("First of B %s \n",r[1].first);
    for(i=0;i<2;i++)
    {
        calfollow(i);
    }
    printf("Follow of A %s \n",r[0].follow);
    printf("Folow of B %s \n",r[1].follow);
    for(i=0;i<2;i++)
    {
        maketable(i);
    }
    printf("M[A,a]= %s\n",r[0].table[0]);
    printf("M[B,a]= %s\n",r[1].table[0]);
    printf("M[B,b]= %s\n",r[1].table[1]);
    stack[++stop]='$';
    stack[++stop]='A';
    stackcall();
}