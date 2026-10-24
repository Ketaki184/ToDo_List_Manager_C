
#include <stdio.h>

struct Task {
    int id;
    char name[50];
    int priority;
};

void displayTasks(struct Task tasks[], int n) {
    int i;

    if (n == 0) {
        printf("No tasks available.\n");
        return;
    }

    printf("\nID\tTask Name\tPriority\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%s\t\t%d\n",
               tasks[i].id, tasks[i].name,
               tasks[i].priority);
    }
}

void searchTask(struct Task tasks[], int n) {
    int id, i;

    printf("Enter task ID to search: ");
    scanf("%d", &id);

    for (i = 0; i < n; i++) {
        if (tasks[i].id == id) {
            printf("Task found!\n");
            printf("ID: %d\n", tasks[i].id);
            printf("Name: %s\n", tasks[i].name);
            printf("Priority: %d\n", tasks[i].priority);
            return;
        }
    }

    printf("Task not found.\n");
}

void deleteTask(struct Task tasks[], int *n) {
    int id, i, j;

    printf("Enter task ID to delete: ");
    scanf("%d", &id);

    for (i = 0; i < *n; i++) {
        if (tasks[i].id == id) {
            for (j = i; j < *n - 1; j++) {
                tasks[j] = tasks[j + 1];
            }

            (*n)--;
            printf("Task deleted successfully.\n");
            return;
        }
    }

    printf("Task not found.\n");
}

void sortTasks(struct Task tasks[], int n) {
    int i, j;
    struct Task temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (tasks[j].priority > tasks[j + 1].priority) {
                temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }

    printf("Tasks sorted by priority (highest priority first).\n");
    displayTasks(tasks, n);
}

int main(void) {
    struct Task tasks[100] = {
        {101, "Assignment", 2},
        {102, "Project", 1},
        {103, "Study", 3}
    };

    int n = 3;
    int choice;

    do {
        printf("\n--- Task Management System ---\n");
        printf("1. Display Tasks\n");
        printf("2. Search Task by ID\n");
        printf("3. Delete Task by ID\n");
        printf("4. Sort Tasks by Priority\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayTasks(tasks, n);
                break;

            case 2:
                searchTask(tasks, n);
                break;

            case 3:
                deleteTask(tasks, &n);
                break;

            case 4:
                sortTasks(tasks, n);
                break;

            case 5:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);

    return 0;
}
