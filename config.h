#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<sys/wait.h>    
#include<sys/sem.h>
#include<fcntl.h>
#include<errno.h>

#include "data.h"

void time_increment();
void advanceClock();
void initClock();
void clearPCB(int loc);

#define NANO 100000000


int linecount = 0;
int pids[18];

