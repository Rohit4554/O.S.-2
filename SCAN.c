#include <stdio.h>
#include <stdlib.h>
#define MAX_CYL 200  

void sort(int arr[], int n) 
{
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (arr[j] > arr[j + 1]) 
            {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

void accept_requests(int requests[], int nreqs) 
{
    printf("Enter the requests: ");
    for (int i = 0; i < nreqs; i++) 
    {
        scanf("%d", &requests[i]);
    }
    sort(requests, nreqs);  
}

void scan(int head, int direction, int requests[], int nreqs) 
{
    int total_movement = 0;
    int count = nreqs;
    int visited[MAX_CYL] = {0};  
    int i;

    if (direction == 1) 
    { 
        for (i = 0; i < nreqs; i++) 
        {
            if (requests[i] >= head)
                break;
        }
    } 
    else 
    { 
        for (i = nreqs - 1; i >= 0; i--) 
        {
            if (requests[i] <= head)
                break;
        }
    }

    printf("Sequence: %d", head);

    while (1) 
    {
        if (i >= nreqs || i < 0) 
        {  
            if (i < 0) 
            {
                total_movement += head;  
                head = 0;
                direction = 1;  
                printf(" -> %d", head);
            } 
            else 
            if (i >= nreqs) 
            {
                total_movement += (MAX_CYL - 1 - head); 
                head = MAX_CYL - 1;
                direction = -1; 
                printf(" -> %d", head);
            }
            i += direction; 
            continue;
        }

        if (visited[i] == 1) 
        { 
            i += direction;
            continue;
        }

        total_movement += abs(head - requests[i]);  
        head = requests[i];  
        visited[i] = 1;  
        printf(" -> %d", head);

        count--;  
        if (count <= 0)  
            break;

        i += direction;  
    }

    printf("\nTotal head movement: %d\n", total_movement);
}

int main() 
{
    int requests[MAX_CYL];  
    int nreqs, head, direction;

    printf("Enter number of requests: ");
    scanf("%d", &nreqs);

    accept_requests(requests, nreqs);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter direction (-1 for left, 1 for right): ");
    scanf("%d", &direction);

    scan(head, direction, requests, nreqs);

    return 0;
}
