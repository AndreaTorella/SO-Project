#include "sem_lib.h"
#include <errno.h>
#include <unistd.h>

#define TEST_ERROR                                 \
    if (errno)                                     \
    {                                              \
        fprintf(stderr,                            \
                "%s:%d: PID=%5d: Error %d (%s)\n", \
                __FILE__,                          \
                __LINE__,                          \
                getpid(),                          \
                errno,                             \
                strerror(errno));                  \
    }

int set_sem(int sem_id, int index, int sem_val)
{
    return semctl(sem_id, index, SETVAL, sem_val);
}

void dec_sem(int sem_id, int index)
{
    struct sembuf sops;
    sops.sem_num = index;
    sops.sem_op = -1;
    sops.sem_flg = 0;
    semop(sem_id, &sops, 1);
}

void rel_sem(int sem_id, int index)
{
    struct sembuf sops;
    sops.sem_num = index;
    sops.sem_op = 1;
    sops.sem_flg = 0;
    semop(sem_id, &sops, 1);
}

void wait_sem_zero(int sem_id, int index)
{
    struct sembuf sops;
    sops.sem_num = index;
    sops.sem_op = 0;
    sops.sem_flg = 0;
    semop(sem_id, &sops, 1);
}

void reset_sem_set(int sem_id, int dim)
{
    int i = 0;
    for (i = 0; i < dim; i++)
    {
        semctl(sem_id, i, SETVAL, 1);
    }
}