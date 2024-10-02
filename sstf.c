#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

void sort(int a[] ,int n)
{
    int i,j,temp;
    for(i=0; i < n-1 ;i++)
    {
        for(j=0; j < n-i-1 ; j++)  // Corrected 'i++' to 'j++'
        {
            if(a[j] > a[j+1])
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}

void accept_requests(int requests[], int nreqs)
{
    printf("Enter %d requests: ", nreqs);
    for (int i = 0; i < nreqs; i++)
    {
        scanf("%d", &requests[i]);  // Accepting disk requests from the user
    }
}

void sstf(int head , int req[] , int nreq)
{
    int total_mov = 0;
    int visited[200] = {0};
    int count  = nreq;
    int i = 0;

    sort(req , nreq);

    // for finding the initial position
    while(i < nreq && req[i] < head)
    {
        i++;
    }
    printf("Sequence : ");
    while(count > 0)
    {
        int left = i-1;
        int right = i;
        while(left >= 0 && visited[left])
        {
            left--;
        }
        while(right < nreq && visited[right])
        {
            right++;
        }
        int left_dist = (left >= 0) ? abs(req[left] - head) : INT_MAX;
        int right_dist = (right < nreq) ? abs(req[right] - head) : INT_MAX;

        if(left_dist == INT_MAX && right_dist == INT_MAX)
        {
            break;
        }
        else if(left_dist < right_dist)
        {
            head = req[left];
            visited[left] = 1;
            total_mov += left_dist;
            count--;
            i = left;
        }
        else 
        {
            head = req[right];
            visited[right] = 1;
            total_mov += right_dist;  // Fixed incorrect assignment of total_mov
            count--;
            i = right;
        }
        printf("%d ", head);
    }
    printf("\nTotal head movements: %d\n", total_mov);  // Corrected print statement
}

int main()
{
    int n;
    printf("Enter the number of disk requests: ");
    scanf("%d",&n);

    int req[100];
    accept_requests(req, n);  // Use the new accept_requests function

    int head;
    printf("Enter initial head position: ");
    scanf("%d",&head);

    sstf(head, req, n);

    return 0;
}
