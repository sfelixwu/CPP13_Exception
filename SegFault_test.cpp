
#include "ecs36b_Common.h"

int
main(void)
{
  int *p;
  // p = NULL;
  p = (int *) 256;
  try {
    printf("*p = %d\n", *p);
  } catch(std::exception& e) {
    printf("I am here %s\n", e.what());   
  }
  return 0;
}
