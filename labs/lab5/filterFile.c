#include <stdio.h>                      /* include for fprintf and getline*/
#include <stdlib.h>                      /* include for exit and free */
#include <string.h>                      /* include for strlen */
#include "syscalls.h"                      /* include for wrapped system calls */

int main(int argc, char *argv[]) {
  /* Add a check to make sure at least two arguments were passed to the program.
   *   If not, print "Usage" message to stderr and exit with return code of 99
   */
  if(argc <= 2){
    fprintf(stderr, "Usage: %s", argv[0]);
    exit(99);
  }

  /* Open the source file in read mode using Fopen */
  FILE *srcfile = Fopen(argv[1], "r");

  /* Open a file in write mode using Fopen (make sure the file is overwritten if it already exists) */
  FILE *dstfile = Fopen(argv[2], "w");

  /* Read a line at a time from the source file.
   *   If the line contains a comma-separated listing of a signed size_t, an unsigned size_t, 
   *   a short, and a string of at most 16 characters:
   *     write the contents of the line to the destination file in reverse order 
   *     (i.e., string first and signed size_t last), separated by tabs instead of commas
   */
  char *buffer = NULL; // buffer is where the dynamic memory is temporarily stored
  size_t length = 0; // unsigned integer for how many characters input
  ssize_t read; // signed value for 
  int fltrdLines = 0;

  while ((read = getline(&buffer, &length, srcfile)) != -1) { // -1 means that there are no more lines to read
    ssize_t ssize; // ssize_t
    size_t ussize; // size_t 
    short shrt; // short 
    char str[17]; // string which includes the null terminator so array size 17 not 16
    int count = sscanf(buffer, "%zd,%zu,%hd,%s", &ssize, &ussize, &shrt, str); // if line includes size_t, ssize_t, short, and string, returns value of 4
    if (count == 4) { // if it has read the correct values, then it will write them to the dstfile, otherwise, it iterates the amount of filtered lines
        fprintf(dstfile, "%s\t%hd\t%zu\t%zd\n", str, shrt, ussize, ssize);
    } else {
        fltrdLines++; // iterate filtered lines if the line doesn't contain conditions
    }
  }

  /* Print to stdout the number of lines you filtered out */
  printf("# filtered lines: %d\n", fltrdLines);

  /* Close your files using Fclose */
  Fclose(srcfile);
  Fclose(dstfile);

  /* Free any allocated memory (verify with "valgrind --leak-checks=yes readLine <source file> <destination") */
  free(buffer); // freeing the buffer

  return 0;
}

/* Q0: Why did the size_t print out 18446744073709551615 in passingTest2?
 * A0: this happened because the scanner was expecting an unsigned integer but when a -1 was passed it this caused the scanner to 
       not fully know to the rewrite it because positive and negative numbers are stored differently so this resulted in a very 
       positive number being written to the dstFile.txt
 *
 * Q1: What did you learn from interestingTest1?
 * A1: interestingTest1 showed me that 99 is of type, unsigned, signed, and short which caused no issues when rewriting them
       to the new dstFile.txt
 *
 * Q2: What did you learn from interestingTest2?
 * A2: interestingTest2 showed me that spaces are not read in as characters by the scanner
 *
 * Q3: Why do you think, in reallyVeryInterestingTest3, did reallyVeryInterestingTest3 
 *     print out in its entirety instead of just the 17 characters in the buffer?
 * A3: It printed the string in its entirety because the sscanf function did not have a specifier of how many chars to read in.
 *
 * Q4: Why are the second and third fields in the output of reallyVeryInterestingTest3
 *     not 99 and 99, respectively?
 * A4: That happens because the buffer size was altered because the char array went over 17 characters which created an error
       for the following int values and the int values were instead taking in char characters. When the values were printed
       to the new file this caused for very high integer values to be printed. 
 * Q5: Why are you getting the last line printed out twice due to an empty line 8 in srcFile.txt?
 *     If you are still getting this duplication, take steps to correct this.  If you are not 
 *     getting this duplication, what did you do to prevent/correct this?
 * A5: I prevented this by only having a new line written when the valid input was input into the program
 *
 * Q6: Did you learn from the redirect of the stderr (using "2>| stderr.txt") that valgrind writes
 *     all its output to stderr?
 * A6: stderr.txt allows to view the memory leaks within the program. However, in this program there was no memory leak so it 
       did not provide too much insight into the program aside from the 18,504 bytes allocated and the 6 allocas and 6 frees.
 *
 */
