#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 

struct File_Details 
{
    char FileName[10]; 
    int Fstart;
    int Flength;
} F[10];  // Array to store file details

int Bit_vector[50], count = 0, n;  // n is the number of blocks

void initial() 
{
    int i;
    for (i = 0; i < n; i++) 
    {
        Bit_vector[i] = 1;  // Set all blocks as free (1)
    }
}

void Display_bit_vector() 
{
    int i;
    printf("Bit Vector: ");
    for (i = 0; i < n; i++) 
    {
        printf("%d ", Bit_vector[i]);  // Display bit vector
    }
    printf("\n");
}

int Check_if_free_blocks_available(int start, int length) 
{
    int j = start;
    int free_count = 0;
    while (j < n && free_count < length) 
    {
        if (Bit_vector[j] == 1) 
        {  // Check if block is free
            free_count++;
        } 
        else 
        {
            return 0;  // Not enough contiguous free blocks
        }
        j++;
    }
    return free_count == length;  // Return true if enough blocks are available
}

void Update_directory(int start, int length, char fname[]) 
{
    int i;
    strcpy(F[count].FileName, fname);
    F[count].Fstart = start;
    F[count].Flength = length;
    // Mark blocks as allocated (0)
    for (i = start; i < start + length; i++) 
    {
        Bit_vector[i] = 0;
    }
    count++;  // Increase file count
}

void Create_File() 
{
    int i, start, length;
    char fname[10];
    printf("\nEnter File name: ");
    scanf("%s", fname);
    printf("Enter File length: ");
    scanf("%d", &length);
    // Find starting position for file
    for (i = 0; i < n; i++) 
    {
        if (Bit_vector[i] == 1 && Check_if_free_blocks_available(i, length)) 
        {
            start = i;
            break;
        }
    }
    if (i == n) 
    {
        printf("Error: Not enough contiguous free space available.\n");
        return;
    } 
    Update_directory(start, length, fname);
    printf("File '%s' created successfully. \n", fname);
}

void Display_directory() 
{
    int i;
    if (count == 0) 
    {
        printf("Directory is empty.\n");
        return;
    }
    printf("\nDirectory:\n");
    printf("File Name\tStart Block\tLength\n");
    for (i = 0; i < count; i++) 
    {
        printf("%s\t\t%d\t\t%d\n", F[i].FileName, F[i].Fstart, F[i].Flength);
    }
}

int File_is_exist_or_not(char temp[]) 
{
    int i;
    for (i = 0; i < count; i++) 
    {
        if (strcmp(F[i].FileName, temp) == 0) 
        {
            return i;  // File found, return its index
        }
    }
    return -1;  // File not found
}

void Delete_File() 
{
    char name[10];
    int i, j, index;
    printf("\nEnter name to delete the file: ");
    scanf("%s", name);
    
    index = File_is_exist_or_not(name);
    if (index == -1) 
    {
        printf("Error: File not found.\n");
        return;
    }
    // Free the allocated blocks
    for (j = F[index].Fstart; j < F[index].Fstart + F[index].Flength; j++) 
    {
        Bit_vector[j] = 1;
    }
    printf("File '%s' deleted successfully.\n", name);
    // Shift the directory array to remove the file
    for (i = index; i < count - 1; i++) 
    {
        F[i] = F[i + 1];
    }
    count--;
}

int main() 
{
    int choice;
    
    printf("Enter the total number of blocks on the disk: ");
    scanf("%d", &n);
    initial();  // Initialize bit vector

    do 
    {
        printf("\n1. Show Bit vector\n");
        printf("2. Create New File\n");
        printf("3. Show Directory\n");
        printf("4. Delete File\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch (choice) 
        {
            case 1: Display_bit_vector();
                    break;
            case 2: Create_File();
                    break;
            case 3: Display_directory();
                    break;
            case 4: Delete_File();
                    break;
            case 5: exit(0);
            
            default: printf("Invalid choice. Please try again.\n");
        }
    }while (choice != 5);
    
    return 0;
}
