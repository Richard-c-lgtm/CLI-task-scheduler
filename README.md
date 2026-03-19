# CLI Task Scheduler

A lightweight command-line task management tool written in C, simulating task queue patterns common in embedded and robotics systems.

## Features

- Add, complete, and delete tasks via CLI
- Heap-based priority queue — urgent tasks are always processed first
- File persistence — tasks are automatically saved and restored between sessions
- Safe user input handling — no crashes on invalid or oversized input

## Technical Highlights

### Heap-Based Priority Queue
Tasks are stored in a max-heap backed by a fixed-size array. Every insertion runs `sift_up` in O(log n), ensuring the highest-priority task is always accessible at the heap root in O(1) — no sorting required.

Completing a task always pops the heap root (`tm_complete` = `tm_pop`), which reflects real embedded task scheduler behavior: the most urgent task is always handled next.

### Data Structure Design
The `TaskManager` struct holds the heap array, current size, capacity, and an auto-incrementing ID counter. Individual `Task` structs contain only task-specific data. This separation keeps the heap management logic independent from task data.

Fixed-size allocation (`128` slots) was chosen deliberately over dynamic resizing to reflect embedded system constraints where memory is bounded and predictable. 

### Deletion from Arbitrary Position
`tm_delete` locates the target node by linear search (O(n) — unavoidable since heap order is not based on ID), replaces it with the last element, decrements size, then runs both `sift_up` and `sift_down` to restore heap validity regardless of whether the replacement node moves up or down.

### File Persistence
Tasks are stored in a pipe-delimited `.txt` file:
```
size|nextId
id|name|priority|due_date|status
```
On startup, `storage_load` parses the file and rebuilds the heap. On exit, `storage_save` writes all current tasks back. Completed tasks are freed immediately and never written to disk — consistent with embedded systems where task history is not required.

### Safe Input Handling
`read_int` and `read_str` in `utils.c` guard against invalid input, buffer overflows, and empty input. Error states return `INVALID_INPUT` (defined via `#define`) for integers, and an empty string for string reads — allowing clean error checking in the caller without relying on magic numbers.

## Project Structure

```
CLITaskScheduler/
├── main.c        # Entry point, main loop, menu interaction
├── task.h        # Struct definitions, function declarations
├── task.c        # Heap operations: push, pop, peek, delete, sift_up, sift_down
├── storage.h
├── storage.c     # File I/O: load and save tasks
├── utilis.h
└── utilis.c      # Input handling and formatted output
```

## Background

Built as a learning project to practice C fundamentals relevant to embedded and robotics development — including dynamic memory management, data structures, file I/O, and modular code organization.
