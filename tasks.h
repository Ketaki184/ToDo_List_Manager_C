#include <stdio.h>
#include <string.h>
#include "tasks.h"

static struct Task tasks[MAX_TASKS];
static int taskCount = 0;

// Add a new task
void addTask(void)
{
    if (taskCount >= MAX_TASKS)
    {
        printf("Task list is full!\n");
        return;
    }

    tasks[taskCount].id = taskCount + 1;

    printf("Enter task description: ");

    getchar();

    fgets(tasks[taskCount].description,
          sizeof(tasks[taskCount].description), stdin);

    tasks[taskCount].description[
        strcspn(tasks[taskCount].description, "\n")] = '\0';

    tasks[taskCount].completed = 0;

    taskCount++;

    printf("Task added successfully!\n");
}

// Display all tasks
void displayTasks(void)
{
    int i;

    if (taskCount == 0)
    {
        printf("No tasks available.\n");
        return;
    }

    printf("\n===== TASK LIST =====\n");

    for (i = 0; i < taskCount; i++)
    {
        printf("Task ID: %d\n", tasks[i].id);
        printf("Description: %s\n", tasks[i].description);

        if (tasks[i].completed)
            printf("Status: Completed\n");
        else
            printf("Status: Pending\n");

        printf("---------------------\n");
    }
}

// Mark a task as completed
void markTaskCompleted(void)
{
    int id, i;

    if (taskCount == 0)
    {
        printf("No tasks available.\n");
        return;
    }

    printf("Enter Task ID to complete: ");

    if (scanf("%d", &id) != 1)
    {
        printf("Invalid input!\n");

        while (getchar() != '\n')
            ;

        return;
    }

    for (i = 0; i < taskCount; i++)
    {
        if (tasks[i].id == id)
        {
            tasks[i].completed = 1;
            printf("Task marked as completed!\n");
            return;
        }
    }

    printf("Task ID not found!\n");
}
