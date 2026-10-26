#ifndef TASKS_H
#define TASKS_H

struct Task
{
    int id;
    char name[100];
    int priority;
    int completed;
    struct Task *next;
};

extern struct Task *head;
extern int nextId;

void addTask(void);
void viewTasks(void);
void completeTask(void);
void deleteTask(void);
void searchTask(void);
void sortTasks(void);
void freeTasks(void);

#endif
