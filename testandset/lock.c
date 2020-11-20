#include "lock.h"

void init_lock() {
    __asm__("lockt:\n\t.long 0":::); // Defining lock

    __asm__("testandsetlock:\n\t"               // Defining main loop
            "movl $1, %%eax\n\t"
            "xchgl %%eax, (lockt)\n\t"           // trying to set value to 1
            "testl %%eax, %%eax\n\t"            // if not 0 means lock was not free
            "jnz testandsetlock\n\t":::
    );

    __asm__("unlockt:\n\t" // Defining unlock loop
        "movl $0, %%eax\n\t"
        "xchgl %%eax, (lockt)\n\t":::);

    // TODO check if asm is not removed because of no output registers involved 
    //(gcc might consider the asm as useless and remove it)
}

void lock() {

    // Calling testandlock
    __asm__("jmp testandsetlock");

    return;
}

void unlock() {

    // Calling unlock
    __asm__("jmp unlock");

    return;
}