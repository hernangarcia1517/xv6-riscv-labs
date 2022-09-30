enum uprocstate { UNUSED, USED, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

struct uproc {
	int pid; //process id
	enum uprocstate state; // process state
	uint64 size; // size of process memory(bytes)
	int ppid; // parent id
	char name[16]; // process command name
	uint cputime;
};
