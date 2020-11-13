#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>

// Variables
pthread_mutex_t *baguettes;
pthread_t *philosophers;
int nb_philo = 3;

// Declaring functions
void lock(pthread_mutex_t *a) { pthread_mutex_lock(a); }
void unlock(pthread_mutex_t *a) { pthread_mutex_unlock(a); }

// Eat and think
void *eat_and_think(void *pos)
{
  int seat = *((int *)pos);


  for (int i = 0; i < 10000; i++)
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
  baguettes = malloc(nb_philo * sizeof(pthread_mutex_t));
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
