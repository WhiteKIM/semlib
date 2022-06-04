#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <semaphore.h>
#include "semlib.h"

int semInit(key_t key)
{
	int semid;
	if((semid=semget(key, 1, 0600 | IPC_CREAT)) < 0)
	{
		perror("semInit error");
		return -1;
	}
	return semid;
}

int semInitValue(int semid, int value)
{
	semun sem;
	sem.val = value;
	if(semctl(semid, 0, SETVAL, sem) < 0)
	{
		perror("semInitValue error");
		return -1;
	}
	return semid;
}

int semWait(int semid)
{
	struct sembuf sem;
	sem.sem_num = 0;
	sem.sem_op = -1;
	sem.sem_flg = SEM_UNDO;
	if(semop(semid, &sem, 1) < 0)
	{
		perror("semWait error");
		return -1;
	}
	return 0;
}

int semTryWait(int semid)
{
	struct sembuf sem;
        sem.sem_num = 0;
        sem.sem_op = -1;
        sem.sem_flg = IPC_NOWAIT;
        if(semop(semid, &sem, 1) < 0)
        {
                perror("semNoWait error");
                return -1;
        }
        return 0;
}

int semPost(int semid)
{
	struct sembuf sem;
        sem.sem_num = 0;
        sem.sem_op = 1;
        sem.sem_flg = SEM_UNDO;
        if(semop(semid, &sem, 1) < 0)
        {
                perror("semPost error");
                return -1;
        }
        return 0;
}

int semGetValue(int semid)
{
	semun sem;
	return semctl(semid, 0, GETVAL, sem);
}

int semDestroy(int semid)
{
	semun sem;
	if(semctl(semid, 0, IPC_RMID, sem) < 0)
	{
		perror("semDestroy error");
		return -1;
	}
	close(semid);
	return 0;
}
