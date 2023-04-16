#include "syscall.h"
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

void Free (void *ptr) {
    if (!ptr) { /* could also do “if (ptr == NULL) …” */
        fprintf(stderr, "Expected NULL pointer to free(void *ptr)\n");
        exit(255);
    } else {
        free(ptr);
    }
}

int Access(const char *pathname, int mode) {
    int rc = 0;
    if ((rc = access(pathname, mode)) != 0){
        fprintf(stderr, "%s not found or is not of mode %d\n", pathname, mode);
    }
    return rc;
}

FILE *Fopen(const char *filename, const char *mode){
    FILE *filePointer = fopen(filename, mode);
    if(filePointer == NULL){
        fprintf(stderr, "Error: failed to open file %s. Exiting.\n", strerror(errno));
        exit(2);
    }
    return filePointer;
}

void Fclose(FILE *filePointer){
    fclose(filePointer);
}