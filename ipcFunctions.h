#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h> 
#include <sys/wait.h> 
#include <stdlib.h>

int semaphoreWait(int semid, int semindex);
int semaphoreSignal(int semid, int semindex);
int messageSend(long type, int action, int messageBox);