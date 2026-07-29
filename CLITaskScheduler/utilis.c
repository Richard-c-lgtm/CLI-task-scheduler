# include "utilis.h"
# include <stdlib.h>
# include <string.h>



char * MyStrCopy(char * to , const char * from , size_t charSize){
    int index = 0;
    
    while(index < charSize && from[index] != '\0'){
        // -1 is for adding '\0' into the end of the to
        to[index] = from[index];
        index++;
    }
    to[index] = '\0';
    
    return to;
}

void printTask(const Task * task){
    printf("%d | %s | %d | %s | %d\n" , task -> idNumber, task -> name, task -> priority, task -> dueDate , task -> status);
}

void printAll(const TaskManager * tm){
    if(tm -> size == 0){
        printf("NO DATA.\n");
        return;
    }
    printf("id | name | priority | du date | status\n");
    for(int i = 0 ; i < tm -> size ; i++){
        printTask(tm -> tasks[i]);
    }
        
}

void printMenu(void){
    printf("1. Add task\n");
    printf("2. View all tasks\n");
    printf("3. Complete task\n");
    printf("4. Delete task\n");
    printf("0. Exit\n");
}

int readInt(char * message){
    // Dealing with the number safely.(make sure there will be no text like "12a" put into the variable marked as int.)
    while(1){
        printf("%s" , message);
        int number = 0;
        char text[10];
        char * endPoint;
        fgets(text , sizeof(text) , stdin);
        number = (int)strtol(text , &endPoint , 10);
        
        if(*endPoint != '\n' && *endPoint != '\0'){
            printf("INVALID INPUT\n");
        }else{
            return number;
        }
    }
}

void readStr(char * name , char * message){
    char buffer[200];
    while(1){
        printf("%s" , message);
        fgets(buffer , 200 , stdin);
        buffer[strcspn(buffer , "\n")] = '\0';
        if(strlen(buffer) > MAX_NAME_LEN){
            printf("INVALID INPUT\n");
        }else{
            MyStrCopy(name, buffer, strlen(buffer));
            return;
        }
    }
}
