#include "lock.h"

int lock_m = 0;

void lock() {

    // Getting result of test and lock
    int res = 0;

    // Calling testandlock
    asm ("movl $1, %%eax\n"
        "xchgl %%eax, %0\n"
        :"=r"(res)
        :"m" (lock_m)
        :"eax"
    );

    // If res not 0 (not free) attempt again
    if (res != 0)
        lock();

    return;
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