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
#include<signal.h>

#define key "/mysem1212"
#define shmkey 0x91919191
int SemID;
int maxlimit = 100;
int flag = 1;
int pids[10];
void semInit();
int main(int * argc, char * argv[])
{
    int i,count=0;
    pid_t pid;
    int status;
    int *scount;
    int shmid;
    int SemKey = ftok(key,43);
    shmid = shmget(shmkey,sizeof(int),IPC_CREAT | 0777);
    if(shmid == -1)
    {
        perror("\n SHM Error");
    }
    scount = shmat(shmid,0,0); 
    *scount = 0;

    if ((SemID = semget(SemKey, 1, 0600 | IPC_CREAT)) == -1) {
		perror("Semaphore Error");
        exit(1);
    }

    semInit();
    while(flag)
    {
        pid = fork();
        if(pid < 0){
            perror("\nFork error\n");
        }
        else if(pid == 0){
            execlp("./child","./child",(char *)NULL);
            exit(0);
        }

        if(pid > 0){
            //printf("\nTotal number of processes forked are %d\n",*scount);
            pids[count] = getpid();
            count++;
            if(count >= maxlimit)
            {
                printf("\nCount Exceeded\n");
                flag = 0;
            }
            printf("\n Children : %d\n",count);
            wait(pid);
            //printf("\nI am parent and my PID %d",getppid());
        }
    }

    tandk();
    //for(i =0;i<10;i++)
    //{
        
    //}


    if ((semctl(SemID, 0, IPC_RMID, 1) == -1) && (errno != EINTR)) {
        perror("Semaphore : Removed");
        //perror(msgerr);
    }
	shmdt(shmid);
	if((shmctl(shmid, IPC_RMID, NULL)) == -1)
	{
	   perror("\n SHM Detach Error\n");	
	} else printf("\nSHM Detached\n");
//sem_unlink("ponagand.");
return 0;
}

void semInit() {
    union semun { int val; struct semid_ds *buf; ushort * array; } argument;
    argument.val = 1;                            // Set the semaphore value to one
    if (semctl(SemID, 0, SETVAL, argument) == -1) {
       perror("oss: semctl (clock)");
        exit(1);
    }
    printf("Initialized Semaphore to 1");

    sem_wait(SemID);                       
    printf("\nIn Sem_Wait\n");
    sem_signal(SemID);                     
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

void tandk()
{
    int i;
    printf("\nTerminating remaining processes");
    for(i= 0;i<maxlimit;i++)
    {
        kill(pids[i], SIGTERM);
    }
}