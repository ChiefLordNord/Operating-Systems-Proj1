//Antonio Chieffallo
//3/28/2025

#include "prodCons.hpp"
using std::cout; using std::endl;

// Helper function to produce a value and place it in shared memory
void produceValue(sharedMem* mem, int value) {
    int prod_first = rand() % 2;
    int prod_second = prod_first == 0 ? 1 : 0;

    if(mem->arr[prod_first] == 0) {
        cout << "Producer made: \t" << value << endl;
        mem->arr[prod_first] = value;
    } else if (mem->arr[prod_second] == 0) {
        cout << "Producer made: \t" << value << endl;
        mem->arr[prod_second] = value;
    }
}

int main() {

    // Open or create shared memory and handle errors

    int fd = shm_open("/sharedmemry", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if(fd == -1) {
        cout << "Error with shm_open: " << errno << endl;
    }
    
    // Resize shared memory to fit the structure

    struct sharedMem *mem;
    int err = ftruncate(fd, sizeof(*mem));
    if(err == -1) { 
        cout << "Error with ftruncate: " << errno << endl;
    }

    // Map shared memory and handle errors

    mem = static_cast<sharedMem*>(mmap(NULL, sizeof(*mem), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
    if(mem == MAP_FAILED) {
        cout << "Error with mmap: " << errno << endl;
    }
    
    // Close the file descriptor

    close(fd);

    // Initialize semaphore and shared memory array

    sem_init(&(mem->semaphore), 1, 1);
    mem->arr[0] = 0; // Initialize first slot to 0 (empty)
    mem->arr[1] = 0; // Initialize second slot to 0 (empty)


    // Main producer loop: generates values, places them in shared memory, and ensures synchronization.

    srand(time(nullptr));
 
    for(int i = 0; i < 25; ++i) {

        // Wait for access to the critical section.

        sem_wait(&(mem->semaphore));

        // Produce a value between 1 and 100 (0 represents empty)

        int value = (rand() % 100) + 1;

        // Use helper function to place value in shared memory
        produceValue(mem, value);

        // Signal other programs that the critical section is free

        sem_post(&(mem->semaphore));
        
        // Wait for a second half the time.
        
        sleep(rand() % 2);
    }
    
        // Destroy shared semaphore.
    
    sem_destroy(&(mem->semaphore));

    // Unlink shared memory and handle errors
   
    fd = shm_unlink("/sharedmemry");
    if(fd == -1) {
        cout << "Error with shm_unlink: " << errno << endl;
    }

    exit(EXIT_SUCCESS);
}