#include "lock.h"
#include <stdio.h>

volatile int lock_m = 0;

void lock() {

    // Try test and set
    while(test_and_set()) {

        // Wait until lock_m is 0
        while (lock_m) {}
    }

    // Now free to execute -->

    return;
}

int test_and_set() {

    int res;

    // Calling testandlock
    asm ("movl $1, %0\n"
        "xchgl %0, %1\n"
        :"=g"(res)
        :"m" (lock_m)
        :"ebx"
    );

    return res;
}

void unlock() {

    // Calling unlock
    asm("movl $0, %%ebx\n" // Setting 0 to eax
        "xchgl %%ebx, %0\n" // Setting lock_m to 0 (freeing)
        :
        :"m" (lock_m)
        :"ebx");

    return;
}
