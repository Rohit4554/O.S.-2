#include<stdio.h>
#include<stdlib.h>

int allocation[10][10], max[10][10], Need[10][10], available[10];
int n, m; // Number of processes and requests/resources

// Function to accept matrix values
void accept_matrix(int a[][10])
{
    int i, j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
}

// Function to accept available resources
void accept_available()
{
    int i;
    for(i = 0; i < m; i++)
    {
        scanf("%d", &available[i]);
    }
}

// Function to calculate the need matrix
void calculate_need()
{
    int i, j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            Need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to display matrices
void display_matrix()
{
    int i, j;
    printf("\nAllocation\tMax\t\tNeed\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
            printf("%d  ", allocation[i][j]);
        printf("\t\t");

        for(j = 0; j < m; j++)
            printf("%d  ", max[i][j]);
        printf("\t");

        for(j = 0; j < m;   j++)
            printf("%d  ", Need[i][j]);
        printf("\n");
    }
    printf("Available:\t");
    for(i = 0; i < m; i++)
    {
        printf("%d ", available[i]);
    }
    printf("\n");
}

int main()
{
    int choice;
    
    // Get the number of processes and requests/resources
    printf("Enter Number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of Requests: ");
    scanf("%d", &m);

    do
    {
        // Display menu
        printf("\nMenu\n");
        printf("1. Accept Allocation Matrix\n");
        printf("2. Accept Max Matrix\n");
        printf("3. Calculate Need\n");
        printf("4. Accept Available\n");
        printf("5. Display Matrix\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);  // Accept choice from the user

        switch(choice)
        {
            case 1:
                printf("Enter Allocation Matrix:\n");
                accept_matrix(allocation);
                break;
            case 2:
                printf("Enter Max Matrix:\n");
                accept_matrix(max);
                break;
            case 3:
                calculate_need();
                printf("Need is calculated.\n");
                break;
            case 4:
                printf("Enter Available Resources:\n");
                accept_available();
                break;
            case 5:
                printf("Displaying Matrices:\n");
                display_matrix();
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid Option!\n");
        }
    } while(choice != 6);

    return 0;
}
