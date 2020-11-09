#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int BUF[8]={0,0,0,0,0,0,0,0};
int ctr_c=0,ctr_p=0;
int nb_pro=8, nb_con=8;
pthread_mutex_t ctr_m_p, ctr_m_c;
pthread_t*pro;
pthread_t*con;

sem_t can_consume;
sem_t can_produce;

void lock(pthread_mutex_t *a){pthread_mutex_lock(a);}
void unlock(pthread_mutex_t *a){pthread_mutex_unlock(a);}

void* consume(){

  while(1){
    int cell;

    sem_wait(&can_consume);
    lock(&ctr_m_c);
      cell=ctr_c++;
    unlock(&ctr_m_c);
    if(cell>1024){
      sem_post(&can_consume); //unlock everything
      sem_post(&can_produce);
      break;
    }

    BUF[cell%8]=0;

    while(rand() > RAND_MAX/10000);

    sem_post(&can_produce);
  }

  return NULL;
}

void* produce(){

  while(1){
    int cell;

    sem_wait(&can_produce);
    lock(&ctr_m_p);
      cell=ctr_p++;;
    unlock(&ctr_m_p);
    if(cell>1024){
      sem_post(&can_produce); //unlock everything
      sem_post(&can_consume);
      break;
    }

    //if(BUF[cell%8]!=0)printf("WARN-collision occured.");
    BUF[cell%8]=rand();

    while(rand() > RAND_MAX/10000);

    sem_post(&can_consume);

  }

  return NULL;
}

int main(int argc, char **argv){
  int opt;

  while((opt = getopt(argc, argv, "P:C:")) != -1)
  {
      if(opt=='P')nb_pro=atoi(optarg);
      else if(opt=='C')nb_con=atoi(optarg);
      //else printf("unknown option: %c\n", optopt);
  }
  //printf("Running with %d producers and %d consumers.\n",nb_pro,nb_con);

  if(nb_pro+nb_con<=1){return 0;} // time is infinite in this case

  pro = malloc(nb_pro*sizeof(pthread_t));
  con = malloc(nb_con*sizeof(pthread_t));

  sem_init(&can_produce, 0 , 8);
  sem_init(&can_consume, 0 , 0);

  for(int i=0;i<nb_pro;i++){
    pthread_create(pro+i,NULL,&produce,NULL);
  }
  for(int i=0;i<nb_con;i++){
    pthread_create(con+i,NULL,&consume,NULL);
  }

  for(int i=0;i<nb_pro;i++){
    pthread_join(pro[i],NULL);
  }

  for(int i=0;i<nb_con;i++){
    pthread_join(con[i],NULL);
  }


  return 0;
}
