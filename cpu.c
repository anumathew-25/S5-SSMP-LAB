/*************************************************
 * File         :cpu.c
 * Description  :C program to implement cpu scheduling algorithms
 * Author       :Anu Mathew
 ************************************************/
#include<stdio.h>
void print(int);
void fcfs(int);
void sjf(int);
void priority(int);
void roundrobin(int);

struct cpuScheduling{
    int no;
    int burst;
    int burstCopy;
    int waiting;
    int turnaround;
    int priority;
};struct cpuScheduling  p[10],temp;

void fcfs(int n){
    int i,com;
    float totalTurn=0,totalWait=0,avgT,avgW;
    com=0;
    for(i=0;i<n;i++){
        com+=p[i].burst;
        p[i].turnaround=com;
        p[i].waiting=com-p[i].burst;
    }
    printf("Gantt Chart\n");
    printf("0");
    for(i=0;i<n;i++){
        printf("[%d] %d",p[i].no,p[i].turnaround);
    }
    printf("\n");
    print(n);
    for(i=0;i<n;i++){
        totalTurn+=p[i].turnaround;
        totalWait+=p[i].waiting;
    }
    avgT=totalTurn/n;
    avgW=totalWait/n;
    printf("Average turn around time: %.2f\n",avgT);
    printf("Average waiting time: %.2f\n",avgW);
}

void sjf(int n){
    int i,j,com;
    float totalTurn=0,totalWait=0,avgT,avgW;
    for(i=0;i<n;i++){
        for(j=0;j<n-i-1;j++){
            if(p[j].burst>p[j+1].burst){
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
    com=0;
    for(i=0;i<n;i++){
        com+=p[i].burst;
        p[i].turnaround=com;
        p[i].waiting=com-p[i].burst;
    }
    printf("Gantt chart\n");
    printf("0");
    for(i=0;i<n;i++){
        printf("[%d] %d ",p[i].no,p[i].turnaround);
    }
    printf("\n");
    print(n);
    for(i=0;i<n;i++){
        totalTurn+=p[i].turnaround;
        totalWait+=p[i].waiting;
    }
    avgT=totalTurn/n;
    avgW=totalWait/n;
    printf("Average turn around time :%.2f\n",avgT);
    printf("Average waiting time :%.2f\n",avgW);
}

void priority(int n){
    int i,j,com;
    float totalTurn=0,totalWait=0,avgT,avgW;
    printf("Enter the priority: \n");
    for(i=0;i<n;i++){
        printf("p[%d]: ",i);
        scanf("%d",&p[i].priority);
    }
    for(i=0;i<n;i++){
        for(j=0;j<n-i-1;j++){
            if(p[j].priority>p[j+1].priority){
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
    com=0;
    for(i=0;i<n;i++){
        com+=p[i].burst;
        p[i].turnaround=com;
        p[i].waiting=com-p[i].burst;
    }
    printf("Gantt chart\n");
    printf("0");
    for(i=0;i<n;i++){
        printf("p [%d] %d ",p[i].no,p[i].turnaround);
    }
    printf("\n");
    print(n);
    for(i=0;i<n;i++){
        totalTurn+=p[i].turnaround;
        totalWait+=p[i].waiting;
    }
    avgT=totalTurn/n;
    avgW=totalWait/n;
    printf("Average turn around time:%.2f\n",avgT);
    printf("Average waiting time: %.2f\n",avgW);
}

void roundrobin(int n){
    int i,quanta,totalBurst=0,com;
    float totalTurn=0,totalWait=0,avgT,avgW;
    printf("Enter the time quanta: \n");
    scanf("%d",&quanta);
    com=0;
    for(i=0;i<n;i++){
        totalBurst+=p[i].burst;
    }
    printf("Gantt chart:\n");
    printf("0");
    while(com<totalBurst){
        for(i=0;i<n;i++){
            if(p[i].burstCopy>0){
                if(p[i].burstCopy<=quanta){
                    com+=p[i].burstCopy;
                    p[i].burstCopy=0;
                    p[i].turnaround=com;
                    p[i].waiting=com-p[i].burst;
                }
                else{
                    com+=quanta;
                    p[i].burstCopy-=quanta;
                }
                printf("p[%d] %d ",i,com);
            }
        }
    }
    print(n);
    for(i=0;i<n;i++){
        totalTurn+=p[i].turnaround;
        totalWait+=p[i].waiting;
    }
    avgT=totalTurn/n;
    avgW=totalWait/n;
    printf("Average turn around time: %.2f\n",avgT);
    printf("Average Waiting time:%.2f\n",avgW);
}
void print(int n){
    int i;
    printf("\nProcess\tBurst time\tturnaround time\twaiting time\n");
    for(i=0;i<n;i++){
        printf("p[%d]\t\t%d\t\t%d\t\t%d\n",p[i].no,p[i].burst,p[i].turnaround,p[i].waiting);
    }
}

int main(){
    int i,j,n,option;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    printf("Enter the burst time: ");
    for(i=0;i<n;i++){
        printf("p[%d]: ",i);
        scanf("%d",&p[i].burst);
        p[i].burstCopy=p[i].burst;
        p[i].no=i;
    }
    do{
        for(i=0;i<n;i++){
            for(j=0;j<n-i-1;j++){
                if(p[j].no>p[j+1].no){
                    temp=p[j];
                    p[j]=p[j+1];
                    p[j+1]=temp;
                }
            }
        }
        printf("\n1.FCFS\n2.SJF\n3.PRIORITY\n4.ROUND ROBIN\n5.EXIT\nEnter the option:");
        scanf("%d",&option);
        switch(option){
            case 1:
            fcfs(n);
            break;
            case 2:
            sjf(n);
            break;
            case 3:
            priority(n);
            break;
            case 4:
            roundrobin(n);
            break;
            case 5:
            printf("Exit");
            break;
            default:
            printf("Invalid option");
            

        }
    }while(option!=5);
    return 0;
}