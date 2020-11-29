#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>

// Choosing lock implementation according to compiler arguments
#if defined(TAS)
  #include "../tas/lock.h"
#elif defined(TATAS)
  #include "../tatas/lock.h"
#else
  void lock(pthread_mutex_t *a){pthread_mutex_lock(a);}
  void unlock(pthread_mutex_t *a){pthread_mutex_unlock(a);}
#endif

// Variables
#if defined(TAS) || defined(TATAS)
  int *baguettes;
#else
  pthread_mutex_t *baguettes;
#endif

pthread_t *philosophers;
int nb_philo = 3;

// Eat and think
void *eat_and_think(void *pos)
{
  int seat = *((int *)pos);


  for (int i = 0; i < 100000; i++)
  {

    // Checking if alone
    if (nb_philo == 1)
    {
      lock(&baguettes[seat]);
      unlock(&baguettes[seat]);
      lock(&baguettes[seat]);
      unlock(&baguettes[seat]);
      continue;
    }

    // Checking
    if (seat < (seat + 1) % nb_philo)
    {
      lock(&baguettes[seat]);
      lock(&baguettes[(seat + 1) % nb_philo]);
    }
    else
    {
      lock(&baguettes[(seat + 1) % nb_philo]);
      lock(&baguettes[seat]);
    }
    // EATS
    unlock(&baguettes[(seat + 1) % nb_philo]);
    unlock(&baguettes[seat]);
  }
  return NULL;
}

int main(int argc, char **argv)
{
  int opt;

  // Getting args
  while ((opt = getopt(argc, argv, "N:")) != -1)
  {
    if (opt == 'N')
      nb_philo = atoi(optarg);
    //else printf("unknown option: %c\n", optopt); // DEBUG
  }
  //printf("Running with %d philosophers.\n",nb_philo); // DEBUG

  // Allocating memory
  #if defined(TAS) || defined(TATAS)
    baguettes = malloc(nb_philo * sizeof(int));
  #else
    baguettes = malloc(nb_philo * sizeof(pthread_mutex_t));
  #endif
  philosophers = malloc(nb_philo * sizeof(pthread_t));

  // Creating threads
  for (int i = 0; i < nb_philo; i++)
  {
    int *k = malloc(sizeof(int));
    *(k) = i;
    pthread_create(philosophers + i, NULL, &eat_and_think, k);
  }

  // Joining threads
  for (int i = 0; i < nb_philo; i++)
  {
    pthread_join(philosophers[i], NULL);
  }

  return 0;
}
