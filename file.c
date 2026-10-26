#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tasks.h"
#include "file.h"

/* Save all tasks to a text file */
void saveTasks(void)
{
    FILE *fp = fopen("tasks.txt", "w");
    struct Task *temp = head;

    if (fp == NULL)
    {
        printf("Error: Could not save tasks.\n");
        return;
    }

    while (temp != NULL)
    {
        /* Format: ID|Priority|Completed|Task name */
        fprintf(fp, "%d|%d|%d|%s\n",
                temp->id,
                temp->priority,
                temp->completed,
                temp->name);

        temp = temp->next;
    }

    fclose(fp);
}

/* Load previously saved tasks */
void loadTasks(void)
{
    FILE *fp = fopen("tasks.txt", "r");
    char line[200];

    if (fp == NULL)
        return;

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        int id, priority, completed;
        char name[100];

        if (sscanf(line, "%d|%d|%d|%99[^\n]",
                   &id, &priority, &completed, name) == 4)
        {
            struct Task *newTask = malloc(sizeof(struct Task));

            if (newTask == NULL)
            {
                printf("Memory allocation failed while loading tasks.\n");
                break;
            }

            newTask->id = id;
            strcpy(newTask->name, name);
            newTask->priority = priority;
            newTask->completed = completed;
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

            if (id >= nextId)
                nextId = id + 1;
        }
    }

    fclose(fp);
}
