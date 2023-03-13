#include <stdio.h>

int main() {
  printf("hello world\n");
  for(int i = 0; i < 100; ++i) {
    printf("in\n");
  }
  if(1) printf("out\n");
  else printf("inin\n");
  return 0;
}
