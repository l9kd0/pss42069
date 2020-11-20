#include "lock.h"
#include "time.h"

int lock_m = 0;

void lock() {

    long wait_time = 10;

    struct timespec ts = {
        0, wait_time
    };

    // Try test and set
    while(test_and_set()) {
        
        // Wait until lock_m is 0
        while (lock_m) {
            nanosleep(&ts, &ts);
            wait_time *= 2;
            ts.tv_nsec = wait_time;
        }
    }

    // Now free to execute -->

    return;
}

int test_and_set() {

    int res = 0;

    // Calling testandlock
    asm ("movl $1, %%eax\n"
        "xchgl %%eax, %0\n"
        :"=g"(res)
        :"m" (lock_m)
        :"eax"
    );

    return res;
}

void unlock() {

    // Calling unlock
    asm("movl $0, %%eax\n" // Setting 0 to eax
        "xchgl %%eax, %0\n" // Setting lock_m to 0 (freeing)
        :
        :"m" (lock_m)
        :"eax");

    return;
}