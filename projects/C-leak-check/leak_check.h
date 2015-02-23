#ifndef LEAK_CHECK_H
#define LEAK_CHECK_H


/* prototype declaration */
int init_leakcheck();
void display_leakinfo();

void* lc_malloc(unsigned long size);
void lc_free(void *addr) ;


#define malloc(size)	lc_malloc(size)
#define free(addr)      lc_free(addr)


#endif //LEAK_CHECK_H
