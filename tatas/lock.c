#include "lock.h"
#include <stdio.h>
void lock(volatile int*lock_m) {

    // Try test and set
    while(test_and_set(lock_m)) {

        // Wait until lock_m is 0
        while (*lock_m) {}
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

void wait(volatile struct my_sem_t*sem_m){
  lock(&(sem_m->sem_lock));
    while((sem_m->count<=0));
    (sem_m->count)--;
  unlock(&(sem_m->sem_lock));
}

void post(volatile struct my_sem_t*sem_m){
  (sem_m->count)++;
}

void my_sem_init(volatile struct my_sem_t*sem_m, int count){
  sem_m->count=count;
  sem_m->sem_lock=0;
}
