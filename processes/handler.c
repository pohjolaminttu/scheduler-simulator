#include "../common.h"

int main()
{
    printf("\n\033[3;90mStarting handler, PID: %i\n\033[0m", getpid());

    key_t key = ftok(FILENAME, PROJECT_ID);
    char reqDnn[4] = "DNN";
    char reqTran[12] = "Transformer";

    /*Let's start by attching to the shared memory made by scheduler*/
    int shMemId = shmget(key, sizeof(struct SharedData), 0666); /*Without IPC_CREAT, attaching to an existing one*/
    struct SharedData *data_ptr = (struct SharedData *)shmat(shMemId, NULL, 0);

    /*We'll read the input from a user*/
    printf("\nEnter inference request (obj det / text gen): ");
    char infReq[9]; /*inference request*/
    fgets(infReq, sizeof(infReq), stdin);
    infReq[strcspn(infReq, "\n")] = '\0';

    /*Now we send the request type to scheduler via shared memory*/
    if (strcmp("obj det", infReq) == 0) /*IF USER TYPED "obj det" -> "DNN" is written to shared memory*/
    {
        strcpy(data_ptr->task_type, reqDnn);
        data_ptr->ready = 1;
    }
    else if (strcmp("text gen", infReq) == 0) /*IF USER TYPED "text gen" -> "Transformer" is written to shared memory*/
    {
        strcpy(data_ptr->task_type, reqTran);
        data_ptr->ready = 1;
    }
    else /*We don't allow other inputs*/
    {
        printf("Incorrect input!");
    }

    /*Now we wait until scheduler has made its scheduling decision*/
    while (data_ptr->ready != 2)
    {
        sleep(1);
    }
    /*Read the returning (when ready = 2)*/
    printf("\nHANDLER: Scheduler decision: %s\n", data_ptr->cluster);

    /*Forks a child*/
    int pid = fork();
    if (pid < 0)
    {
        printf("\033[31mFork error.");
        return 1;
    }
    else if (pid == 0)
    {
        printf("\n\033[32mChild forked succesfully!\033[0m");
        printf("\nPID: %i\nTask:%s\nCluster%s\n", pid, data_ptr->task_type, data_ptr->cluster);
    }

    /*Detach and delete*/
    shmdt(data_ptr);
    shmctl(shMemId, IPC_RMID, NULL);

    return 0;
}