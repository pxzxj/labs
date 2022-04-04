#include "kernel/types.h"
#include "user/user.h"

int main()
{
  int pico[2];
  int poci[2];
  pipe(pico);
  pipe(poci);
  char buf[2];
  if(fork() == 0) {
    close(poci[1]);
    read(poci[0], buf, 2);
    close(poci[0]);
    printf("%d: received ping\n", getpid());
    close(pico[0]);
    write(pico[1], "a", 1);
    close(pico[1]);
  } else {
    close(poci[0]);
    write(poci[1], "a", 1);
    close(poci[1]);
    close(pico[1]);
    read(pico[0], buf, 2);
    close(pico[0]);
    printf("%d: received pong\n", getpid());
  }
  exit(0);
}
