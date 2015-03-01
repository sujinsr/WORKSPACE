#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

static FILE *writefp;
static pthread_mutex_t mem_handle;

typedef struct
{
    void            *address;
    unsigned long   size;
}memInfo;

typedef struct _memLeak
{
    memInfo mem_info;
    struct _memLeak *next;
}memLeak;

static memLeak *mem_start;
static memLeak *mem_end;

void add_meminfo(void *alloc, unsigned long size);
void rem_meminfo(void *alloc);
void add(memInfo mem_alloc);
void rem(void *memAddr);


int init_leakcheck()
{
    /*writefp = fopen("memory_leak.txt", "w");
    if (writefp == NULL) {
        printf("failed to open mem log file.\n");
        return 1;
    }*/
    
    pthread_mutex_init(&mem_handle, NULL);
}

void* lc_malloc(unsigned long size)
{
    void* alloc = malloc(size);
    if (alloc != NULL) {
        add_meminfo(alloc, size);
    }
    return alloc;
}

void * lc_calloc(unsigned long count, unsigned long size)
{
    unsigned long totalSize;
    void *memPtr = calloc(count, size);
    if (memPtr != NULL) {
        totalSize = count * size;
        add_meminfo(memPtr, totalSize);
    }
    return memPtr;
}

void * lc_realloc(void *addr, unsigned long size)
{
    void *memPtr;
    
    memPtr = realloc(addr, size);
    if (memPtr != NULL) {
        if (addr == NULL) {
            add_meminfo(memPtr, size);
        }
        else {
            rem_meminfo(addr);
            add_meminfo(memPtr, size);
        }
    }
    return memPtr;
}

char * lc_strdup(const char *str)
{
    char *ret_str;
    unsigned long str_size = strlen(str) + 1;
    
    ret_str = strdup(str);
    if (ret_str != NULL) {
        add_meminfo(ret_str, str_size);
    }
    return ret_str;
}

void lc_free(void *addr) 
{
    rem_meminfo(addr);
    free(addr);
}

void add_meminfo(void *alloc, unsigned long size)
{
    memInfo mem_alloc;
    
    memset(&mem_alloc, 0, sizeof(mem_alloc));
    mem_alloc.address = alloc;
    mem_alloc.size = size;
    
    pthread_mutex_lock(&mem_handle);
    add(mem_alloc);
    pthread_mutex_unlock(&mem_handle);
}

void rem_meminfo(void *alloc)
{
    if (alloc == NULL)
        return;
    pthread_mutex_lock(&mem_handle);
    rem(alloc);
    pthread_mutex_unlock(&mem_handle);
}


void add(memInfo mem_alloc)
{
    memLeak *mem_leak_info = NULL;
    
    mem_leak_info = malloc( sizeof(memLeak));
    if (mem_leak_info == NULL) {
        perror("malloc");
        exit(-1);
    }
    mem_leak_info->mem_info.size = mem_alloc.size;
    mem_leak_info->mem_info.address = mem_alloc.address;
    mem_leak_info->next = NULL;
    
    if (mem_start == NULL) {
        mem_start = mem_leak_info;
        mem_end = mem_start;
    }
    else {
        mem_end->next = mem_leak_info;
        mem_end = mem_leak_info;
    }
}

void rem(void *memAddr)
{
    memLeak *delnode, *prev;
    memLeak *memlist_ptr = mem_start;
    
    if (memlist_ptr->mem_info.address == memAddr ) {
        mem_start = memlist_ptr->next;
        delnode = memlist_ptr;
        free(delnode);
        return;
    }
    
    prev = memlist_ptr;
    memlist_ptr = memlist_ptr -> next;
    
    while (memlist_ptr != NULL) {
        if (memlist_ptr->mem_info.address == memAddr) {
            delnode = memlist_ptr;
            prev->next = memlist_ptr->next;
            free(delnode);
            return;
        }
        else {
            prev = prev->next;
            memlist_ptr = memlist_ptr->next;
        }
    }
}


void display_leakinfo() 
{
    memLeak *memlist = mem_start;
    
    printf("-----------------------------MEMORY LEAK----------------------------------------\n");
    
    while(memlist != NULL)
    {
        printf("Address : %p    size : %ld bytes\n", memlist->mem_info.address, memlist->mem_info.size);
        memlist = memlist->next;
    }
    printf("---------------------------------------------------------------------------------\n");
    
    pthread_mutex_destroy(&mem_handle);
}