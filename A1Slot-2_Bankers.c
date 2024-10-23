#include<stdio.h>
#include<stdlib.h>

int available[10], need[10][10], request[10] ,finish[10]={0},  work[10], safe[10]={0}, process,nor;
int allocation[10][10];
int max[10][10];

void accept_matrix(int a[][10], int n, int m)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
}

void find_need(int n ,int m)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

void accept_available(int m)
{
    int i;
    for(i=0;i<m;i++)
    {
        scanf("%d",&available[i]);
    }
}

void accept_request(int n,int m)
{
    int i;
    printf("Enter Process Number: ");
    scanf("%d",&process);
    printf("Enter Resource request for process %d: ",process);
    for(i=0;i<m;i++)
    {
        scanf("%d",&request[i]);
    }
}

void display_matrices(int n ,int m)
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

        for(j = 0; j < m; j++)
        printf("%d  ", need[i][j]);
        printf("\n");
    }
     printf("Available:\t");
     for(i = 0; i < m; i++)
     {
        printf("%d ", available[i]);
     }
  printf("\n");
}

int compare_need(int p)
{
    int j;
    for(j=0;j<nor;j++)
    {
        if(need[p][j] > work[j])
        {
            return -1;
        }
    }
    return p;
}

void safety_algo(int n, int m)
{
    int i,j,k,l=0,flag,over=0;
    for(i=0;i<m;i++)
    {
        work[i] = available[i];
    }

    while(!over)
    {
        flag = 0;
        for(i=0;i<n;i++)
        {
            if(finish[i] == 0)
            {
                int canProceed = 1;
                for(j=0;j<m;j++)
                {
                    if(need[i][j] > work[j])
                    {
                        canProceed = 0;
                        break;
                    }
                }
                if(canProceed)
                {
                    for(k=0;k<m;k++)
                    {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = 1;
                    safe[l++] = i;
                    flag = 1;
                }
            }
        }
        if(!flag)
        {
            for(i=0;i<n;i++)
            {
                if(finish[i] == 0)
                {
                    printf("System is Unsafe...\n");
                    exit(1);
                }
            }
            over = 1;
        }
    }
    printf("Safe Sequence is: ");
    for(i=0;i<n;i++)
    {
        printf("P%d  ",safe[i]);
    }
    printf("\n");
}

void resource_req_algo(int n, int m)
{
    int i;

    // Check if request exceeds the need of the process
    for(i = 0; i < m; i++)
    {
        if(request[i] > need[process][i])
        {
            printf("ERROR: Process %d exceeds its maximum demand.\n", process);
            return;  // Exit without making any changes
        }
    }

    // Check if the request can be satisfied with the available resources
    for(i = 0; i < m; i++)
    {
        if(request[i] > available[i])
        {
            printf("Process %d must wait. Resources are not available.\n", process);
            return;  // Exit without making any changes
        }
    }

    // Temporarily allocate the requested resources
    for(i = 0; i < m; i++)
    {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    // Run safety algorithm to check if the system remains in a safe state
    printf("Running Safety Algorithm...\n");
    safety_algo(n, m);

    // If the system is safe, grant the request permanently
    printf("The request for Process %d has been granted.\n", process);
}


void bankers_algo(int n,int m)
{
    resource_req_algo(n,m);
}

int main()
{
    int n, m, choice;
    printf("Enter the number of processes : ");
    scanf("%d",&n);

    printf("Enter the number of resources : ");
    scanf("%d",&m);

   do
    {
        printf("\nMenu >>>>>>>>\n");
        printf("1. Accept Allocation Matrix \n");
        printf("2. Accept Max Matrix \n");
        printf("3. Calculate Need \n");
        printf("4. Accept Available \n");
        printf("5. Display Matrices \n");
        printf("6. Accept request and apply Banker's algorithm \n");
        printf("7. Display Safe Sequence \n");
        printf("8. EXIT \n");

        printf("Enter Your choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1: printf("Enter Allocation Matrix:\n");
                    accept_matrix(allocation, n, m);
                    break;
            case 2: printf("Enter Max Matrix:\n");
                    accept_matrix(max, n, m);
                    break;
            case 3: printf("Calculating Need Matrix...\n");
                    find_need(n, m);
                    display_matrices(n, m);
                    break;
            case 4: printf("Enter Available Resources:\n");
                    accept_available(m);
                    break;
            case 5: display_matrices(n, m);
                    break;
            case 6: accept_request(n, m);
                    bankers_algo(n, m);
                    break;
            case 7: safety_algo(n, m);
                    break;
            case 8: printf("Exiting...\n");
                    exit(0);
            default : printf("Invalid Option..\n");
        }

     }while(choice != 8);
     
    return 0;
}
