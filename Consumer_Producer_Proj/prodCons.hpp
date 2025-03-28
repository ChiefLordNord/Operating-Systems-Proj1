ifndef prodCons_hpp
#define prodCons_hpp

#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <ctype.h>


struct SharedMemory {
    int buffer[2]; // Buffer size of 2
    sem_t empty;    // Semaphore for empty slots
    sem_t full;     // Semaphore for full slots
};

#endif