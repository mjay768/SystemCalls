#ifndef DATA_H
#define DATA_H


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/shm.h>


typedef struct {
    
    pid_t pids[18];
    int pidJob[18];
    int req_nanos[18];

    int resources[20];
    int alloc[18][20];
    int req[18][20];

}resDescriptor;

typedef struct {
    uint secs;
    uint nanos;
} Clock;

#endif