#include "../common.h"

int main()
{
    printf("\n\033[3;90mStarting scheduler, PID: %i\n\033[0m", getpid());

    key_t key = ftok(FILENAME, PROJECT_ID);

    /*Let's first create the shared memory*/
    int shMemId /*Shared memory id*/
        = shmget(key, sizeof(struct SharedData), 0666 | IPC_CREAT);

    /*Then we have to attach to that created (shared) memory*/
    struct SharedData *data_ptr /*Pointer to the address of the shared memory*/
        = (struct SharedData *)shmat(shMemId, NULL, 0);

    data_ptr->ready = 0;
    printf("\033[3;32mScheduler ready and waiting...\033[0m\n");

    /*Read from handler. When ready = 1, choose the cluster based on task type*/
    while (data_ptr->ready != 1)
    {
        sleep(1);
    }

    printf("\nSCHEDULER: Data gotten via shared memory from handler:%s", data_ptr->task_type);
    if (strcmp(data_ptr->task_type, "DNN") == 0)
    {
        strcpy(data_ptr->cluster, "DLA");
        data_ptr->ready = 2;
    }
    else
    {
        strcpy(data_ptr->cluster, "GPU");
        data_ptr->ready = 2;
    }

    printf("\n\033[3;90mStopping the scheduler... \033[0m\n");
    /*Detach the memory*/
    shmdt(data_ptr);
    return 0; /*To indicate that the program has ended succesfully*/
}
