#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

//From proc.h Proc structure
// Per-process state
enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };
struct proc {
  enum procstate state; // Process state
  int pid;              // Process ID
  int ppid ;            // Parent process ID
  uint ctime;           // Creation time
  char name[16];        // Process name
};

#define MAX_PROC 10

void ps() {
  struct proc ptable[MAX_PROC];
  struct proc *p;
  int err;
  
  err = getptable(10*sizeof(struct proc), &ptable);
  if(err !=0)
    printf(1,"Error getting ptable");
  
  p = &ptable[0];
  printf(1, "\nPID     STATE     C_TIME      NAME\n");
  while(p != &ptable[MAX_PROC-1] && p->state != UNUSED){
    printf(1,"%d      ", p->pid);
    switch(p->state){
      case UNUSED:
        printf(1," %s       ", "UNUSED");
        break;
      case EMBRYO:
        printf(1," %s       ", "EMBRYO");
      break;
      case SLEEPING:
        printf(1," %s       ", "SLEEPING");
        break;
      case RUNNABLE:
        printf(1," %s       ", "RUNNABLE");
        break;
      case RUNNING:
        printf(1," %s       ", "RUNNING");
        break;
      case ZOMBIE:
        printf(1," %s       ", "ZOMBIE");
        break;
    }
    printf(1, "%d         %s\n",p->ctime, p->name);
    p++;
  }
}

int main(int argc, char *argv[]) {
  int k, n, id, z, d;
  double x;
  
  if (argc < 2) n = 1;
  else n = atoi(argv[1]);
  
  if (n < 0 || n > 20) n = 2;
  
  if (argc < 3) d = 1;
  else d = atoi(argv[2]);
  
  x = 0;
  id = 0;
  
  for (k = 0; k < n; k++) {
    id = fork();
    if (id < 0) printf(1, "%d failed to fork!\n", getpid());
    else if (id > 0) {
      printf(1, "Parent %d creating child %d\n", getpid(), id);
      wait();
    } else {
      for (z = 0; z < 4; z += d) {
        ps();
        x = x + 3.14 * 89.55;
      }
      printf(1, "Child %d ended\n", getpid());
      break;
    }
  }
  exit();
}