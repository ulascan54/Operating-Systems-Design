# CSE331 Operating Systems Design

## Overview
This repository contains solutions and documentation for assignments and term projects of the CSE331 Operating Systems Design course at Yeditepe University, Fall 2024. Below is a summary of the tasks for each assignment and project phase.

---

## **Assignments**

### **Assignment 1: UNIX Processes and POSIX Threads**

#### Objective:
Explore and compare three programming paradigms: multi-process, multithreaded (with and without mutual exclusion), and single-process programming, by performing operations on a long array.

#### Tasks:
1. **Multi-Process Program:** Parent process creates child processes, each incrementing elements in its designated subarray. Parent collects results and calculates execution time.
2. **Multi-Threaded Program with Mutual Exclusion:** Threads increment elements in their assigned subarrays with synchronization using mutual exclusion mechanisms.
3. **Multi-Threaded Program without Mutual Exclusion:** Threads increment subarray elements without synchronization.
4. **Single-Process Program:** A single process updates the entire array.

---

### **Assignment 2: POSIX Semaphores and Shared Semaphores**

#### Objective:
Compare multi-process programs with shared semaphores and multi-threaded programs using POSIX semaphores for unsharp filtering of images.

#### Tasks:
1. **Multi-Process Program with Shared Semaphores:**
   - Perform Laplacian filtering followed by matrix subtraction.
   - Use POSIX semaphores to synchronize operations between child processes.
2. **Multi-Threaded Program with POSIX Semaphores:**
   - Similar functionality as the multi-process program, but implemented using threads and POSIX semaphores.

---

## **Term Project**

### **Phase 1: System Calls**
#### Objective:
Implement a new system call in Linux that provides information about the current process.

#### Tasks:
1. Add a system call, `getProcInfoF24`, to return details such as PID, parent PID, user ID, and a calculated value.
2. Write a user-space program to test the system call and demonstrate functionality for valid and invalid inputs.

---

### **Phase 2: Fair-Share Scheduler**
#### Objective:
Modify the Linux scheduler to implement fair-share scheduling and compare its performance with the default scheduler.

#### Tasks:
1. **Implement a New Scheduling Policy:** Modify `kernel/sched.c` to allocate CPU resources fairly among users.
2. **Enable/Disable Custom Scheduler:** Add a system call to toggle the custom scheduler.
3. **Develop Performance Instrumentation:** Collect detailed performance metrics for both schedulers and analyze results.

---

**Prepared for:** CSE331 Operating Systems Design, Yeditepe University, Fall 2024.
**Phase 1, Assigment 1, Assigment 2 Prepared by:** Ulaş Can Demirbağ
**Phase 2 Prepared by:** Ulaş Can Demirbağ, [Mevlüt Akif Şahin](https://github.com/AkifSahn), [Emirhan Tala](https://github.com/Emivvvvv)

