#include "../common.h"

int main()
{
    key_t key = ftok(FILENAME, PROJECT_ID);

    /*Let's start by attching to the shared memory made by scheduler.c*/
    int shMemId = shmget(key, 1024, 0666); /*Without IPC_CREAT, attaching to an existing one*/
    char *shMemAdd = shmat(shMemId, NULL, 0);

    /*Read from the memory*/
    printf("Reading: %s", shMemAdd);

    /*Detach and delete*/
    shmdt(shMemAdd);
    shmctl(shMemId, IPC_RMID, NULL);

    return 0;
}
