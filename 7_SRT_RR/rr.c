#include<stdio.h>
int main(){
    int a[10], b[10], x[10], c[10];
    int w=0, t=0;
    int i, n, total=0, temp, counter=0, tq;
    float avg=0.0, tt=0.0;

    //Accept no of processes, arrival times, burst times, time quantum
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);
    temp = n;

    printf("\n");
    for(i=0; i<n; i++){
        printf("Enter the arrival time of process %d : ",i+1);
        scanf("%d",&a[i]);
    }

    printf("\n");
    for(i=0; i<n; i++){
        printf("Enter the burst time of process %d : ",i+1);
        scanf("%d",&b[i]);
    }

    //create copy of burst times x=n
    for(i=0; i<n; i++)
        x[i] = b[i];

    printf("\nEnter the Time Quantum : ");
    scanf("%d", &tq);

    printf("PID  Burst  Arrival  Waiting  Turnaround  Completion");
    for(total=0,i=0; temp!=0;){
        //if burst time less than time quantum
        if(x[i]<=tq && x[i]>0){
            total = total + x[i];
            x[i] = 0;
            counter = 1; //ready to be printed
        }
        //if burst time greater than time quantum
        else if(x[i]>0){
            x[i] = x[i] - tq;
            total = total + tq;
        }

        //if some process has completed
        if(x[i]==0 && counter==1){
            temp--;
            c[i] = total;
            printf("\nP[%d]\t %d\t %d\t %d\t %d\t %d", i+1, b[i], a[i], total-a[i]-b[i], total-a[i], c[i]);
            w += total - a[i] - b[i];
            t += total - a[i];
            counter = 0;
        }

        //loop around
        if(i == n-1)
            i=0;
        else if(a[i+1] <= total)
            i++;
        else
            i=0;  
    }

    avg = w * 1.0 / n;
    tt = t * 1.0 / n;

    printf("\n\nAverage Waiting Time:\t%f", avg); 
    printf("\nAvg Turnaround Time:\t%f\n", tt); 
    return 0; 
}