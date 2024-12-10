#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BLOCKS 10
#define MAX_FILES 10

struct file_details 
{
    char fname[20];
    int start;
    int end;
};

int bit_vector[MAX_BLOCKS];
struct file_details directory[MAX_FILES];
int file_count = 0;

void init() 
{
    int i;
    for (i = 0; i < MAX_BLOCKS; i++) 
    {
        bit_vector[i] = -1;
    }
}

void show_bit_vector() 
{
    printf("Bit Vector: ");
    for (int i = 0; i < MAX_BLOCKS; i++) 
    {
        printf("%d ", bit_vector[i]);
    }
    printf("\n");
}

void show_directory() 
{
    if (file_count == 0) 
    {
        printf("Directory is empty.\n");
        return;
    }
    printf("Directory:\n");
    for (int i = 0; i < file_count; i++) 
    {
        printf("File Name: %s, Start Block: %d, End Block: %d\n",
               directory[i].fname,
               directory[i].start,
               directory[i].end);
    }
}

void create_file() 
{
    if (file_count >= MAX_FILES) 
    {
        printf("Directory is full.\n");
        return;
    }
    
    char fname[20];
    int file_size, start_block = -1, previous_block = -1;

    printf("Enter the File Name: ");
    scanf("%s", fname);

    printf("Enter the File Size: ");
    scanf("%d", &file_size);

    if (file_size > MAX_BLOCKS) 
    {
        printf("File size exceeds maximum limit.\n");
        return;
    }

    int free_blocks = 0;
    for (int i = 0; i < MAX_BLOCKS; i++) 
    {
        if (bit_vector[i] == -1) 
        {
            free_blocks++;
        }
    }

    if (free_blocks < file_size) 
    {
        printf("Not enough free blocks available.\n");
        return;
    }

    srand(time(0));
    for (int i = 0; i < file_size; i++) 
    {
        int block;
        do 
        {
            block = rand() % MAX_BLOCKS;
        } 
        while (bit_vector[block] != -1);

        if (start_block == -1) 
        {
            start_block = block;
        } 
        else 
        {
            bit_vector[previous_block] = block;
        }
        previous_block = block;
        bit_vector[block] = -9; // Mark block as used
    }

    directory[file_count].start = start_block;
    directory[file_count].end = previous_block;
    strcpy(directory[file_count].fname, fname);
    file_count++;
    printf("File created successfully.\n");
}

void delete_file() 
{
    char fname[20];
    printf("Enter filename to delete: ");
    scanf("%s", fname);

    int found = -1;
    for (int i = 0; i < file_count; i++) 
    {
        if (strcmp(directory[i].fname, fname) == 0) 
        {
            found = i;
            break;
        }
    }

    if (found == -1) 
    {
        printf("File not found.\n");
        return;
    }

    int block = directory[found].start;
    while (block != -9) 
    {
        int next_block = bit_vector[block];
        bit_vector[block] = -1; // Mark block as free
        block = next_block;
    }
    for (int i = found; i < file_count - 1; i++) 
    {
        directory[i] = directory[i + 1];
    }
    file_count--;
    printf("File deleted successfully.\n");
}

int main() 
{
    int ch;
    init();
    do {
        printf("\nMenu:\n");
        printf("1. Show Bit Vector\n");
        printf("2. Create New File\n");
        printf("3. Display Directory\n");
        printf("4. Delete File\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) 
        {
            case 1: show_bit_vector(); break;
            case 2: create_file(); break;
            case 3: show_directory(); break;
            case 4: delete_file(); break;
            case 5: exit(0);
            default: printf("Invalid option.\n");
        }
    } while (ch != 5);
    return 0;
}
