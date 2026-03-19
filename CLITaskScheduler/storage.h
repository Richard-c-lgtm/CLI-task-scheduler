# ifndef STORAGE_H
# define STORAGE_H

# include "task.h"

# define SUCCESS 1
# define OPEN_FILE_FAIL 0
# define READ_FILE_FAIL -1
# define MISSING_DATA -2
# define NO_DATA_NEED_TO_STORE -3

int storageSave(const TaskManager *tm, const char *filepath);
int storageLoad(TaskManager *tm, const char *filepath);


# endif
