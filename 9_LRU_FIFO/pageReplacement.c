#include<stdio.h>
int n,nf; //seq length and no. of frames
int in[100]; //seq string
int p[50]; //page
int hit=0;
int i,j,k;
int avail;
int PgFaultCnt=0;

//Get the seq length, seq string and no. of frames 
void getData()
{
    printf("\nEnter length of page reference sequence:");
    scanf("%d",&n);
    printf("\nEnter the page reference sequence:");
    for(i=0; i<n; i++)
        scanf("%d",&in[i]);
    printf("\nEnter no of frames:");
    scanf("%d",&nf);
}

//set frame contents to 9999
void initialize()
{
    PgFaultCnt=0;
    for(i=0; i<nf; i++)
        p[i]=9999;
}

//check if the current item is already present in any of the frames 
int isHit(int data)
{
    hit=0;
    for(j=0; j<nf; j++)
    {
        if(p[j]==data)
        {
            hit=1;
            break;
        }
    }
    return hit;
}

//display each contents of pages
void dispPages()
{
    for (k=0; k<nf; k++)
    {
        if(p[k]!=9999)
            printf(" %d",p[k]);
    }
 
}

//display the page fault count
void dispPgFaultCnt()
{
    printf("\nTotal no of page faults:%d",PgFaultCnt);
}

//fifo page replacement
void fifo()
{
    initialize();
    int pos=0;
    
    //run through the sequence
    for(i=0; i<n; i++)
    {
        printf("\nFor %d :",in[i]);
        //Replace if no hit
        if(isHit(in[i])==0)
        {
            p[pos]=in[i];
            pos=(pos+1)%nf;
            PgFaultCnt++;
            dispPages();
        }
        //Else no page fault
        else
            printf("No page fault!");
    }
    dispPgFaultCnt();
}

//lru page replacement
void lru()
{
    initialize();
 
    int least[50];
    //run through the sequence
    for(i=0; i<n; i++)
    {
        printf("\nFor %d :",in[i]);
        //replace if no hit
        if(isHit(in[i])==0)
        {
            //go through frame elements
            for(j=0; j<nf; j++)
            {
                //check which element(pg) is least recently used
                int pg=p[j];
                int found=0;
                for(k=i-1; k>=0; k--)
                {
                    if(pg==in[k])
                    {
                        least[j]=k;
                        found=1;
                        break;
                    }
                    else
                        found=0;
                }
                if(!found)
                    least[j]=-9999;
            }
            //check which frame element(j) has the least value
            int min=9999;
            int repindex;
            for(j=0; j<nf; j++)
            {
                if(least[j]<min)
                {
                    min=least[j];
                    repindex=j;
                }
            }
            p[repindex]=in[i];
            PgFaultCnt++;
 
            dispPages();
        }
        else
            printf("No page fault!");
    }
    dispPgFaultCnt();
}

int main()
{
    int choice;
    while(1)
    {
        printf("\n\nPage Replacement Algorithms\n1.Enter data\n2.FIFO\n3.LRU\n4.Exit\nEnter your choice:");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            getData();
            break;
        case 2:
            fifo();
            break;
        case 3:
            lru();
            break;
        default:
            return 0;
            break;
        }
    }
}