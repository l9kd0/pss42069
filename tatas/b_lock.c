#include "b_lock.h"
#include "time.h"

void lock(volatile int*lock_m) {

    long wait_time = 10;

    struct timespec ts = {
        0, wait_time
    };

    // Try test and set
    while(test_and_set(lock_m)) {
        // Wait until lock_m is 0
        while (*lock_m) {
            nanosleep(&ts, &ts);
            wait_time *= 2;
            ts.tv_nsec = wait_time;
        }
    }
    // Now free to execute -->

    return;
}

int test_and_set(volatile int*lock_m) {

    int res;

    // Calling testandlock
    asm ("movl $1, %0\n"
        "xchgl %0, (%1)\n"
        :"=a"(res)
        :"b" (lock_m)
    );

    return res;
}

void unlock(volatile int*lock_m) {

    // Calling unlock
    asm("movl $0, %%ebx\n" // Setting 0 to eax
        "xchgl %%ebx, (%0)\n" // Setting lock_m to 0 (freeing)
        :
        :"a" (lock_m)
        );

    return;
}
