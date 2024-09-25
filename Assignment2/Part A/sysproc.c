#include <stddef.h>
#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "processes_info.h"

// // Return Number of active processes
// sys_getNumProc(void)
// {
// 	return getNumProc();
// }

// // Return Maximum PID among all active processes
// int 
// sys_getMaxPid(void)
// {
// 	return getMaxPid();	
// }	

// // Return Information about process with given PID
// int 
// sys_getProcInfo(void)
// {
// 	int pid;
// 	struct processInfo *p;
  
//   // fetching process id into variable pid from user stack to kernel space.
//   // 0 specifies that first command line argument value is taken for fetching value into pid  
// 	argptr(0, (void *)&pid, sizeof(pid));

//   // fetching struct processInfo into variable p from user stack to kernel space.
//   // 1 specifies that second command line argument value is taken for fetching value into p
//   argptr(1, (void *)&p, sizeof(p));
	
//   return getProcInfo(pid, p);
// }

// // To set process burst time
// int 
// sys_set_burst_time(void)
// {
// 	int burst_time;

//   // Fetch the burst_time from user space to kernel space and 
//   // if pointer doesn't lies within the process address space then -1 is returned. 
// 	if(argint(0, &burst_time) <0)
// 		return -1;

// 	return set_burst_time(burst_time);
// }

// // To get recently set burst time
// int sys_get_burst_time(void)
// {
//   // function is called from proc.c from which the kernel code returns the burst time of currently running process
// 	return get_burst_time();
// }


int sys_settickets(void){
  int num_of_tickets;
  // Error
  argptr(0, (void*)&num_of_tickets,sizeof(num_of_tickets));
  if(num_of_tickets <= 0)  
    return -1;

  acquire(&ptable.lock);
  setproctickets(myproc(), num_of_tickets);
  release(&ptable.lock);

  return 0;
}

int sys_getpinfo(void)
{
  struct processes_info* target;
  argptr(0,(void*)&target,sizeof(*target));

  if(target == NULL)
    return -1;

  acquire(&ptable.lock);
  struct proc* p;
  target->num_processes=0;
  int index=0;
  for(p=ptable.proc;p != &(ptable.proc[NPROC]); p++)
    {
      if(p->state != UNUSED)
        {
          target->num_processes++;
          target->pids[index] = p->pid;
          target->ticks[index] = p->ticks;
          target->tickets[index] = p->tickets;
          index++;
        }
    }
  release(&ptable.lock);
  return 0;
}

int sys_yield(void)
{
  yield();  // Call the actual yield function
  return 0;
}

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
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

int
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

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
