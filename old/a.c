#include <stdio.h>
#include <time.h>
int main() {
  int program_done = 0;
  time_t start = time();
  while(1){
    if (start - time() >= 30) {
      start = start + 30;
      // insert periodic stuff here
    }
    // do small pieces of work here, no longer than the timer limit.
    // if no work to do, a sleep(1) could be placed here.
    if (program_done){
	printf("done\n");
	break;
    }
  }
}
