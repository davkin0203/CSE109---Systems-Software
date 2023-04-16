
void *Malloc (size_t size) {
	void *ptr = NULL; // or = 0
	if((ptr = malloc(size)) == NULL){
		// error handling - print message and exit
		fprintf(stderr, "Could not allocate space for %ld bytes - %s", size, strerror(errno));
		exit(errno);
	}
	return ptr;
}
