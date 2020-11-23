#include "lock.h"
#include <stdio.h>

void lock(volatile int*lock_m) {

    // Getting result of test and lock
    int res = 0;

    do{

      // Calling testandlock
      asm ("movl $1, %0\n"
          "xchgl %0, (%1)\n"
          :"=a"(res)
          :"b" (lock_m)
      );

      // If res not 0 (not free) attempt again
    }while(res != 0);

    return;
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

  // protecting semaphore counter
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
