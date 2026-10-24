#ifndef TASKS_H
#define TASKS_H

#define MAX_TASKS 1000

struct Task {
    int id;
    char name[100];
    int priority;
    int completed;
    struct Task *next;
};

void addTask(void);
void viewTasks(void);
void completeTask(void);
void deleteTask(void);
void searchTask(void);
void sortTasks(void);
void freeTasks(void);

#endif
