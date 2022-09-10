#include "kernel/param.h"
#include "kernel/types.h"
#include "user/uproc.h"
#include "user/user.h"

struct uproc uproc[NPROC];
int nprocs;

// helper function to output the process tree rooted at pid
// calls itself recursively on any children of pid
void mktree(int indent, int pid, int ppid)
{
  if(pid > nprocs) return;

  int curr_ppid = uproc[pid-1].ppid;
  if(curr_ppid != 0) indent++;
  if(pid == 1 || ppid == curr_ppid){
    for(int i = 0; i < indent; i++){
      printf(" ");
    }
    printf("%s\n", uproc[pid-1].name, uproc[pid-1].ppid);
  }

  mktree(indent, pid+1, pid);



  return;
}

int
main(int argc, char **argv)
{
  int pid = 1;
  if (argc == 2)
    pid = atoi(argv[1]);
  nprocs = getprocs(uproc);
  if (nprocs < 0)
    exit(-1);

  // You can remove the following print statement
  //printf("%d processes\n", nprocs);

  mktree(0, pid, 0);
  exit(0);
}

