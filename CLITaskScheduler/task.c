# include "task.h"
# include "utilis.h"
# include <stdlib.h>
# include <string.h>
#include <stdio.h>


TaskManager * tmCreate(void){
    // Create and Initialize TaskManager System.
    TaskManager * tm = malloc(sizeof(TaskManager));
    tm -> nextId = 1;
    tm -> size = 0; // There is no task in the queue.
    tm -> capacity = MAX_TASKS;
    tm -> tasks = malloc(MAX_TASKS * sizeof(Task)); // Initialize the queue.
    
    return tm;
}

void tmDestroy(TaskManager * tm){
    for(int i = 0 ; i < tm -> size ; i++){
        free(tm -> tasks[i]);
    }
    free(tm -> tasks);
    free(tm);
}

int tmPush(TaskManager *tm, const char *name, int priority, const char *due){
    /*
     The sorting wasn't done at the push step because during actual operation, the program will directly start running the tasks in heap[0]. If a new task is added at this point, the program will by default drop it to the end. Sorting at this point might cause the tasks in heap[0] to no longer be running tasks.
     */
    // Move new task to the end of the heap. Return 0 or 1 for fail or successful to add the task.
    Task * task = malloc(sizeof(Task));
    task -> idNumber = tm -> nextId;
    MyStrCopy(task -> name, name, strlen(name));
    task -> priority = priority;
    MyStrCopy(task -> dueDate, due, strlen(due));
    task -> status = STATUS_PENDING;
    tm -> tasks[tm -> size] = task;
    siftUp(tm, tm -> size);
    
    tm -> nextId++;
    if(tm -> nextId > 999){
        tm -> nextId = 1;
    }
    tm -> size++;
    
    return 1;
}

static void swap(TaskManager * tm , int i , int j){
    // Internal function : Swaping two nodes in the heap.
    Task * tempTask = tm -> tasks[i];
    tm -> tasks[i] = tm -> tasks[j];
    tm -> tasks[j] = tempTask;
    
}

void siftUp(TaskManager * tm , int i){
    // Node i is compared with its parent node; if the node with higher priority is selected, it is sifted up.【It's still needed in data loading.】

    while(i != 0){
        int parentIndex = (i - 1) / 2;
        if(tm -> tasks[i] -> priority <= tm -> tasks[parentIndex] -> priority){
            break;
        }else{
            swap(tm , i , parentIndex);
            i = parentIndex;
        }
    }
}

static void siftDown(TaskManager * tm , int i){
    // Internal function: Node i is compared with its left and right child nodes; if the node with lower priority is sifted down.

    if((2*i+1) > tm ->size || (2*i+2) > tm -> size){
        // There is no child node for this node.
        return;
    }
    while(tm->tasks[2*i+1] != NULL || tm->tasks[2*i+2] != NULL){
        int theLargest = 0;
        if(tm->tasks[2*i+1] -> priority < tm->tasks[2*i+2] -> priority){
            theLargest = 2*i+2;
        }else{
            //left ≥ right
            theLargest = 2*i+1;
        }
        if(tm -> tasks[i] -> priority < tm -> tasks[theLargest] -> priority){
            swap(tm, i, theLargest);
            i = theLargest;
        }else{
            // target ≥ left(or right) sub-node.
            break;
        }
    }
}

Task * tmPeek(TaskManager * tm){
    //
    return tm -> tasks[0];
}

void tmPop(TaskManager *tm){
    // remove tasks[0](which is completed). And restructing the heap. Completed tasks are immediately freed from memory. This reflects embedded system constraints where memory is limited and task history is not required.
    
    // Free the task from the memory.
    Task * completedTask = tmPeek(tm);
    free(completedTask);
    tm -> size--;
    
    // Restructing the heap.
    tm -> tasks[0] = tm -> tasks[tm -> size];
    siftDown(tm, 0);
}


int tmDelete(TaskManager * tm , int id){
    // find target node, free it and replace with the last node. Restructing the heap by sifting down or up. Return 0 or 1 for fail or successful to remove the task.
    int index = 9999;
    for(int i = 0 ; i < tm -> size ; i++){
        if(tm -> tasks[i] -> idNumber == id){
            index = i;
            free(tm -> tasks[index]);
            break;
        }
    }
    if(index == 9999){
        // The id isn't exist in the tasks list.
        return 0;
    }
    
    if(index == tm -> size){
        // The deleted data is the last node.
        tm -> size--;
    }else{
        tm -> size--;
        tm -> tasks[index] = tm -> tasks[tm -> size];
        if(index == 0){
            // The deleted data is the first node.
            siftDown(tm, 0);
        }else{
            if(tm -> tasks[index] -> priority > tm -> tasks[(index-1)/2] -> priority){
                siftUp(tm, index);
            }else{
                // The priority of current task < it parent node. Therefore it definitly ≥ it child nodes.
                siftDown(tm, index);
            }
        }
    }
    return 1;
}

int tmComplete(TaskManager * tm , int id){
    // Find target node and mart the status as done. Return 0 or 1 means failed or done. 
    if(tm -> size == 0){
        printf("NO DATA.");
        return 0;
    }
    tmPeek(tm) -> status = STATUS_DONE;
    tmPop(tm);
    printf("SUCCESSFUL.");
    return 1;
}

