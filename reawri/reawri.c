#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

void lock(pthread_mutex_t *a){pthread_mutex_lock(a);}
void unlock(pthread_mutex_t *a){pthread_mutex_unlock(a);}
void wait(sem_t *a){sem_wait(a);}
void post(sem_t *a){sem_post(a);}

pthread_mutex_t wc,rc,z;
sem_t data, green;
int nbr=0,nbw=0,r_threads,w_threads;

pthread_t *r,*w;


void *writer(void *m){
  int a = *((int*)m);
  for(int i=0;i<a;i++){

      lock(&wc);
        if(++nbw==1)wait(&green);// Waiting green lights
      unlock(&wc);

      wait(&data);
        while(rand() > RAND_MAX/10000); // Writing
      post(&data);

      lock(&wc);
        if(--nbw==0)post(&green);// All pending writers are done, green lights on
      unlock(&wc);
  }
  return NULL;
}

void *reader(void *m){
  int a = *((int*)m);
  for(int i=0;i<a;i++){

      lock(&z);
        wait(&green);// Waiting for green lights
        lock(&rc);
          if(++nbr==1)wait(&data);// Waiting end of writing
        unlock(&rc);
        post(&green);// Sending green lights for any reader (and any writer if last reader)
      unlock(&z);

        while(rand() > RAND_MAX/10000); // Accessing

      lock(&rc);
        if(--nbr==0)post(&data);// Allowing writing again
      unlock(&rc);

  }
  return NULL;
}

int main(int argc, char **argv){
  int opt;

  while((opt = getopt(argc, argv, "R:W:")) != -1)
  {
      if(opt=='R')r_threads=atoi(optarg);
      else if(opt=='W')w_threads=atoi(optarg);

  }

  r = (pthread_t*)malloc(r_threads*sizeof(pthread_t));
  w = (pthread_t*)malloc(w_threads*sizeof(pthread_t));

  sem_init(&data, 0 , 1);
  sem_init(&green, 0 , 1);

  for(int i=0;i<w_threads;i++){

    int *k = malloc(sizeof(int));
    *(k) = 640/w_threads+(i==w_threads-1?640%w_threads:0);
    pthread_create(w,NULL,&writer,k);

  }


  for(int i=0;i<r_threads;i++){
    int *k = malloc(sizeof(int));
    *(k) = 640/w_threads+(i==r_threads-1?2560%r_threads:0);
    pthread_create(r,NULL,&reader,k);
  }

  for(int i=0;i<w_threads;i++){
    pthread_join(w[i],NULL);
  }

  for(int i=0;i<r_threads;i++){
    pthread_join(r[i],NULL);
  }


  return 0;
}
