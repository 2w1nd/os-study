#include "week6.h"

int main(int argc, char *argv[]) {
  int n;
  FILE *from, *to;
  char buf[BUFSIZE];
  if (argc != 3) {
    fprintf(stderr, "Usage: %s from-file to-file\n", *argv);
    exit(1);
  }
  if ((from = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Usage: %s from-file to-file\n", *argv);
    exit(1);
  }
  while ((n = fread(buf, sizeof(char), BUFSIZE, from)) > 0)
    fwrite(buf, sizeof(char), n, to);
  fclose(from);
  fclose(to);
  exit(0);
}