#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>
int top=-1;
int i=0;
char input[20]; char stack[20]; char action[20];

void printfn()
{
    int j;
    for(j=0;j<=top;j++) 
        printf("%c",stack[j]);
    printf("\t%s",input); 
    printf("\t%s",action); 
    printf("\n");
}

void check()
{
    while(1)
    {
        if(stack[top]=='T' && stack[top-1]=='+' && stack[top-2]=='E')
        {
            if(input[i+1]=='*')
                break; 
        }
        if(stack[top]=='T')
        {
            if(input[i+1]=='*')
                break; 
        }
        if(stack[top]=='F' && stack[top-1]=='*' && stack[top-2]=='T')
        {
            strcpy(action,"Reduce T->T*F"); 
            stack[--top]=' '; 
            stack[--top]='T';
            printfn();
        }
        if(stack[top]=='T' && stack[top-1]=='+' && stack[top-2]=='E')
        {
            strcpy(action,"Reduce E->E+T"); 
            stack[--top]=' ';
            stack[--top]='E';
            printfn();
        }
        if(stack[top]=='d' && stack[top-1]=='i')
        {
            strcpy(action,"Reduce F->id"); 
            stack[--top]='F';
            printfn();
        }
        else if(stack[top]=='F')
        {
            strcpy(action,"Reduce T->F"); stack[top]='T';
            printfn();
        }
        else if(stack[top]=='T')
        {
            strcpy(action,"Reduce E->T"); stack[top]='E';
            printfn();
        }
        else if(stack[top]=='E' || stack[top]=='*' || stack[top]=='+')
        {
            break;
        } 
    }
}

int main()
{
    printf("GRAMMAR is \nE->E+T|T \nT->T*F|F \nF->id|(E) \n"); 
    printf("Enter the sentence\n");
    scanf("%s",input);
    input[8] ='$';
    printf("Stack\tInput\tAction\n"); 
    printf("---\t%s\t---\n",input);
    
    for(i=0;input[i]!='$';i++)
    {
        if(input[i]=='i' && input[i+1]=='d')
        {
            input[i]=' ';
            input[i+1] =' '; 
            stack[++top] ='i'; 
            stack[++top]='d';
            i=i+1; 
            strcpy(action,"Shift id"); 
            printfn();
            check(); 
        }
        if(input[i]=='*')
        {
            input[i]=' ';
            stack[++top]='*'; 
            strcpy(action,"Shift *"); 
            printfn();
            check();
        } 
        if(input[i]=='+')
        {
            input[i]=' ';
            stack[++top]='+'; 
            strcpy(action,"Shift +"); 
            printfn();
            check();
        } 
    }
    return 0; 
}