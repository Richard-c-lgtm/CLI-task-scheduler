# ifndef UTILIS_H
# define UTILIS_H

# include "task.h"
# include <stdio.h>

// return pointer is for chained calls
char * MyStrCopy(char * to , const char * from , size_t charSize);
void printTask(const Task *t);
void printAll(const TaskManager *tm);
void printMenu(void);
int  readInt(char * message);
void readStr(char * name , char * message);

# endif
