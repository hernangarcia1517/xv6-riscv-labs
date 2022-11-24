#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  if(argaddr(0, &p) < 0)
    return -1;
  return wait(p);
}

uint64
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_getprocs(uint64 addr)
{
  if(argaddr(0, &addr) < 0)
    return -1;
  return procinfo(addr);
}

uint64
sys_freepmem(void)
{
    return kfreepagecount();
}

uint64
sys_sem_init(void)
{
  sem_t sem;
  int pshared;
  int value;

  if((argaddr(0, &sem) < 0)) return -1;

  if((argint(1, &pshared) < 0)) return -1;

  if(pshared != 1) return -1;
  
  if((argint(2, &value) < 0)) return -1;
  
  return sem_init(sem, pshared, value);
}
uint64
sys_sem_destroy(void)
{
  sem_t sem;
  
  if(argaddr(0, &sem) < 0) return -1;

  return sem_destroy(sem);
}
uint64
sys_sem_wait(void)
{
  sem_t sem;
  
  if(argaddr(0, &sem) < 0) return -1;

  return sem_wait(sem);
}
uint64
sys_sem_post(void)
{
  sem_t sem;
  
  if(argaddr(0, &sem) < 0) return -1;

  return sem_post(sem);
}
