#include "../common.h"

int main()
{
    key_t key = ftok(FILENAME, PROJECT_ID);

    /*Let's start by attching to the shared memory made by scheduler*/
    int shMemId = shmget(key, sizeof(struct SharedData), 0666); /*Without IPC_CREAT, attaching to an existing one*/
    struct SharedData *data_ptr = (struct SharedData *)shmat(shMemId, NULL, 0);

    /*We'll read the input from a user*/
    printf("Enter inference request (obj det / text gen): ");
    char infReq[12]; /*inference request*/
    scanf("%11s", infReq);

    /*Now we send the request type to scheduler via shared memory*/
    strcpy(data_ptr->task_type, infReq);
    strcpy(data_ptr->ready, 1);

    /*TODO read the returning (when ready = 2), do magic and children*/
    /*Detach and delete*/
    shmdt(data_ptr);
    shmctl(shMemId, IPC_RMID, NULL);

    return 0;
}
