#ifndef WRAPPERS_H
#define WRAPPERS_H
#include <stddef.h>

void *Malloc(size_t size);
void *Free(void *ptr);
int Access(const char *pathname, int mode);

#endif
