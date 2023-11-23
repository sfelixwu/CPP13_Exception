
// original source (from)
// https://stackoverflow.com/questions/2350489/how-to-catch-segmentation-fault-in-linux

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
segfault_sigaction
(int signal, siginfo_t *si, void *arg)
{
  printf("Caught segfault at address %p\n", si->si_addr);
  exit(0);
}

int
main(void)
{
  int *foo = (int *) 256;
  // int *foo = (int *) 0;
  struct sigaction sa;

  memset(&sa, 0, sizeof(struct sigaction));
  sigemptyset(&sa.sa_mask);
  sa.sa_sigaction = segfault_sigaction;
  sa.sa_flags     = SA_SIGINFO;
  
  sigaction(SIGSEGV, &sa, NULL);

  /* Cause a seg fault */
  *foo = 1;

  return 0;
}
