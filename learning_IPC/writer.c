#include "../common.h"

int main()
{
    key_t key = ftok(FILENAME, PROJECT_ID);

    /*Let's first create the shared memory*/
    int shMemId /*Shared memory id*/
        = shmget(key, 1024 /*One kilobyte, later change this to sizeOf(struct x)*/,
                 0666 | IPC_CREAT);

    /*Then we have to attach to that created (shared) memory*/
    char *shMemAdd /*Pointer to the address of the shared memory*/
        = shmat(shMemId, NULL, 0);

    /*Writing to memory*/
    fgets(shMemAdd, 1024, stdin);

    /*Detach the memory*/
    shmdt(shMemAdd);

    return 0; /*To indicate that the program has ended succesfully*/
}
