#include<stdio.h>
#define MAX 20

int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
int avail[MAX];
int p, r, k, pnum;
int result[MAX], work[MAX], finish[MAX];

void input()
{
    int i,j;
    printf("Bankers Algorithm!");
    printf("\nEnter the number of processes: ");
    scanf("%d", &p);
    printf("\nEnter the number of resources: ");
    scanf("%d", &r);

    printf("\nEnter the allocated resources for each process: \n");
    for(i=0; i<p; i++)
    {
        for(j=0; j<r; j++)
        {
            scanf("%d",&alloc[i][j]);
        }
    }

    printf("\nEnter the maximum resources for each process: \n");
    for(i=0; i<p; i++)
    {
        for(j=0; j<r; j++)
        {
            scanf("%d",&max[i][j]);
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    printf("\nEnter the available resources: ");
    for(j=0; j<r; j++)
    {
        scanf("%d", &avail[j]);
        work[j] = -1;
    }

    for(i=0; i<p; i++)
        finish[i]=0;
}

int search(int i)
{
    int j;
    for(j=0; j<r; j++)
        if(need[i][j]>avail[j])
            return -1;
    return 0;
}

void method()
{
    int i=0,j,flag=0;
    while(1)
    {
        if(finish[i]==0)
        {
            pnum = search(i);
            if(pnum!= -1)
            {
                result[k++]=i;
                finish[i]=1;
                for(j=0; j<r; j++)
                {
                    avail[j]=avail[j]+alloc[i][j];
                }
            }
        }
        i++;
        if(i==p)
        {
            flag=0;
            for(j=0; j<r; j++)
                if(avail[j]!=work[j])

            flag=1;
            for(j=0; j<r; j++)
                work[j]=avail[j];

            if(flag==0)
                break;
            else
                i=0;
        }
    }
}

void display()
{
    int i,j;
    int temp;
    int flag = 0;

    printf("\nThe need matrix is: \n");
    for(i=0; i<p; i++)
    {
        for(j=0; j<r; j++)
        {
            printf("%d ",need[i][j]);
        }
        printf("\n");
    }
    
    for (i=0; i<p; i++)
    {
        if(finish[i]==0)
        {
            flag=1;
        }
    }

    if(flag==1)
        printf("\n\nThe system is not in safe state and deadlock may occur!!");
    else
    {
        printf("\n\nThe system is in safe state and deadlock will not occur!!");
        printf("\nThe safe state sequence is: ");
        for(i=0; i<k; i++)
        {
            temp = result[i] + 1;
            printf("P%d ",temp);
        }
        printf("\n");
    }
}

int main()
{
    int i,j;
    k = 0;
    for(i=0; i<MAX; i++)
    {   
        for(j=0; j<MAX; j++)
        {
            alloc[i][j] = 0;
            max[i][j] = 0;
            need[i][j] = 0;
        }
        avail[i] = 0;
        result[i] = 0;
        finish[i] = 0;
    }

    input();
    method();
    display();

    return 0;
}