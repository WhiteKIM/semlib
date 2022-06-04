#ifndef SEMLIB_H
#define SEMLIB_H

typedef union {
	int val;
}semun;

int semInit(key_t key);
int semInitValue(int semid, int value);
int semWait(int semid);
int semTryWait(int semid);
int semPost(int semid);
int semGetValue(int semid);
int semDestroy(int semid);

#endif
