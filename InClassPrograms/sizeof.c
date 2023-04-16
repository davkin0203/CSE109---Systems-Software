#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yomama(int *, int);

int main() {
	void *vptr = malloc(1024);
	fprintf(stdout, "sizeof(vptr) = %ld\n", sizeof(vptr));
	fprintf(stdout, "sizeof(*vptr) = %ld\n", sizeof(*vptr)); // same as vprt[0]

	char *cptr = (char *) malloc(1024);
	for(int i = 0; i < 1024; i++){
		cptr[i] = 'z';
	}
	cptr[1024] = 'a';
	fprintf(stdout, "sizeof(cptr) = %ld\n", sizeof(cptr));
        fprintf(stdout, "strlen(cptr) = %ld\n", strlen(cptr));

	int *iptr = (int *)malloc(256 * sizeof(int)); // int is 4 bytes
	fprintf(stdout, "sizeOf(iptr) = %ld\n", sizeof(iptr)); // pointer to anything is 8 bytes
	fprintf(stdout, "sizeOf(*iptr) = %ld\n", sizeof(*iptr)); 
	iptr[256] = -1;

	int dork = 391;
	int *intPtr = &dork;

	yomama(intPtr, 3); // yomama(&dork, 3); same thing!

	return 0;
}

void yomama(int *ptr, int x){
	*ptr = 2 * (*ptr) + x;
}
