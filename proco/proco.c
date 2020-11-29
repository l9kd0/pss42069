#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define BUFSIZE 8

// Choosing lock implementation according to compiler arguments
#if defined(TAS)
  #include "../tas/lock.h"
#elif defined(TATAS)
  #include "../tatas/lock.h"
#else
  void lock(pthread_mutex_t *a){pthread_mutex_lock(a);}
  void unlock(pthread_mutex_t *a){pthread_mutex_unlock(a);}
  void wait(sem_t *a){sem_wait(a);}
  void post(sem_t *a){sem_post(a);}
#endif

int BUF[BUFSIZE]={0,0,0,0,0,0,0,0};
// ctr_p next index to produce, ctr_c next index to consume in buffer
int ctr_c=0,ctr_p=0; // Specific counters for consumers and producers
int nb_pro=8, nb_con=8;
pthread_t*pro;
pthread_t*con;

// Required semaphores and mutexes
#if defined(TAS) || defined(TATAS)
  volatile int ctr_m_p, ctr_m_c;
  volatile struct my_sem_t can_consume,can_produce;
#else
  pthread_mutex_t ctr_m_p, ctr_m_c;
  sem_t can_consume, can_produce;
#endif


void* consume(void *m){
  int a = *((int*)m);

  for(int i=0;i<a;i++){
    int cell;
    wait(&can_consume); // Waiting for a new value
    lock(&ctr_m_c); // Locking the consumer counter
      cell=ctr_c++;
      BUF[cell%BUFSIZE]=0; // Array access
      post(&can_produce); // Value is retrieved, may now be erased
    unlock(&ctr_m_c);
    while(rand() > RAND_MAX/10000); // Value is consumed
  }

  return NULL;
}

void* produce(void *m){

  int a = *((int*)m);

  for(int i=0;i<a;i++){
    int cell;
    while(rand() > RAND_MAX/10000); // Simulate new value creation
    wait(&can_produce); // Wait for free space or new erasable values
    lock(&ctr_m_p);

      cell=ctr_p++;

      //if(BUF[cell%BUFSIZE]!=0)printf("WARN-collision occured. %d\n",cell);
      BUF[cell%BUFSIZE]=rand(); // Simulate array access
      post(&can_consume); // Value now available for consumption

    unlock(&ctr_m_p);

  }
  return NULL;
}

int main(int argc, char **argv){
  int opt;

  while((opt = getopt(argc, argv, "P:C:")) != -1)
  {
      if(opt=='P')nb_pro=atoi(optarg);
      else if(opt=='C')nb_con=atoi(optarg);
  }

  if(nb_pro+nb_con<=1){return 0;} // time is infinite in this case

  pro = malloc(nb_pro*sizeof(pthread_t));
  con = malloc(nb_con*sizeof(pthread_t));

  #if defined(TAS) || defined(TATAS)
    my_sem_init(&can_produce,8);
    my_sem_init(&can_consume,0);
  #else
    sem_init(&can_produce, 0 , 8);
    sem_init(&can_consume, 0 , 0);
  #endif

  for(int i=0;i<nb_pro;i++){
    int *k = malloc(sizeof(int));
    *(k) = 1024/nb_pro+(i==nb_pro-1?1024%nb_pro:0);
    pthread_create(pro+i,NULL,&produce,k);
  }
  for(int i=0;i<nb_con;i++){
    int *k = malloc(sizeof(int));
    *(k) = 1024/nb_con+(i==nb_con-1?1024%nb_con:0);
    pthread_create(con+i,NULL,&consume,k);
  }

  for(int i=0;i<nb_pro;i++){
    pthread_join(pro[i],NULL);
  }

  for(int i=0;i<nb_con;i++){
    pthread_join(con[i],NULL);
  }


  return 0;
}
