void lock(volatile int*a);
int test_and_set(volatile int*a);
void unlock(volatile int*a);

struct my_sem_t{
  volatile int count;
  volatile int sem_lock;
};
void wait(volatile struct my_sem_t*a);
void post(volatile struct my_sem_t*a);
void my_sem_init(volatile struct my_sem_t*a,int counter);
