#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tasks.h"
#include "file.h"

struct Task *head = NULL;
int nextId = 1;

/* Read an integer safely */
static int readNumber(const char *message)
{
    char input[50];
    char extra;
    int number;

    while (1)
    {
        printf("%s", message);

        if (fgets(input, sizeof(input), stdin) == NULL)
            return -1;

        if (sscanf(input, " %d %c", &number, &extra) == 1)
            return number;

        printf("Invalid input. Enter a number.\n");
    }
}

/* Add a new task */
void addTask(void)
{
    struct Task *newTask;
    char name[100];
    int priority;

    printf("Enter task name: ");

    if (fgets(name, sizeof(name), stdin) == NULL)
        return;

    name[strcspn(name, "\n")] = '\0';

    if (strlen(name) == 0)
    {
        printf("Task name cannot be empty.\n");
        return;
    }

    priority = readNumber("Enter priority (1 = High, 5 = Low): ");

    if (priority < 1 || priority > 5)
    {
        printf("Priority must be between 1 and 5.\n");
        return;
    }

    newTask = malloc(sizeof(struct Task));

    if (newTask == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    newTask->id = nextId++;
    strcpy(newTask->name, name);
    newTask->priority = priority;
    newTask->completed = 0;
    newTask->next = NULL;

    if (head == NULL)
    {
        head = newTask;
    }
    else
    {
        struct Task *temp = head;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newTask;
    }

    saveTasks();
    printf("Task added successfully. ID: %d\n", newTask->id);
}

/* Display all tasks */
void viewTasks(void)
{
    struct Task *temp = head;

    if (temp == NULL)
    {
        printf("No tasks available.\n");
        return;
    }

    printf("\n----------- YOUR TASKS -----------\n");
    printf("%-5s %-25s %-10s %-12s\n",
           "ID", "Task", "Priority", "Status");

    while (temp != NULL)
    {
        printf("%-5d %-25.25s %-10d %-12s\n",
               temp->id,
               temp->name,
               temp->priority,
               temp->completed ? "Completed" : "Pending");

        temp = temp->next;
    }
}

/* Mark a task as completed */
void completeTask(void)
{
    int id = readNumber("Enter task ID to complete: ");
    struct Task *temp = head;

    while (temp != NULL)
    {
        if (temp->id == id)
        {
            if (temp->completed)
            {
                printf("This task is already completed.\n");
                return;
            }

            temp->completed = 1;
            saveTasks();
            printf("Task marked as completed.\n");
            return;
        }

        temp = temp->next;
    }

    printf("Task ID not found.\n");
}

/* Delete a task */
void deleteTask(void)
{
    int id = readNumber("Enter task ID to delete: ");
    struct Task *temp = head;
    struct Task *previous = NULL;

    while (temp != NULL)
    {
        if (temp->id == id)
        {
            if (previous == NULL)
                head = temp->next;
            else
                previous->next = temp->next;

            free(temp);
            saveTasks();

            printf("Task deleted successfully.\n");
            return;
        }

        previous = temp;
        temp = temp->next;
    }

    printf("Task ID not found.\n");
}

/* Search tasks by name */
void searchTask(void)
{
    char name[100];
    struct Task *temp = head;
    int found = 0;

    printf("Enter task name to search: ");

    if (fgets(name, sizeof(name), stdin) == NULL)
        return;

    name[strcspn(name, "\n")] = '\0';

    if (strlen(name) == 0)
    {
        printf("Enter a task name.\n");
        return;
    }

    printf("\nSearch results:\n");

    while (temp != NULL)
    {
        if (strstr(temp->name, name) != NULL)
        {
            printf("ID: %d | Task: %s | Priority: %d | Status: %s\n",
                   temp->id,
                   temp->name,
                   temp->priority,
                   temp->completed ? "Completed" : "Pending");

            found = 1;
        }

        temp = temp->next;
    }

    if (!found)
        printf("No matching task found.\n");
}

/* Sort tasks by priority: 1 is highest */
void sortTasks(void)
{
    struct Task *i;
    struct Task *j;
    int swapped;

    if (head == NULL || head->next == NULL)
    {
        printf("Not enough tasks to sort.\n");
        return;
    }

    do
    {
        swapped = 0;
        i = head;

        while (i->next != NULL)
        {
            j = i->next;

            if (i->priority > j->priority)
            {
                int tempId = i->id;
                int tempPriority = i->priority;
                int tempCompleted = i->completed;
                char tempName[100];

                strcpy(tempName, i->name);

                i->id = j->id;
                i->priority = j->priority;
                i->completed = j->completed;
                strcpy(i->name, j->name);

                j->id = tempId;
                j->priority = tempPriority;
                j->completed = tempCompleted;
                strcpy(j->name, tempName);

                swapped = 1;
            }

            i = i->next;
        }
    } while (swapped);

    saveTasks();
    printf("Tasks sorted by priority (highest first).\n");
    viewTasks();
}

/* Release linked-list memory */
void freeTasks(void)
{
    struct Task *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}
