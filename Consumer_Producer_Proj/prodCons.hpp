#ifndef prodCons_HPP
#define prodCons_HPP

#include <fcntl.h>           // file control
#include <semaphore.h>       // semaphore functions sem_t
#include <sys/mman.h>        // memory mapping
#include <sys/stat.h>        // shared memory
#include <unistd.h>          // ftruncate, sleep
#include <cstdlib>           
#include <cstdio>

// shared memory 

struct SharedMemory {
    int data[2];      // buffer
    int count;        // items currently in buffer

    sem_t* full;      // pointer to named semaphore for consumer
    sem_t* empty;     // pointer to named semaphore for producer
};

#endif // prodCons_HPP