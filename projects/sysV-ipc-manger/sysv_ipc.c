#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>

#include "sysv_ipc.h"
#include "ipclist.h"

/* Function prototype declaration */
static int load_shm();
static int load_sem();
static int load_msg();
static void display_shm();
static void display_sem();
static void display_msq();

/* static list variable declartion */
static Ipclist *shmlist_start, *shmlist_end;
static Ipclist *semlist_start, *semlist_end;
static Ipclist *msqlist_start, *msqlist_end;

typedef struct _list
{
    void *          data;
    struct _list *  next;
}List;

union semun {
    int                 val;
    struct semid_ds    *buf;
    unsigned short      *array;
    struct seminfo      *__buf;
};

static int load_shm()
{
    struct shmid_ds shmds, *buf;
    int shmCount, shmid, i;
    
    if ((shmCount = shmctl(0, SHM_INFO, &shmds)) == -1) {
        printf("Error: Failed to read total shm count.\n");
        return 1;
    }
    
    for (i = 1; i <= shmCount; i++)
    {
        shmid = shmctl(i, SHM_STAT, &shmds);
        addto_list(shmid, &shmds, SHM_TYPE, &shmlist_start, &shmlist_end);
        //printf("add %d\n", i);
    }
    
    return 0;
}

static int load_sem()
{
    struct semid_ds semds;
    union semun semopts;
    int semCount, semid, i;
    
    semopts.buf = &semds;
    
    if ((semCount = semctl(0, 0, SEM_INFO, semopts)) == -1) {
        printf("Error: Failed to read total semaphore segment.\n");
        return 1;
    }
    
    for (i = 1; i <= semCount; i++)
    {
        semid = semctl(i, 0, SEM_STAT, semopts);
        addto_list(semid, &semds, SEM_TYPE, &semlist_start, &semlist_end);
    }
    return 0;
}

static int load_msg()
{
    struct msqid_ds msqds;
    int msqCount, msqid, i;
    
    if ((msqCount = msgctl(0, MSG_INFO, &msqds)) == -1) {
        printf("Error: Failed to read total message queue.\n");
        return 1;
    }
    
    for (i = 1;  i <= msqCount; i++)
    {
        msqid = msgctl(i, MSG_STAT, &msqds);
        addto_list(msqid, &msqds, MSG_TYPE, &msqlist_start, &msqlist_end);
    }
    return 0;
}

void read_sysvipc( const Cmdarg *cmdOpts)
{
    if (cmdOpts->opts & OPTION_SHM) {
        load_shm();
    }
    else if (cmdOpts->opts & OPTION_SEM) {
        load_sem();
    }
    else if (cmdOpts->opts & OPTION_MSG) {
        load_msg();
    }
    else {
        load_shm();
        load_sem();
        load_msg();
    }
}

static void display_shm()
{
    printf("----- IPC Sharedmemory Segments -----\n");
    printf("shmid       key             size        nattach    \n");
    display_list(SHM_TYPE, shmlist_start);
    printf("\n\n");
}

static void display_sem()
{
    printf("----- IPC Semaphores -----\n");
    printf("semid       key             nsems       \n");
    display_list(SEM_TYPE, semlist_start);
    printf("\n\n");
}

static void display_msq()
{
    printf("----- IPC Message Queues -----\n");
    printf("msqid       key             nmsgs       \n");
    display_list(MSG_TYPE, msqlist_start);
    printf("\n\n");
}

void display_sysvipc( const Cmdarg *cmdOpts)
{
    if (cmdOpts->opts & OPTION_SHM) {
        display_shm();    
    }
    else if (cmdOpts->opts & OPTION_SEM) {
        display_sem();
    }
    else if (cmdOpts->opts & OPTION_MSG) {
        display_msq();
    }
    else {
        display_shm();
        display_sem();
        display_msq();
    }
}




