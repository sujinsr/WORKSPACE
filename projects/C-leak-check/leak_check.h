#ifndef LEAK_CHECK_H
#define LEAK_CHECK_H

#ifdef LEAK_CHECK
#define malloc(size)	lc_malloc(size)
#endif //LEAK_CHECK

#endif //LEAK_CHECK_H
