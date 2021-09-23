#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
  int pid = fork();
  char *cmd = "/bin/ls";
  char *arg[] = {
    "ls", "-a", NULL
  };

  if (pid < 0) {
    printf("fork error\n");
    exit(1);
  } else if (pid == 0) {
  //  execl(cmd, "ls", NULL);
  //  execlp(cmd, "ls", NULL);
    execve(cmd, arg, envp); // real sys
  } else {
    printf("i am parent\n");
  }
  return 0;
}
