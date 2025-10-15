#ifndef COMMON_H /*Let's make sure we don't create COMMON_H more than once*/
#define COMMON_H

#include <stdio.h>
#include <string.h>
#include <unistd.h> //for sleep() and fork()
// Next three includes are for functions associated with shared memory
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define FILENAME "common.h"
#define PROJECT_ID 0
#define TT_SIZE 12 /*Task type size, maximum is "transformer" + \0 */
#define C_SIZE 4   /*Cluster size, options are DLA / GPU + \0 */

struct SharedData
{
    char task_type[TT_SIZE];
    char cluster[C_SIZE];
    int ready; /*State of shared memory. 0 =initialized, 1 = handler made changes, 2 = scheduler made changes*/
};

#endif