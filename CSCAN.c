#include <stdio.h>
#include <stdlib.h>

#define MAX_CYL 200

void sort(int arr[], int n) 
{
    int temp,i,j;
    for (i = 0; i < n - 1; i++) 
    {
        for (j = 0; j < n - i - 1; j++) 
        {
            if (arr[j] > arr[j + 1]) 
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void accept_requests(int requests[], int nreqs) 
{
    printf("Enter requests: ");
    for (int i = 0; i < nreqs; i++) 
    {
        scanf("%d", &requests[i]);
    }
    sort(requests, nreqs); 
}

void c_scan(int head, int direction, int requests[], int nreqs) 
{
    int total_movement = 0;
    int count = nreqs;
    int visited[MAX_CYL] = {0}; 
    int i=0;
    int j=0;
    printf("Sequence of head movements: %d ", head);  

    if (direction == 1) 
    {
        int i = 0;
        while (i < nreqs && requests[i] < head) 
        {
            i++;
        }

        for (j = i; j < nreqs; j++) 
        {
            total_movement += abs(head - requests[j]);
            head = requests[j];
            printf("%d ", head);
        }

        total_movement += (MAX_CYL - 1 - head);
        printf("%d 0 ", MAX_CYL - 1); 
        total_movement += (MAX_CYL - 1); 
        head = 0;

        for (j = 0; j < i; j++) 
        {
            total_movement += abs(head - requests[j]);
            head = requests[j];
            printf("%d ", head);
        }

    } 
    else 
    if (direction == -1) 
    {
        i = nreqs - 1;
        while (i >= 0 && requests[i] > head) 
        {
            i--;
        }

        for (j = i; j >= 0; j--) 
        {
            total_movement += abs(head - requests[j]);
            head = requests[j];
            printf("%d ", head);
        }

        total_movement += head;
        printf("0 %d ", MAX_CYL - 1); 
        total_movement += (MAX_CYL - 1); 
        head = MAX_CYL - 1;

       
        for (j = nreqs - 1; j > i; j--) 
        {
            total_movement += abs(head - requests[j]);
            head = requests[j];
            printf("%d ", head);
        }
    }

    printf("\nTotal head movement: %d\n", total_movement);
}

int main() 
{
    int requests[200];
    int nreqs, head, direction;

    printf("Enter number of requests: ");
    scanf("%d", &nreqs);

    accept_requests(requests, nreqs);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter direction (1 for right, -1 for left): ");
    scanf("%d", &direction);

    c_scan(head, direction, requests, nreqs);

    return 0;
}
