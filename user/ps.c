/*
 * Skeleton code for ps.c
 */
#include "kernel/param.h"
#include "kernel/types.h"
#include "user/uproc.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
  struct uproc uproc[NPROC];
  struct uproc *u;
  int nprocs;

  /********************************
   * Add any additional variables or data structures you will need
   ********************************/



  nprocs = getprocs(uproc);
  if (nprocs < 0)
    exit(-1);

  printf("pid\tname\tcputime\tppid\n");
  for(u = uproc; u < &uproc[nprocs]; u++){
    printf("%d\t%s\t%d\t%d", u->pid, u->name, u->cputime, u->ppid);
    printf("\n");
  }

  //for(int i = 0; i < nprocs; i++){
    //printf("%d process\n", uproc[i].pid);
  //}

  // You can remove the following print statement
  //printf("%d processes\n", nprocs);

  /*********************************
   * Add your code here to output information returned by getprocs()
   * Hint: see procdump() code in kernel/console.c, except that here
   * you will be outputting the first nprocs elements of the uproc array
   * and all will have active states.
   *********************************/ 





  exit(0);
}

