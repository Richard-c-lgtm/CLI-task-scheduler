# include "storage.h"
# include "task.h"
# include "utilis.h"
# include <stdio.h>

int main(void) {
    TaskManager * tm = tmCreate();
    int state = storageLoad(tm , "tasks.txt");
    if(state == OPEN_FILE_FAIL){
        printf("There is no such file.\n");
    }else if(state == READ_FILE_FAIL){
        printf("Missing some important data. File reading failure.\n");
        return 0;
    }else if (state == MISSING_DATA){
        printf("Missing some tasks data.\n");
    }
    
    int choice = 999;
    while(1){
        printMenu();
        choice = readInt("Make a choice: ");
        if(choice > 4 || choice < 0){
            printf("Invalid Value.\n");
        }else if(choice == 0){
            int state = storageSave(tm, "tasks.txt");
            if(state == NO_DATA_NEED_TO_STORE){
                printf("NO DATA NEED TO STORE.\n");
            }else if(state == SUCCESS){
                printf("STORAGE SUCCESS.\n");
            }
            tmDestroy(tm);
            return 0;
        }else{
            switch(choice){
                case 1:{
                    char name[MAX_NAME_LEN];
                    readStr(name , "Input Task Name: ");
                    int priority = 0;
                    while(1){
                        priority = readInt("Input Task Priority: ");
                        if(priority == 0 || priority > 5){
                            printf("Invalid Value.\n");
                        }else{
                            break;
                        }
                    }
                    char dueDate[MAX_NAME_LEN];
                    readStr(dueDate , "Input Task due date: ");
                    tmPush(tm, name, priority, dueDate);
                    break;
                }
                case 2:{
                    printAll(tm);
                    break;
                }
                case 3:{
                    int id = readInt("Input Task id number you have completed: ");
                    tmComplete(tm, id);
                    break;
                }
                case 4:{
                    int id = readInt("Input Task id number you want to delete: ");
                    tmDelete(tm, id);
                    break;
                }
            }
        }
    }
}
