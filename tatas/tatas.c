#ifdef BACKOFF
  #include "b_lock.h"
#endif

#ifndef BACKOFF
  #include "lock.h"
#endif

#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include <stdio.h>

#define NBSC 6400 // Defining total number of critical sections

// Number of threads
int NB_THREADS = 0;
pthread_t* ham;
volatile int lk=0;

// Make some pizza
void* mcdonald(){

    for(int i = 0; i < NBSC / NB_THREADS; i++){
        lock(&lk); // Locking

        while(rand() > RAND_MAX/10000);

        unlock(&lk);

    }

    return NULL;
}

int main(int argc, char **argv){
    int opt;

    while((opt = getopt(argc, argv, "P:")) != -1)
    {
        if(opt=='P')NB_THREADS=atoi(optarg);
    }

    // Debug
    //printf("Making %d hamburgers with %d mcdonalds.\n", NBSC, NB_THREADS);

    // Allocating memory
    ham = malloc(NB_THREADS*sizeof(pthread_t));

    // Creating threads
    for(int i=0;i<NB_THREADS;i++){
        pthread_create(ham+i,NULL,&mcdonald,NULL);
    }

    // Joining threads
    for(int i=0;i<NB_THREADS;i++){
        pthread_join(ham[i],NULL);
    }

    return 0;
}
