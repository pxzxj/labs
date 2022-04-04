#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  printf("sleeping\n");
  if(argc < 2) {
    printf("args required\n");
  } else {
    int s = atoi(argv[1]);
    sleep(s);
  }
  exit(0);
}

