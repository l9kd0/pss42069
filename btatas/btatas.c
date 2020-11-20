#include "lock.h"
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include <math.h>
#include <stdio.h>

#define NBSC 6400 // Defining total number of "sections critiques"

// Number of threads
int NB_THREADS = 0;
pthread_t* bar;

// Make some beer
void* barman(){

    for(int i = 0; i < floor(NBSC / NB_THREADS); i++){
        lock(); // Locking 

        while(rand() > RAND_MAX/10000);

        unlock();

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
    printf("Making %d beers with %d barmen.\n", NBSC, NB_THREADS);

    //printf("debug %d", test_and_set());
    //unlock();

    return 0; /////// BUGGED FIX SEG FAULT FIRST

    // Allocating memory
    bar = malloc(NB_THREADS*sizeof(pthread_t));

    // Creating threads
    for(int i=0;i<NB_THREADS;i++){
        pthread_create(bar+i,NULL,&barman,NULL);
    }

    // Joining threads
    for(int i=0;i<NB_THREADS;i++){
        pthread_join(bar[i],NULL);
    }

    return 0;
}