#ifndef TASKS_H
#define TASKS_H

#define MAX_TASKS 100

struct Task
{
    int id;
    char description[100];
    int completed;
};

void addTask(void);
void displayTasks(void);
void markTaskCompleted(void);

#endif
