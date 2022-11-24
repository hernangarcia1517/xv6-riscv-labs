#define NSEM 100

// Mutual exclusion lock.
struct spinlock {
  uint locked;       // Is the lock held?

  // For debugging:
  char *name;        // Name of lock.
  struct cpu *cpu;   // The cpu holding the lock.
};

// counting semaphore
struct semaphore {
struct spinlock lock; int count;
int valid;
// semaphore lock
// semaphore value
// 1 if this entry is in use
};

// OS semaphore table type
struct semtab {
  struct spinlock lock;
  struct semaphore sem[NSEM];
};

//table methods
void seminit(void);
uint64 semalloc(void);
int semdealloc(uint64 s_idx);

//per-semaphore methods
int sem_init(sem_t sem, int pshared, int value);
int sem_destroy(sem_t sem);
int sem_wait(sem_t sem);
int sem_post(sem_t sem);

extern struct semtab semtable;

