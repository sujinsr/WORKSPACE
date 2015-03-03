#include <stdio.h>
#include "sysv_ipc.h"

/* Function prototype declaration */
static void loadall_ipc();
static void load_shm();
static void load_sem();
static void load_msg();

/* static variable declartion */
struct shmid_ds buf;
struct semid_ds semstru;
struct msqid_ds msqstru;

typedef struct _list
{
    void *          data;
    struct _list *  next
}List;

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
        loadall_ipc();
    }
}

static void loadall_ipc()
{
    load_shm();
    load_shm();
    load_msg();
}

static void load_shm()
{
    printf("load_shm\n");
    
}

static void load_sem()
{
    printf("load_sem");
    
}

static void load_msg()
{
    printf("load_msg\n");
    
}

