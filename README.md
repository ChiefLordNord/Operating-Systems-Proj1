Programming Assignment #1 In this programming assignment, you must provide the source codes, documents, and examples ;in detail on Github. They will be counted for the final score. Please submit the link to the project on Github.

Requirements:

    You are required to use C/C++ in Linux/Unix. You can consider installing VirtualBox in your non-Linux environment.
    Programs must succeed in compilation and execution as required (80 points)
    Readme, documentation and example are required (20 points).

Topic: Producer-Consumer Problem

The producer generates items and puts items onto the table. The consumer will pick up items. The table can only hold two items at the same time. When the table is complete, the producer will wait. When there are no items, the consumer will wait. We use semaphores to synchronize producer and consumer. Mutual exclusion should be considered. We use threads in the producer program and consumer program. Shared memory is used for the “table”.

We expect to use these two programs (producer and consumer) like this:

$ gcc producer.c -pthread -lrt -o producer $ gcc consumer.c -pthread -lrt -o consumer $ ./producer & ./consumer &

This project implements the Producer-Consumer Problem using C++ on a Linux/Unix environment. The problem involves a producer generating items and placing them on a shared "table" (represented by shared memory), while a consumer picks up items from the table. The table can hold a maximum of two items at a time, and synchronization is achieved using semaphores to ensure mutual exclusion and proper coordination between the producer and consumer.

Key Components:
1. Shared Memory:
   - The table is implemented as a shared memory structure (`sharedMem`) defined in `prodCons.hpp`. It contains:
     - An array `arr[2]` to hold up to two items.
     - A semaphore `semaphore` to synchronize access.

2. Producer:
   - Implemented in `producer.cpp`.
   - Generates random values between 1 and 100 and places them in the shared memory.
   - Waits if the table is full and resumes when space becomes available.

3. Consumer:
   - Implemented in `consumer.cpp`.
   - Picks up items from the shared memory.
   - Waits if the table is empty and resumes when items are available.

4. Synchronization:
   - Semaphores are used to ensure mutual exclusion and proper synchronization between the producer and consumer.

5. Build and Execution
   - The project can be built and executed using the provided `makefile`.
   - Alternatively, commands for manual compilation and execution are provided in `example.txt` and the README.md.

Example Workflow:
1. Compile the programs:

   g++ producer.cpp -pthread -lrt -o producer
   g++ consumer.cpp -pthread -lrt -o consumer

2. Run the producer and consumer simultaneously:

   ./producer & ./consumer

Output:
The producer generates items and displays messages like:

Producer made:  66

The consumer picks up items and displays messages like:

Consumer took:  66

This project demonstrates the use of shared memory, semaphores, and multithreading to solve a classic synchronization problem.