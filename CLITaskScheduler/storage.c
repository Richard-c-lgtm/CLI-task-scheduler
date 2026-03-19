# include "storage.h"
# include "utilis.h"
# include <stdlib.h>
# include <string.h>
# include <stdio.h>


int storageSave(const TaskManager *tm, const char *filepath){
    FILE * fp = fopen(filepath , "w");
    if(fp == NULL){
        return OPEN_FILE_FAIL;
    }
    if(tm -> size == 0){
        return NO_DATA_NEED_TO_STORE;
    }
    // Store the total number of the tasks
    fprintf(fp , "%d|%d\n" , tm -> size , tm -> nextId);
    for(int i = 0 ; i < tm -> size ; i++){
        fprintf(fp ,
                "%d|%s|%d|%s|%d\n" ,
                tm -> tasks[i] -> idNumber,
                tm -> tasks[i] -> name,
                tm -> tasks[i] -> priority,
                tm -> tasks[i] -> dueDate,
                tm -> tasks[i] -> status);
    }
    
    fclose(fp);
    return SUCCESS;
}


int storageLoad(TaskManager *tm, const char *filepath){
    FILE * fp = fopen(filepath , "r");
    if(fp == NULL){
        return OPEN_FILE_FAIL;
    }
    
    if(fscanf(fp, "%d|%d" , &tm -> size , &tm -> nextId)!= 2){
        fclose(fp);
        return READ_FILE_FAIL;
    }
    
    int index = 0;
    // Ensure data integrity and discard incomplete data.
    int status = 0;
    for(int i = 0 ; i < tm -> size ; i++){
        Task * task = malloc(sizeof(Task));
        status = fscanf(fp , "%d|%[^|]|%d|%[^|]|%d" , &task -> idNumber, task -> name, &task -> priority, task -> dueDate, &task -> status);
        
        if(status == -1){
            // End of file. Missing data(Actual amount of data in the file < The amount of data stored in the file)
            break;
        }
        if(status != 5){
            // Data corruption
            free(task);
        }else{
            tm -> tasks[index] = task;
            index++;
            
            // Restructing the heap if necessary
            if(tm -> tasks[index-1] -> priority > tm -> tasks[((index-2)/2)] -> priority){
                siftUp(tm , (index-1));
            }
        }
    }
    
    if(tm -> size > index){
        tm -> size = index;
        return MISSING_DATA;
    }
    return SUCCESS;
}
