#include <gtest/gtest.h>

// Tell the C++ compiler to handle these C headers using C linkage rules
extern "C" {
    #include "task.h"
    #include "utilis.h"
}

// Test 1: Verify TaskManager initialization
TEST(TaskManagerTest, Initialization) {
    TaskManager *tm = tmCreate();
    
    // Expecting initial size to be 0
    EXPECT_EQ(tm->size, 0);
    // Expecting capacity to match MAX_TASKS (128)
    EXPECT_EQ(tm->capacity, MAX_TASKS); 
    
    tmDestroy(tm);
}

// Test 2: Verify tmPush and priority queue ordering (siftUp)
TEST(TaskManagerTest, PushAndPrioritySorting) {
    TaskManager *tm = tmCreate();
    
    // Insert tasks with different priority levels: 2, 5, 1
    tmPush(tm, "Task_Low", 2, "2026-08-01");
    tmPush(tm, "Task_High", 5, "2026-08-02");
    tmPush(tm, "Task_Lowest", 1, "2026-08-03");
    
    // Size should be 3 after inserting 3 tasks
    EXPECT_EQ(tm->size, 3);
    
    // The heap top (tmPeek) must return the highest priority task (priority = 5)
    Task *topTask = tmPeek(tm);
    EXPECT_STREQ(topTask->name, "Task_High");
    EXPECT_EQ(topTask->priority, 5);
    
    tmDestroy(tm);
}

// Test 3: Verify tmPop and heap restructuring (siftDown)
TEST(TaskManagerTest, PopAndSiftDown) {
    TaskManager *tm = tmCreate();
    
    tmPush(tm, "Task_A", 3, "2026-08-01");
    tmPush(tm, "Task_B", 5, "2026-08-02");
    tmPush(tm, "Task_C", 4, "2026-08-03");
    
    // Before pop: Top element should be Task_B with priority 5
    EXPECT_EQ(tmPeek(tm)->priority, 5);
    
    // Pop the highest priority task (completing Task_B)
    tmPop(tm);
    
    // Size should decrease to 2
    EXPECT_EQ(tm->size, 2);
    
    // New top element should be Task_C with the next highest priority (4)
    Task *newTopTask = tmPeek(tm);
    EXPECT_STREQ(newTopTask->name, "Task_C");
    EXPECT_EQ(newTopTask->priority, 4);
    
    tmDestroy(tm);
}