#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include <semaphore.h>

int main(int argc, char **argv){
  while(rand() > RAND_MAX/10000);
  return 1;
}
