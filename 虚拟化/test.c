#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  int x = 100;
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "failed fork \n");
    exit(1);
  } else if (rc == 0) {
    x = 200;
    printf("i am child (pid:%d)\n", (int) getpid());
  } else {
    int wc = wait(NULL);
    printf("i am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int) getpid());
  }
  printf("%d\n", x);
  return 0;
}
