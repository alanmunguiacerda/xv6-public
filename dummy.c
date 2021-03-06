#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

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
      printf(1, "Child %d created\n", getpid());
      for (z = 0; z < 400000000; z += d) {
        x = x + 3.14 * 89.55;
      }
      break;
    }
  }
  exit();
}