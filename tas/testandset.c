#include "lock.h"
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include <stdio.h>

#define NBSC 6400 // Defining total number of "sections critiques"

// Number of threads
int NB_THREADS = 0;
pthread_t* piz;
volatile int lk=0;

// Make some pizza
void* pizzaiolo(){

    for(int i = 0; i < NBSC / NB_THREADS; i++){
        int a=rand();
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

    // Allocating memory
    piz = malloc(NB_THREADS*sizeof(pthread_t));

    // Creating threads
    for(int i=0;i<NB_THREADS;i++){
        pthread_create(piz+i,NULL,&pizzaiolo,NULL);
    }

    // Joining threads
    for(int i=0;i<NB_THREADS;i++){
        pthread_join(piz[i],NULL);
    }

    return 0;
}
