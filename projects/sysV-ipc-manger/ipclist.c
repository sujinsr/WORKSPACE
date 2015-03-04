/* Generic linked list implemenation all all three ipc resources */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>

#include "sysv_ipc.h"
#include "ipclist.h"

/* Function prototype declaration */
static Ipclist * create_node(int id, const void *ipc_ds, Listtype type);
static void display_shm(int shmid, struct shmid_ds *shm);
static void display_sem(int semid, struct semid_ds *sem);
static void display_msq(int msqid, struct msqid_ds *msq);


static Ipclist * create_node(int id, const void * ipc_ds, Listtype type)
{
    struct shmid_ds *shmnode = NULL;
    struct semid_ds *semnode = NULL;
    struct msqid_ds *msgnode = NULL;
    Ipclist *newnode = NULL;
    
    newnode = malloc(sizeof(Ipclist));
    if (newnode == NULL) {
        perror("malloc");
        exit(1);
    }

    if (type = SHM_TYPE) {
        shmnode = malloc(sizeof(struct shmid_ds));
        memcpy(shmnode, ipc_ds, sizeof(struct shmid_ds));
        newnode->data = (void *)shmnode;
    }
    else if(type == SEM_TYPE) {
        semnode = malloc(sizeof(struct semid_ds));
        memcpy(semnode, ipc_ds, sizeof(struct semid_ds));
        newnode->data = (void *)semnode;
    }
    else {
        msgnode = malloc(sizeof(struct msqid_ds));
        memcpy(msgnode, ipc_ds, sizeof(struct msqid_ds));
        newnode->data = (void *)msgnode;
    }
    newnode->ipcid = id;
    newnode->next = NULL;
    return newnode;
}


void addto_list(int id, const void * ipc_ds, Listtype type , Ipclist **list_start, Ipclist **list_end)
{
       Ipclist *newnode = NULL;
       
       newnode = create_node(id, ipc_ds, type);
       
       if(*list_start == NULL) {
           *list_start = newnode;
           *list_end = newnode;
       }
       else {
           (*list_end)->next = newnode;
           *list_end = newnode;
       }
        return;
}

static void display_shm(int shmid, struct shmid_ds *shm)
{
    printf("%d      0x%x        %zd         %d\n", 
                shmid, shm->shm_perm.__key, shm->shm_segsz, (int)shm->shm_nattch);
}

static void display_sem(int semid, struct semid_ds *sem)
{
    printf("%d      0x%x        %d\n", 
                semid, sem->sem_perm.__key, (int)sem->sem_nsems);
}

static void display_msq(int msqid, struct msqid_ds *msq)
{
    printf("%d      0x%x        %d\n", 
                msqid, msq->msg_perm.__key, (int)msq->msg_qnum);
}

void display_list(Listtype type, Ipclist *list)
{
    struct shmid_ds *shmnode = NULL;
    struct semid_ds *semnode = NULL;
    struct msqid_ds *msqnode = NULL;
    int count = 0;
    
    while (list != NULL)
    {
        if (type == SHM_TYPE) {
            shmnode = list->data;
            display_shm(list->ipcid, shmnode);
        }
        else if(type == SEM_TYPE) {
            semnode = list->data;
            display_sem(list->ipcid, semnode);
        }
        else {
            msqnode = list->data;
            display_msq(list->ipcid, msqnode);
        }
        list = list->next;
        count ++;
    }
}


