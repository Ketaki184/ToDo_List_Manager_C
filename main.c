#include <stdio.h>
#include "tasks.h"
#include "file.h"

int main(void)
{
    int choice;

    loadTasks();

    do {
        printf("\n===== TO-DO LIST MANAGER =====\n");
        printf("1. Add Task\n");
        printf("2. View All Tasks\n");
        printf("3. Mark Task Completed\n");
        printf("4. Delete Task\n");
        printf("5. Search Task\n");
        printf("6. Sort by Priority\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please restart the program.\n");
            break;
        }

        switch (choice) {
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
            case 7:
                printf("Thank you for using To-Do List Manager!\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 7);

    freeTasks();
    return 0;
}
