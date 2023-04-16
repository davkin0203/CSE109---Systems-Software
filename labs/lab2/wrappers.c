#include "wrappers.h"
#include <unistd.h>
#include <stdio.h>   /* for fprintf */
#include <stdlib.h>  /* for size_t, malloc, exit */
#include <errno.h>   /* for errno */
#include <string.h>  /* for strerror */

void *Malloc(size_t size) {
  void *ptr = NULL; /* or = 0; initializing not really needed b/c ptr will always be given a value by malloc call */
  if ((ptr = malloc(size)) == NULL) {  /* error checking and handling */
    fprintf(stderr, "Could not allocated space for %ld bytes - %s", size, strerror(errno));
    exit(errno);
  }
  return ptr;
}

void *Free(void *ptr){
	if(ptr == NULL){
		fprintf(stderr, "Cannot free a null pointer");
		exit(255);
	}
	free(ptr);
	return 0;
}

int Access(const char *pathname, int mode){
	int val = access(pathname, mode);
	if(val < 0){
		fprintf(stderr, "Error has occured %s\n", strerror(errno));
	}
	return val;
}
