#include<stdio.h>
#include<stdlib.h>

// function to accept disk request from user

void accept_req(int req[] ,int nreq)
{
    int i;
    printf("Enter %d requests:", nreq);
    for(i=0;i<nreq;i++)
    {
        scanf("%d",&req[i]);
    }
}

// function to implement fcfs algorithm

void fcfs(int head, int req[] ,int nreq)
{
    int i;
    int total_mov =0;
    printf("Sequence of head movement are:\n");
    for(i=0;i<nreq;i++)
    {
        printf("->%d",head);
        total_mov += abs(head - req[i]);
        head = req[i];
    }
    printf("->%d\n",head);
    printf("Total head movement: %d\n\n",total_mov);
}

int main()
{
    int i,nreq,head;
    printf("Enter Initial Head Position: ");
    scanf("%d",&head);

    printf("Enter Number of Requeats: ");
    scanf("%d",&nreq);

    int req[nreq]; // Array to store disk requests

    accept_req(req , nreq); // call to the Accept Request function

    fcfs(head,req,nreq);

 return 0;
}
