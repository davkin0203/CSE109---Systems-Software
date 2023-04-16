/* 
 * Program: lab6.c
 * Name: Ima D. Veloper
 * UID: idv123
 */

/* preprocessor directives - NO NEED TO ADD MORE */
#include <stdio.h>    /* for fprintf function */
#include <stdint.h>   /* for uintX_t types */

/* prototypes - DO NOT MODIFY THESE */
void printChar(char);
void print1byte(uint8_t);
void print2bytes(uint16_t);
void print4bytes(uint32_t);
void print8bytes(uint64_t);

/* main - DO NOT MODIFY THIS FUNCTION */
int main() {
  fprintf(stdout, "\nCreate and load a union with various hex characters...\n");
  union {  /* a union simply allows us to access the same location in memory with different data types */
    unsigned char  c[8];
    unsigned short s[4];
    unsigned int   i[2];
    unsigned long  l[1];
  } u64;
  u64.c[0] = 0x0D; u64.c[1] = 0xF0; u64.c[2] = 0xAD; u64.c[3] = 0xBA; u64.c[4] = 0xEF; u64.c[5] = 0xBE; u64.c[6] = 0xAD; u64.c[7] = 0xDE; /* load values into memory */
  fprintf(stdout, "\tDone\n");

  fprintf(stdout, "\nNow print out the union's bytes as \"bits\"...\n");
  fprintf(stdout, "\tAddress %p: Characters 0-7 == ", &(u64.c));
  for (int i = 0; i < 8; i++) { print1byte(u64.c[i]); putc(' ', stdout); }
  fprintf(stdout, "\n\tAddress %p: Shorts 0-3     == ", &(u64.s));
  for (int i = 0; i < 4; i++) print2bytes(u64.s[i]);
  fprintf(stdout, "\n\tAddress %p: Ints 0-1       == ", &(u64.i));
  for (int i = 0; i < 2; i++) print4bytes(u64.i[i]);
  fprintf(stdout, "\n\tAddress %p: Long 0         == ", &(u64.l));
  for (int i = 0; i < 1; i++) print8bytes(u64.l[i]);
  fprintf(stdout, "\n");
  fprintf(stdout, "\nAnd now print out the union's bytes as hex characters...\n");
  fprintf(stdout, "\tAddress %p: Characters 0-7 == %02X %X %X %X %X %X %X %X\n", &(u64.c), u64.c[0], u64.c[1], u64.c[2], u64.c[3], u64.c[4], u64.c[5], u64.c[6], u64.c[7]);
  fprintf(stdout, "\tAddress %p: Shorts 0-3     == %X  %X  %X  %X\n", &(u64.c), u64.s[0], u64.s[1], u64.s[2], u64.s[3]);
  fprintf(stdout, "\tAddress %p: Ints 0-1       == %X    %X\n", &(u64.c), u64.i[0], u64.i[1]);
  fprintf(stdout, "\tAddress %p: Long 0         == %lX\n", &(u64.c), u64.l[0]);
  fprintf(stdout, "\n\n");

  return 0;
}

/* functions */

void printChar(char c) {      
  /* This function's purpose is to accept an 8-bit variable and print out its bits one-at-a-time.
   * To do this, you need to create 8 masks such that you can determine whether each of the 8 bits
   * is a binary 1 or a binary 0. If the bit is a 1, print the character '1', otherwise print the
   * character '0'. You are encouraged to use the ternary operator and the putc function to create
   * a loop body of just one line. The "(void)c;" line is just to allow a compile of this starter
   * code; you need to replace that with your loop. */
  for(int i = 7; i >= 0; i--){ // for loop going from 7 to 0
    putc((c & (1 << i)) ? '1' : '0', stdout); // put 1 if the char of c and the bit shift is both 1, if not print 0
  }
}                             /* Make sure you understand this code! Answer Q1 and Q2 below. */

/* The remainder of the functions call printChar to print out the bits in 1-, 2-, 4-, or 8-byte data types 
 *
 * Your job is to replace the function shells with code to do this! 
 */

void print1byte(uint8_t num) {    /* This one's already done for you! Aren't we nice? */
  printChar(num);
}

/* In this next function, you'll have to create a union named u16 with two members; use the union in main as a reference for learning.
 * 1) a member variable named "num" whose datatype is uint16_t (i.e., 16 bits)
 * 2) a member variable named "chars" which is an array of unsigned char's with sizeof(uint16_t) elements.
 * Next, set u16.num to equal the num passed in to this function.
 * Then, create a "for" loop that iterates over the bytes of num in reverse order (use ssize_t i as the loop variable and base its initial value off of sizeof(uint16_t)).
 * In the loop, 1) call printChar and pass it u16.chars[i], and 2) print a single space character (' ') so there's space between each printed byte
 * Answer Q3 and Q4.
 */
void print2bytes(uint16_t num) {  
  union {
    uint16_t num;
    unsigned char chars[sizeof(uint16_t)];
    } u16;

    u16.num = num;

    for(ssize_t i = sizeof(uint16_t) - 1; i >= 0; i--) {
        printChar(u16.chars[i]);
        putc(' ', stdout);
    }
}

/* Repeat what you did above for 2 bytes with uint32_t (4 bytes); answer Q5 */
void print4bytes(uint32_t num) {  
  union {
    uint32_t num;
    unsigned char chars[sizeof(uint32_t)];
    } u32;

    u32.num = num;

    for(ssize_t i = sizeof(uint32_t) - 1; i >= 0; i--) {
        printChar(u32.chars[i]);
        putc(' ', stdout);
    }
}

/* Repeat what you did above for 4 bytes with uint64_t (8 bytes) */
void print8bytes(uint64_t num) {
  union {
    uint64_t num;
    unsigned char chars[sizeof(uint64_t)];
    } u64;

    u64.num = num;

    for(ssize_t i = sizeof(uint64_t) - 1; i >= 0; i--) {
        printChar(u64.chars[i]);
        putc(' ', stdout);
    }
}

/* Answer any remaining questions below */

/*
 * Q1: Why in printChar do we want to create masks of 10000000, 01000000, 00100000, etc.? 
 * A1: Used to check each bit and then if they match (are 1) then you put that char, else put 0
 *
 * Q2: If we initialize a loop variable to 7, decrease it by 1 each iteration, and exit the loop 
 *     when the variable is less than 0, what will happen if we use an unsigned loop variable?
 * A2: It will never be less than 0 so it'll be an infinite loop, this is because an unsigned integer is never negative
 *
 * Q3: Why are we printing the bytes in reverse order?
 * A3: We want to print most significant bit to least singificant bit, not the other way around
 *
 * Q4: Do we have to use the sizeof operator to determine the number of bytes in a variable? If not, why might we want to use it? 
 * A4: We don't to but it makes the process easier without having to check for null terminator.
 *
 * Q5: Why do you think we used the family of uintX_t data types instead of char, short, int, and long?
 * A5: This is because we want to specify the amount of bits while those types have all different byte sizes, unlike the family of unitX_t.
 *
 * Q6: Do you now understand byte ordering?
 * A6: Yes, this is really cool. 
 *
 * Q7: Do you now appreciate how viewing bytes as hex characters instead of bits can be helpful?
 * A7: Yes, this was very interesting.
 *
 */
