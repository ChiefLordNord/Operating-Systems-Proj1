//Antonio Chieffallo
//3/28/2025

#include "prodCons.hpp"
using std::cout; using std::endl;

int main() {

    // Open or create shared memory, print on error.

    int fd = shm_open("/sharedmemry", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if(fd == -1) {
        cout << "Error with shm_open: " << errno << endl;
    }

    // Resize shared memory to fit the structure, print on error.

    struct sharedMem* mem;
    int err = ftruncate(fd, sizeof(*mem));
    if(err == -1) { 
        cout << "Error with ftruncate: " << errno << endl;
    }

    // Map shared memory and handle errors.
    
    mem = static_cast<sharedMem*>(mmap(NULL, sizeof(*mem), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
    if(mem == MAP_FAILED) {
        cout << "Error with mmap: " << errno << endl;
    }
    close(fd);

    // Stops deadlocking.
    sleep(2);

    // Loop to consume items, ensuring mutual exclusivity with semaphore.

    for(int i = 0; i < 25; ++i) {
        // Wait for access to the critical section
        sem_wait(&(mem->semaphore));

        // Determine the order of slots to check
        int slots[2] = {rand() % 2, 0};
        slots[1] = 1 - slots[0];

        // Attempt to consume an item from the slots
        for(int slot : slots) {
            if(mem->arr[slot] != 0) {
                cout << "Consumer took: \t" << mem->arr[slot] << endl;
                mem->arr[slot] = 0;
                break;
            }
        }

        // Release the semaphore
        sem_post(&(mem->semaphore));

        // Random delay
        sleep(rand() % 2);
    }

    exit(EXIT_SUCCESS);
}