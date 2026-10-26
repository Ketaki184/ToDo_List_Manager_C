#include <stdio.h>
#include "tasks.h"
#include "file.h"

int main(void)
{
    int choice;
    char input[50];
    char extra;

    loadTasks();

    do
    {
        printf("\n================================\n");
        printf("       TO-DO LIST MANAGER\n");
        printf("================================\n");
        printf("1. Add Task\n");
        printf("2. View All Tasks\n");
        printf("3. Mark Task as Completed\n");
        printf("4. Delete Task\n");
        printf("5. Search Task\n");
        printf("6. Sort Tasks by Priority\n");
        printf("0. Exit\n");
        printf("================================\n");
        printf("Enter your choice: ");

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        if (sscanf(input, " %d %c", &choice, &extra) != 1)
        {
            printf("Invalid choice. Enter a number.\n");
            continue;
        }

        switch (choice)
        {
            case 1:
                addTask();
                break;

            case 2:
                viewTasks();
                break;

            case 3:
                completeTask();
                break;

            case 4:
                deleteTask();
                break;

            case 5:
                searchTask();
                break;

            case 6:
                sortTasks();
                break;

            case 0:
                freeTasks();
                printf("Thank you for using To-Do List Manager!\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}
