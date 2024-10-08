#include "syscall.h"
#include "traps.h"

#define SYSCALL(name) \
  .globl name; \
  name: \
    movl $SYS_ ## name, %eax; \
    int $T_SYSCALL; \
    ret

SYSCALL(fork)
SYSCALL(exit)
SYSCALL(wait)
SYSCALL(pipe)
SYSCALL(read)
SYSCALL(write)
SYSCALL(close)
SYSCALL(kill)
SYSCALL(exec)
SYSCALL(open)
SYSCALL(mknod)
SYSCALL(unlink)
SYSCALL(fstat)
SYSCALL(link)
SYSCALL(mkdir)
SYSCALL(chdir)
SYSCALL(dup)
SYSCALL(getpid)
SYSCALL(sbrk)
SYSCALL(sleep)
SYSCALL(uptime)
# For creating an interface for your user program to access system call from user.h, we added the below lines in usys.S.

SYSCALL(yield)
SYSCALL(settickets)
SYSCALL(getpinfo)
# SYSCALL(getNumProc)
# SYSCALL(getMaxPid)
# SYSCALL(getProcInfo)
# SYSCALL(set_burst_time)
# SYSCALL(get_burst_time)