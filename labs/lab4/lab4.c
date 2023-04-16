/* 
 * Program: lab4.c
 * Name: Mark Erle
 * UID: merle
 */

/* preprocessor directives */
#include <stdio.h>
#include <string.h>

/* prototypes - DO NOT CHANGE EITHER OF THESE */
void printViaArrForm(char *[], const char *);  /* pass argv or envp, pass "argv" or "envp" */
void printViaPtrForm(char **, const char *);   /* pass argv or envp, pass "argv" or "envp" */

/* main - DO NOT CHANGE ANYTHING IN HERE */
int main(int argc, char **argv, char *envp[]) {  /* could use "char *argv[]" and/or "char **envp" */
  putc('\n', stdout);
  fprintf(stdout, "argc (at address %p) has value %d\n", &argc, argc);  /* print location and value of argc */
  fprintf(stdout, "argv (at address %p) has value %p\n", &argv, argv);  /* print location and value of argv */
  fprintf(stdout, "envp (at address %p) has value %p\n", &envp, envp);  /* print location and value of envp */
  putc('\n', stdout);
  printViaArrForm(argv, "argv");  /* print the command-line arguments */
  putc('\n', stdout);
  printViaArrForm(envp, "envp");  /* print the environment variables  */
  putc('\n', stdout);
  printViaPtrForm(argv, "argv");  /* print the command-line arguments */
  putc('\n', stdout);
  printViaPtrForm(envp, "envp");  /* print the environment variables  */
  putc('\n', stdout);
  return 0;
}

/* functions */
void printViaArrForm(char *dp[], const char *sp) {  /* all references to elements of dp must use square brackets "[ ]" */
	fprintf(stdout, "%s (at address %p) points to address %p\n", sp, &dp, dp);

	//unsigned int COUNT = 0;
	//while(sp[COUNT] != 0){
	//	COUNT++;
	//}
	//printf("COUNT IS: %d\n", COUNT);

	unsigned int i;
        for(i = 0; i < sizeof(dp) / 8; i++){
                fprintf(stdout, "\t%s[%d] (at address %p) points to address %p\n", sp, i, &dp[i], dp[i]);
        	fprintf(stdout, "where this string of %ld bytes is stored: '%s'\n", strlen(dp[i]), dp[i]); // can do strlen() because a char is 1 byte so the amt of chars is the amt of bytes
	}
	fprintf(stdout, "\t%s[%d] (at address %p) is (null)\n", sp, i, &dp[i]);
}

void printViaPtrForm(char **dp, const char *sp) {  /* all references to elements of dp must use pointer arithmetic */
	fprintf(stdout, "%s (at address %p) points to address %p\n", sp, &dp, dp);
  
        //unsigned int COUNT = 0;
        //while(sp[COUNT] != 0){
        //          COUNT++;
        //}
        //printf("COUNT IS: %d\n", COUNT);
  
        unsigned int i;
        for(i = 0; i < sizeof(dp) / 8; i++){
                fprintf(stdout, "\t%s[%d] (at address %p) points to address %p\n", sp, i, (dp + i), *(dp + i));
                fprintf(stdout, "where this string of %ld bytes is stored: '%s'\n", strlen(*(dp + i)), *(dp + i));
        }
        fprintf(stdout, "\t%s[%d] (at address %p) is (null)\n", sp, i, (dp + i));	
}

/* Q & A 
 *
 * Q1. What is envp (in terms of its data structure)?
 * A1. envp is an array of arrays, a 2D array
 * 
 * Q2. Why is the address where envp is stored 8 bytes away from where argv is stored?
 * A2. they're initiliazed sequentially in an array so they are one memory address away
 *     and it's a 64-bit processor so everything in memory is 64 bits, 8 bytes.
 * 
 * Q3. Why are the addresses of argv and envp different when printed from the function printViaArrForm then when printed from main?
 * A3. it's different because it needs to store the pointer address somewhere in memory which causes it to have 
 *     a different memory address.
 *
 * Q4. Why are the values of argv and envp the same whether they were printed from printViaArrForm or main?
 * A4. they are the same because the pointer address of the arguments stays the same because the pointers 
 *     are passed in and not just the variable of the values.
 *
 * Q5. Why are arrays considered pointers, or conversely, why can pointers be viewed as arrays?
 * A5. arrays are considered pointers because when an array is declared a user may use pointer arithmetic to 
 *     traverse the array through pointer addresses. Also, array pointers always point to the first element 
 *     in the array.
 *
 */
