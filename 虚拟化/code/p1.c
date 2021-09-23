#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  printf("hello world (pid:%d)\n", (int) getpid());

  int rc = fork();

  if(rc < 0) {
    // fork fail eixt
    fprintf(stderr, "fork failed\n");
  } else if(rc == 0) {
    // child new process
    printf("hello , i am child (pid:%d)\n", (int) getpid());
  } else {
    int wc = wait(NULL);
    // parent goes down this path (main)
    printf("hello, i am parent of %d (pid:%d)\n", rc, (int) getpid());
  }
  return 0;
}
