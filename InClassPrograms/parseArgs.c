# include <stdio.h>

int main(int argc, char *argv[]){ /* or char **argv */
    int i;
    printf("Program name: %s\n", *argv); /* or argv[0] */
    printf("Number of arguments: %d\n", argc);
    for(i = 1; i < argc; i++) printf("Arg %d: %s\n", i, *++argv); /* or argv[i] */
    return 0;
}
		     
