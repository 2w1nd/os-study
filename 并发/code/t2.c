#include <stdio.h>
#include <pthread.h>

int done = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void thr_exit() {
  pthread_mutex_lock(&m);
  done = 1;
  pthread_cond_signal(&c);
  pthread_mutex_unlock(&m);
}

void *child(void *args) {
  printf("child\n");
  thr_exit();
  return NULL;
}

void thr_join() {
  pthread_mutex_lock(&m);
  // 这里done和while循环的设置都是必须且精巧的的
  while (done == 0) 
    pthread_cond_wait(&c, &m);
  pthread_mutex_unlock(&m);
}
// 无论是子线程比父线程慢执行还是快执行，这个程序都是正确的
int main(int argc, char *argv[]) {
  printf("parent: begin\n");
  pthread_t p;
  pthread_create(&p, NULL, child, NULL);
  thr_join();
  printf("parent: end\n");
  return 0;
}
