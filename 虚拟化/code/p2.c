#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  printf("hell world (pid:%d)\n", (int) getpid());
  int rc = fork();
  if (rc < 0) {
    // fork failed: exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    // child new process
    printf("hello, i am child (pid: %d)\n", (int) getpid());
    char *myargs[3];
    myargs[0] = strdup("wc");
    myargs[1] = strdup("p2.c");
    myargs[2] = NULL;
    execvp(myargs[0], myargs);
    printf("this shouldn`t print out");
  } else {
    // parent goes down this path
    int wc = wait(NULL);
    printf("hello , i am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int) getpid());
  }
  return 0;
}
