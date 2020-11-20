#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

// Declaring simulations functions
void prepare_data(){};
void write_database(){};
void process_data(){};
void read_database(){};

// Variables
pthread_mutex_t mutex_readcount;  // protège readcount
pthread_mutex_t mutex_writecount; // protège writecount
pthread_mutex_t mutex_z;
sem_t sem_read;
sem_t sem_write;
int readcount = 0; // nombre de readers
int writecount = 0;
int nb_pro = 8, nb_con = 8;
pthread_t *pro;
pthread_t *con;

// Writer code
void *writer(void *t)
{
  while (1)
  {
    prepare_data(); // Simulation

    pthread_mutex_lock(&mutex_writecount); // Locking in order to change number of writers
    writecount++;
    if (writecount == 1)
    {
      sem_wait(&sem_read);
    }
    pthread_mutex_unlock(&mutex_writecount);

    sem_wait(&sem_write); // Waiting

    write_database(); // Critical section

    sem_post(&sem_write); // Freeing

    pthread_mutex_lock(&mutex_writecount); // Changing number of writers
    writecount--;
    if (writecount == 0)
    {
      sem_post(&sem_read);
    }
    pthread_mutex_unlock(&mutex_writecount); // Leaving
  }
  return 0;
}

// Reader code
void *reader(void *t)
{
  while (1)
  {
    pthread_mutex_lock(&mutex_z);
    sem_wait(&sem_read);

    pthread_mutex_lock(&mutex_readcount); // Locking in order to change number of readers
    // section critique
    readcount++;
    if (readcount == 1)
    { // arrivée du premier reader
      sem_wait(&sem_write);
    }
    pthread_mutex_unlock(&mutex_readcount); // Unlocking

    sem_post(&sem_read);
    pthread_mutex_unlock(&mutex_z);

    read_database(); // Critical section (not really)

    pthread_mutex_lock(&mutex_readcount); // Locking in order to change number of readers
    // section critique
    readcount--;
    if (readcount == 0)
    { // départ du dernier reader
      sem_post(&sem_write);
    }
    pthread_mutex_unlock(&mutex_readcount); // On libère les mutex
    process_data();                         // Processing data at the end
  }
  return 0;
}

int main(int argc, char **argv)
{

  int opt;

  // Getting args
  while ((opt = getopt(argc, argv, "P:C:")) != -1)
  {
    if (opt == 'P')
      nb_pro = atoi(optarg);
    else if (opt == 'C')
      nb_con = atoi(optarg);
    //else printf("unknown option: %c\n", optopt); // DEBUG
  }
  //printf("Running with %d producers and %d consumers.\n",nb_pro,nb_con); // DEBUG

  // Checking if args are correct
  if (nb_pro + nb_con <= 1)
  {
    return 0;
  } // time is infinite in this case

  // Allocating memory
  pro = malloc(nb_pro * sizeof(pthread_t));
  con = malloc(nb_con * sizeof(pthread_t));

  // init sem
  sem_init(&sem_read, 0, 1);
  sem_init(&sem_write, 0, 1);

  // Creating threads
  for (int i = 0; i < nb_pro; i++)
  {
    pthread_create(pro + i, NULL, &writer, NULL);
  }
  for (int i = 0; i < nb_con; i++)
  {
    pthread_create(con + i, NULL, &reader, NULL);
  }

  // Joining threads
  for (int i = 0; i < nb_pro; i++)
  {
    pthread_join(pro[i], NULL);
  }

  for (int i = 0; i < nb_con; i++)
  {
    pthread_join(con[i], NULL);
  }

  return 0;
}
