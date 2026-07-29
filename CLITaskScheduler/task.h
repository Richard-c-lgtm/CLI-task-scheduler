# ifndef TASK_H
# define TASK_H

# define MAX_NAME_LEN 64
# define MAX_DATE_LEN 16
# define MAX_TASKS 128 // 2^7

typedef enum{
    STATUS_PENDING = 0,
    STATUS_DONE = 1
}TaskStatus;

typedef struct{
    int idNumber; // Unique id number
    char name[MAX_NAME_LEN]; // Task name
    int priority; // From 1 to 5(5 is the highest priority.)
    char dueDate[MAX_DATE_LEN]; // Expriation date YYYY-MM-DD
    TaskStatus status; // status:Done/Pending
}Task;

typedef struct{
    Task ** tasks; // Pointer for the list of tasks.
    int size; // Current size of the binary heap
    int capacity; // Current queue capacity
    int nextId; // An infinitely incrementing value; if the value reaches 999, it returns 1.
    
}TaskManager;

TaskManager* tmCreate(void);
int tmPush(TaskManager *tm, const char *name, int priority, const char *due);
void siftUp(TaskManager * tm , int i);
Task* tmPeek(TaskManager *tm);
void tmPop(TaskManager *tm);
int  tmComplete(TaskManager *tm, int id);
int  tmDelete(TaskManager *tm, int id);
void tmDestroy(TaskManager *tm);

# endif

