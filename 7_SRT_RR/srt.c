#include<stdio.h>
int main(){
    int a[10], b[10], x[10];
    int w[10], t[10], c[10];
    int i, j, smallest, time, n, count=0;
    double avg=0.0, tt=0.0, end;

    printf("\nEnter the number of processes: ");
    scanf("%d",&n);

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

    for(i=0; i<n; i++)
        x[i] = b[i];

    b[9] = 9999;

    for(time=0; count!=n; time++){
        smallest = 9;

        for(i=0; i<n; i++){
            if(a[i]<=time && b[i]<b[smallest] && b[i]>0)
                smallest = i;
        }

        b[smallest]--;

        if(b[smallest]==0){
            count++;
            end = time+1;
            c[smallest] = end;
            w[smallest] = end - a[smallest] - x[smallest];
            t[smallest] = end - a[smallest];
        }
    }

    printf("PID  Burst  Arrival  Waiting  Turnaround  Completion");
    for(i=0; i<n; i++){
        printf("\n%d \t%d \t%d \t%d \t%d \t  %d", i+1, x[i], a[i], w[i], t[i], c[i]);
        avg = avg + w[i];
        tt = tt + t[i];
    }

    printf("\n\nTotal waiting time =  %lf",avg);
    printf("\nTotal turnaround time =  %lf",tt);
    printf("\n\nAverage waiting time = %lf",avg/n);
    printf("\nAverage Turnaround time = %lf\n",tt/n);

    return 0;
}