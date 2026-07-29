cmake_minimum_required(VERSION 3.14)
project(TaskSchedulerTest C CXX)

# Set C/C++ standards
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)

# 1. Fetch GoogleTest automatically from GitHub
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 2. Specify source files (Exclude main.c and storage.c for core logic testing)
set(SOURCE_FILES task.c utilis.c)

# 3. Compile the test executable
add_executable(run_tests test_task.cpp ${SOURCE_FILES})

# 4. Link GoogleTest libraries
target_link_libraries(run_tests gtest_main)

# 5. Enable CTest support
include(GoogleTest)
gtest_discover_tests(run_tests)