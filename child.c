#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<errno.h>

#define key "/mysem1212"
#define shmkey 0x91919191
int SemID;
int main(int *argc, char *argv[])
{
    int shmid,semid;
    int *count;
    //sem_t *sem;
    //key_t key =  ftok("/mysem1212");
    //sem = sem_open(key,O_CREAT | 0666);
    /*if(sem == SEM_FAILED)
        perror("\n Error opening Semaphore");
    //sem_init(sem,0,0);
    if(sem = SEM_FAILED)
     perror("\n Semaphore not opened"); */
     int SemKey = ftok(key,43);
     if ((SemID = semget(SemKey, 1, 0600 | IPC_CREAT)) == -1) {
		perror("semget Err resource");
        exit(1);
    }
    shmid = shmget(shmkey,sizeof(int), IPC_CREAT | 0777);
    if(shmid ==-1)
    {
        perror("\n SHM Error");
    }
    else printf("\n SHM attached to CHild");
    count = shmat(shmid,0,0);
    printf("\nEntering Critical section\n");
    //sem_wait(sem);
    sem_wait(SemID);
    //sleep(1);
    *count+=1;
    printf("\n Count: %d\n",*count);
    printf("\nExiting critical section\n");
    sem_signal(SemID);
    //sem_post(sem);

    /* if ((semctl(SemID, 0, IPC_RMID, 1) == -1)) {
        perror("oss: resources removed");
        //perror(msgerr);
    }*/
     shmdt(shmid);
    return 0;
}

// Wait Function
void sem_wait(int semid) {
	struct sembuf sbuf;			
	sbuf.sem_num = 0;							
	sbuf.sem_op = -1;							
	sbuf.sem_flg = 0;							
	if (semop(semid, &sbuf, 1) == -1)  {
			exit(0);
	}
	return;
}

// Singal Function
void sem_signal(int semid) {
	struct sembuf sbuf;						
	sbuf.sem_num = 0;							
	sbuf.sem_op = 1;						
	sbuf.sem_flg = 0;						
	if (semop(semid, &sbuf, 1) == -1)  {
			exit(1);
	}
	return;
}
