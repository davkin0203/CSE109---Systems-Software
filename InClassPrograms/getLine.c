#include <stdio.h> 
#include <string.h>

// ssize_t getline(char **lineptr, size_t *n, FILE *stream);
// int sscanf(const char *str, const char *format, ...);
// ssize => signed

int main(){
	
	char *buffer = NULL; // hold the string read
	size_t length = 0; // length of the string read
	ssize_t numChars = 0; // return val from getLine

	fprintf(stdout, "\nEnter some input (Cntrl+D to exit): ");
	while((numChars = getline(&buffer, &length, stdin)) != -1){
		// if numChars == -1, there was an error OR user entered Cntrl-D (same as EOF)
		// if numChars == 1, user just hit Enter
		// if numChars > 1, user entered 1 or more characters followed by enter
		// if numChars == 0, dont know know this would happen
		
		fprintf(stderr,   "\n\tnumChars     = %zd\n", numChars);
		fprintf(stderr,     "\n\tlength     = %zu\n", length);
		fprintf(stderr, "\n\tbuffer len     = %zu\n", strlen(buffer));
		fprintf(stderr,     "\n\tbuffer     = \"%s\"\n", buffer);

		int numMatches; // hold number of matches
		char c; // hold char
		long l; // hold long
		int i; // hold int
		
		buffer[numChars - 1] = "\0";
		numMatches = sscanf(buffer, "%c %lu %d", &c, &l, &i);
		switch(numMatches){
			case 3:
				fprintf(stderr, "got 3 matches\n");
				break;
			case 2:
				fprintf(stderr, "got 2 matches\n");
				break;
			case 1:
				fprintf(stderr, "got 1 match\n");
				break;
			default:
				fprintf(stderr, "got no match or error\n");
				break;
		}

		fprintf(stdout, "\nEnter some input (Cntrl+D to exit): ");
	}
	return 0;
}
