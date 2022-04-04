#include "kernel/types.h"
#include "user/user.h"


int main(int argc, char *argv[]) {
  if(argc < 2) {
    printf("at least two args required");
  }
  char *commands[100];
  int commandsnum = 0;
  char command[512] = {0};
  char *p = command;
  char buf[2];
  char *s;
  while(read(0, buf, 1)) {
    if(buf[0] == '\n') {
      *p = 0;
      s = malloc(strlen(command) + 1);
      strcpy(s, command);
      commands[commandsnum++] = s;
      p = command;
    } else {
      *p++ = buf[0];
    }
  }
  commands[commandsnum] = 0;
  if(fork() == 0) {
    char *execargv[argc + commandsnum];
    for(int i = 0; i < argc - 1; i++) {
      execargv[i] = argv[i + 1];
    }
    for(int i = 0; i < commandsnum; i++) {
      execargv[argc - 1 + i] = commands[i];
    }
    execargv[argc + commandsnum - 1] = 0;
    exec(argv[1], execargv);
    printf("exec failed!\n");
  } else {
    wait((int *)0);
  }
  exit(0);
}
