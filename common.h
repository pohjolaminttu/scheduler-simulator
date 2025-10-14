#ifndef COMMON_H /*Let's make sure we don't create COMMON_H more than once*/
#define COMMON_H

#include <stdio.h>
// Next three includes are for functions associated with shared memory
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define FILENAME "common.h"
#define PROJECT_ID 0

#endif