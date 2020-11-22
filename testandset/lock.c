#include "lock.h"

volatile int lock_m = 0;

void lock() {

    // Getting result of test and lock
    int res = 0;

    do{
      // Calling testandlock
      asm ("movl $1, %0\n"
          "xchgl %0, %1\n"
          :"=g"(res)
          :"m" (lock_m)
          :"ebx"
      );

      // If res not 0 (not free) attempt again
    }while(res != 0);

    return;
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
