# CSE109 - Systems Software - Spring 2023

## Homework 2 - Exploring GCC

**Due Date: 3/8/2023 EOD**

## Instructions 

**Read thoroughly before starting your project:**

1. Fork this repository into your CSE109 project namespace. [Instructions](https://docs.gitlab.com/ee/workflow/forking_workflow.html#creating-a-fork)
2. Clone your newly forked repository onto your development machine. [Instructions](https://docs.gitlab.com/ee/gitlab-basics/start-using-git.html#clone-a-repository) 
3. As you are writing code you should commit patches along the way. *i.e.* don't just submit all your code in one big commit when you're all done. Commit your progress as you work. **You must make at least one commit per question.**
4. When you've committed all of your work, there's nothing left to do to submit the assignment.

## Assignment

In this assignment we will explore the C GCC compilation pipeline. I've defined a simple C program in the project directory. Take a moment before starting to familiarize yourself with the files in the `src` and `include` directories. We are going to compile `main.c` into an executable `main`, and `lib1.c`/`lib2.c` into a library `libmylib.a`. The executable `main` will link to `libmylib.a`. You've done this several times already with the gcc command, but as we've learned in class, gcc is really a series of programs that are interconnected. In this assignment we will decompose the process into a number of different steps. Those steps are:

1. The C preprocessor - cpp
2. The C frontend - cc
3. The assembler - as
4. The linker - ld

As you go through this assignment you will generate a number of intermediate files. Usually I implore you not to commit compiler artifacts to your git repositories, but for this assignment the whole point is to generate and analyze these artifacts, so do commit them this time. They will have the extensions `.i`, `.s`, `.o`, and `.a`. In Part 1 will ask you to generate some files of the form `main.i.NNNt.*`. Save these to your repository as well. You should keep them all in the project root.

Here is a short reference of what the various file types mean:

- `.h` - C Header file
- `.c` - C Source
- `.i` - C preprocesor output
- `.s` - Assembly
- `.o` - Object Code
- `.a` - Object Archive

For this assignment, I ask you to make a number of observations about things we haven't covered in detail, and to form an inference from what you observe. Your objective for these questions is not to get the right answer (although it's fine if you do), but to form a well-reasoned response based on what we have studied. Getting the question wrong is fine as long as you do so thoughtfully. You will be graded on the clarity of your reasoning, and your ability to pull in knowledge from what we have studied in class.

### Part 1 - Exploring The C Preprocessor

The C preprocessor can be called directly by invoking the command `cpp` from the command line with a target input file. For example:

```bash
$ cpp main.c
```

Use the `cpp` command to preprocess `/src/bin/main.c`. You will have to use the `-I` flag in the usual way to tell the preprocessor where to find `mylib.h`. Save the result to a file in the project root directory called `main.i` (you can use the [`>` bash operator](https://www.linux.com/topic/desktop/understanding-angle-brackets-bash/) in the terminal to do this).

**Question 1:** How many bytes are in the source file?
	There are 134 bytes in the source file. This is known by using the ls -l command. 
**Question 2:** How many bytes are in `main.i`? What happened in `cpp` to cause this difference?
	There are 628 bytes in the main.i file. This is due to the fact that cpp linked the .h files which take up additional space in memory. 
**Question 3:** List all the differences you see between `main.c` and `main.i`.
	The main.c file simply has a header which includes mylib.h and a main that has the functions add() and sub().
	The main.i file has a longer header that shows the paths of the .c and .h files. Along with this it shows the 
	two functions sub() and add() with their paths under them. And under both fo those is the main function from 
	main.c.
### Part 2 - Exploring The C Frontend

We can call the C frontend directly by invoking the command `cc` from the command line, with the target input file being the output we got from `main.i`. When you invoke `cc`, it transforms the input program into a number of internal states. We can take a look at some of these states with a collection of flags named `-fdump-*`.

The `cc` command will automatically invoke the assembler, which we can short-circuit with the `-S` flag to see the assembly output.

(you can do Questions 4-7 in one command)

**Question 4:** Use the `cc` command to compile `main.i`, into `main.s`, the contents of which is `main.c` represented in human-readable assembly language.

**Question 5:** Use the `-fdump-tree-gimple` flag to output the Gimple intermediate representation.

**Question 6:** Use the `-fdump-tree-ssa` flag to output the SSA intermediate representation.

**Question 7:** Use the `-fdump-rtl-expand` flag to output the first RTL intermediate representation.

**Question 8:** Use the `-fdump-rtl-dfinish` flag to output the final RTL intermediate representation.

**Question 9:** On my machine, the files generated are:

- main.i.004t.gimple
- main.i.018t.ssa
- main.i.192t.expand
- main.i.270t.dfinish

What do you think the number in the file names might indicate?
	I think that number is the amount of bytes stored in each file because each file progressively became larger in the amount of
	text it included which leads me to believe the size in bytes also increased. 
**Question 10:** Consider `main.i` and the Gimple intermediate representation. What has changed between these two files?
	The main.i file showed where the methods were included from as well as the main function from main.c. The Gimple file was more simplistic
	because it merely had the main function but it had a value assigned to the starting value of x and showed that the value of x was altered
	throughout the program and then returned the value x.
**Question 11:** Consider the Gimple and SSA intermediate representations. What has changed between these two files?
	I notice that the code within the main function is becoming more lower-level because the variables are being assigned different values which shows
	the compiler that the variables are being altered throughout the program. In the Gimple file the variables kept the values 'x' and 'y' but it merely 
	showed that the program returned a specific value 'x'.
**Question 12:** Consider the SSA and RTL-expand intermediate representations. Why do you think the RTL representation is so much larger than the SSA representation?
	The RTL-expand is lower level language and includes comments about how the program is executed as well as the registers that are used. This contrasts with 
	the SSA representation because SSA allows for easy data flow analysis.
**Question 13:** Now take a look at the assembly code in the `main.s` file. It's okay that you don't know what this does, that's a topic for CSE202. But as you look at this file, remember the [Rosetta Stone](https://en.wikipedia.org/wiki/Rosetta_Stone). The people who studied this stone were able to use their knowledge of Greek to decode the meaning behind the hieroglyphics by making connections between the two languages. Try to use your knowledge of C to decode the meaning behind some of the assembly in `main.s`. There are wrong answers here (this question will be graded on your reasoning, not on accuracy).
	I can see in the main.c file the main function is declared and the there are lines of code proceeding it. I can see that there are explicit calls to 
	the registers with pushq which pushes the rbp register onto the stack, the base pointer. Then, through mvp it changes rbp to the stack pointer (rsp). 
	By using movl, it moves different values into different registers: ESI, EDI. It also uses call to call the functions sub and add. Bascially, 
	in main.s, the compiler is assigning values to different registers so the program may be executed. 

### Part 3 - Exploring the Assembler

The assembler can be called directly using the command `as`. The input to the assembler will be the assembly file from Part 2. The assembler will convert this assembly code into platform specific object code. Normally, `as` will call the linker `ld` after this step to generate an executable, but we can prevent that using the `-o` flag.

**Question 14:** Use `as` to turn `main.s` into `main.o`.

**Question 15:** A `.o` file is known as an object file because it contains platform-specific object code. We can take a look at this code using the `hexdump` command with the `-C` flag. Do this in your console and reproduce the results below:

**main.o:**
```
Upload file of hexdump of main.o, 'hexdump.txt'
```

We'll learn more about this later in the course. For now, just looking at it, what observations do you make? Are you able to draw any connections between the hexdump and the C and assembly code?
	I notice that there are three distinct columns. On the far left it appears to be hexadecimal, the middle two appear to be mostly zeroes with some number, and the far right is also zeros
	with some text as well. One of the similarities I see between the three files is that they all have .'' text within them.
### Part 4 - Building a Library

Now that we've gone through the process of turning a source file into an object file, we need to link to the library code on which it depends. To do that, we need to repeat the build process for `mylib1.c` and `mylib2.c`.

**Question 16:** Go through the process of turning `mylib1.c`/`mylib2.c` into `mylib1.o`/`mylib2.o` by following the steps in parts 1 through 3. You'll need to build the following files (you can skip the Gimple/SSA/RTL intermediate representations):

- `mylib1.i`
- `mylib1.s`
- `mylib1.o`
- `mylib2.i`
- `mylib2.s`
- `mylib2.o`

**Question 17:** Use `hexdump -C` to take a look at the object code within `mylib1.o` and `mylib2.o`. Paste the output of each below:

**mylib1.o:**
```
Upload file of hexdump of mylib1.o, 'lib1hexdump.txt'
```
**mylib2.o:**
```
Upload file of hexdump of mylib2.o, 'lib2hexdump.txt'
```

**Question 18:** Using `ar`, package `mylib1.o` and `mylib2.o` into a static library called `libmylib.a`.

**Question 19:** Now use `hexdump -C` to inspect the contents of `libmylib.a`. Paste the output in the space below.

**libmylib.a:**
```
Upload file of hexdump of libmylib.a, 'arhexdump.txt'
```

**Question 20:** Compare the hexdumps of `mylib1.o`, `mylib2.o`, and `libmylib.a`. What do you notice? How many bytes are in `mylib1.o`? How many are in `mylib2.o`? How many are in `libmylib.a`? Based on your comparison, what do you think the extra bytes are doing in `libmylib.a`?
	The hexdump of libmylib.a includes the hexdumps of mylib1.o and mylib2.o as well as some other data. mylib1.o has 1240 bytes, mylib2.o has 1232 bytes, libmylib.a has 2680 bytes. 
	The extra byte space may come from the other data within the file that links the two files together. 
### Part 5 - Building an Executable

We now have everything we need to build our executable. The `gcc` linker is a program called `ld`, and you can invoke the linker manually with the `ld` command in the terminal. But we won't use this command directly to build our executable, because doing so requires a number of arguments that are specific to the way your machine is configured. Therefore it's hard for me to provide generic instructions to do this as it might be different depending on your operating system and environment. Instead, we will invoke `gcc` which will call `ld` with the appropriate configuration options.

**Question 21:** Use `gcc` to combine `main.o` with `libmylib.a` to generate an executable named `main`.

**Question 22:** Use `hexdump -C` to take a look at hte object code within `main` and paste the output below:

```
Upload file of hexdump of main, 'main_hexdump.txt'
```

**Question 23:** Compare the output of `hexdump` for `main`, `main.o`, and `libmylib.a`. What do you notice? How many bytes are in `main.o`? How many are in `libmylib.a`? How many are in `main`? Based on your comparison, what do you think the extra bytes are doing in `main`?
	main has the longest hexdump because it is including data from all of the files linked to it, libmylib.a is just the two libs.o in one archive, and main.o has a similar length to 
	libmylib.a. main.o has 1448 bytes, libmylib.a has 2680 bytes, and main has 17736 bytes (the largest). The extra bytes in main is probably additional code that linkes all the files together. 
**Question 24:** Write a `Makefile` that automates the build process without using `gcc` (except to invoke the linker in the last step). Your `Makefile` should have the following directives:

- all - build the executable from `main.o` and `libmylib.a`
- main.o - build `main.o` from `main.c`
- libmylib.a - build `libmylib.a` from `mylib1.c` and `mylib2.c`
- clean - remove all `*.i`, `*.s`, `*.a`, `*.o`, `main`, and intermediate representation files.
