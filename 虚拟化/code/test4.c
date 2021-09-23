#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int pid = fork();

  if (pid < 0) {
    fprintf(stderr, "fail fork!");
    exit(1);
  } else if (pid == 0) {
    int wc = waitpid(pid, NULL, 0);
    printf("i am child(pid = %d), wc = %d\n", getpid(), wc);
  } else {
    int wc = waitpid(pid, NULL, 0);
    printf("i am parent(pid = %d), wc = %d\n", getpid(), wc);
  }
  return 0;
}
