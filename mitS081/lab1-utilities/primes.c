#include "kernel/types.h"
#include "user/user.h"

void handle(int p[]);

int main()
{
  int p[2];
  pipe(p);
  if(fork() == 0) {
    handle(p);
  } else {
    close(p[0]);
    for(int i = 2; i < 36; i++) {
      write(p[1], &i, 4);
    }
    close(p[1]);
    wait((int *) 0);
  }
  exit(0);
}

void handle(int p[]) {
  close(p[1]);
  int index;
  read(p[0], &index, 4);
  printf("prime %d\n", index);
  int num;
  int noChild = 1;
  int cp[2];
  while(read(p[0], &num, 4) != 0) {
    if(num%index != 0) {
      if(noChild) {
        noChild = 0;
	pipe(cp);
	if(fork() == 0) {
	  handle(cp);
	} else {
	  close(cp[0]);
	}
      }
      write(cp[1], &num, 4);
    }
  }
  close(cp[1]);
  close(p[0]);
  wait((int *) 0);
}
