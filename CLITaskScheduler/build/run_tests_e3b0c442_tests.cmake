add_test([=[TaskManagerTest.Initialization]=]  /Users/chenhao/Desktop/ProgramingForJob/CLITaskScheduler/Program/CLITaskScheduler/build/run_tests [==[--gtest_filter=TaskManagerTest.Initialization]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TaskManagerTest.Initialization]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/chenhao/Desktop/ProgramingForJob/CLITaskScheduler/Program/CLITaskScheduler/test_task.cpp:10]==]
    WORKING_DIRECTORY [==[/Users/chenhao/Desktop/ProgramingForJob/CLITaskScheduler/Program/CLITaskScheduler/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TaskManagerTest.PushAndPrioritySorting]=]  /Users/chenhao/Desktop/ProgramingForJob/CLITaskScheduler/Program/CLITaskScheduler/build/run_tests [==[--gtest_filter=TaskManagerTest.PushAndPrioritySorting]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TaskManagerTest.PushAndPrioritySorting]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/chenhao/Desktop/ProgramingForJob/CLITaskScheduler/Program/CLITaskScheduler/test_task.cpp:22]==]
    WORKING_DIRECTORY [==[/Users/chenhao/Desktop/ProgramingForJob/CLITaskScheduler/Program/CLITaskScheduler/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TaskManagerTest.PopAndSiftDown]=]  /Users/chenhao/Desktop/ProgramingForJob/CLITaskScheduler/Program/CLITaskScheduler/build/run_tests [==[--gtest_filter=TaskManagerTest.PopAndSiftDown]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TaskManagerTest.PopAndSiftDown]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/chenhao/Desktop/ProgramingForJob/CLITaskScheduler/Program/CLITaskScheduler/test_task.cpp:42]==]
    WORKING_DIRECTORY [==[/Users/chenhao/Desktop/ProgramingForJob/CLITaskScheduler/Program/CLITaskScheduler/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
set(run_tests_TESTS [==[TaskManagerTest.Initialization]==] [==[TaskManagerTest.PushAndPrioritySorting]==] [==[TaskManagerTest.PopAndSiftDown]==])
