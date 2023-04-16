#define PAGE 4096                                                        /* no changes */
#define KILO 1024                                                        /* no changes */
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

char *strerror(int errnum);
void *Malloc(int);

int main() {
  unsigned int i;                                                        /* no changes */
  char **memptr = Malloc(KILO * KILO * sizeof(char *));                  /* no changes */
  for (i = 0; i < KILO * KILO; i++) {                                    /* do not add add'l statements to loop body until step 9 */
    memptr[i] = Malloc(PAGE);                                            /* no changes */
    memptr[i][KILO] = 255;					         /* no changes */
    if(i < 10){
      fprintf(stdout, "Memory address of memptr[%d] is %p\n", i, &memptr[i]);
    }
    //free(memptr);
  }
  for(i = 0; i < KILO * KILO; i++){
    free(memptr[i]);
  }
  free(memptr);
}

void *Malloc(int numBytes) {                                             /* no changes */
  void *ptr = NULL;                                                      /* no changes */
  if ((ptr = malloc(numBytes)) == NULL) {                                /* no changes */
    fprintf(stderr, "Could not allocate space - %s", strerror(errno));   /* no changes */
    exit(99);                                                            /* no changes */
  }
  return ptr;
}

/*
 * Q0: What does this program do?
 * A0: This program continuously allocates memory for a double array pointer of size.
 *     Within the for-loop the characters of the array are allocated memory using
 *     Malloc and then each is assigned the value 255 within the 2D array. Memory is 
 *     then freed up using the free() function after the for-loop. 
 *
 * Q1: How many bytes are between the pointers to the allocated memory? (answer in decimal)
 * A1: The memory addresses between the pointers is 8 bytes which is 64 bits because a byte 
 *     is 8 bits. Converting 64 bits to decimal results in 4294967295. 
 *
 * Q2: Is this the amount you expected? Why or why not?
 * A2: Yes, each piece of memory on a 64-bit processor is stored in 8 bytes. 
 * 
 * Q3: What changes did you make to fix the warnings and errors?
 * A3: - Explicitly declared Malloc() and strerror()
 *     - Removed the parameters of main()
 *     - main() should have return type of int
 *     - Gave Malloc() a return statement because it's void
 *     - Included two libraries <stdio.h> and <errno.h> 
 *     - Used free() function to free up memory after using Malloc()
 */
