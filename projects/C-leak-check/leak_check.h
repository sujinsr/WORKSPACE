#ifndef LEAK_CHECK_H
#define LEAK_CHECK_H

/* prototype declaration */
int             sinit_leakcheck();
void            display_leakinfo();
void *          lc_malloc(unsigned long size);
void            lc_free(void *addr);
void *          lc_calloc(unsigned long count, unsigned long size);
void *          lc_realloc(void *addr, unsigned long size);
char *          lc_strdup(const char *str);

#define malloc(size)	        lc_malloc(size)
#define calloc(count, size)     lc_calloc(count, size)
#define realloc(addr, size)     lc_realloc(addr, size)
#define strdup(str)             lc_strdup(str)
#define free(addr)              lc_free(addr)


#endif //LEAK_CHECK_H
