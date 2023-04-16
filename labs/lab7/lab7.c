/*
 * File: lab7.c
 * UserID: Ivanna B. Kewl
 */

#include <stdio.h>       /* for fprintf */
#include <string.h>      /* for strcpy */
#include <sys/socket.h>  /* PF_FILE, SOCK_STREAM */
#include "syscalls.h"    /* for wrapped system calls */

#define msgLen 64

/* global variable (don't modify) */
static char const key[msgLen] = "91AcZ4l0nX39)e.xm2l'gu20wsx87s4K7&-*C1Y%>?11niO0=~bzN,}x[$vZ2/5q"; /* pretend both processes have this secret key */

/* prototype (don't modify) */
void crypto(char *);


/* main - only need to make 4 edits here; replace C++-style comments (i.e., "//") with function calls */
int main(void) {
  pid_t pid;
  int sockd[2]; /* the pair of socket descriptors */

  Socketpair(PF_FILE, SOCK_STREAM, 0, sockd);  /* creates an unnamed pair of connected sockets: sockd[0] and sockd[1] */

  if ((pid = Fork()) != 0) {  /* parent */
    Close(sockd[0]);  /* we only need one end of the socket in the parent, so we will choose to close sockd[0] */
    char message[msgLen];
    // add a call to Read() to read msgLen bytes from sockd[1] into message array
    Read(sockd[1], message, msgLen);
    fprintf(stdout, "parent: received encrypted message => '%s'\n", message);
    crypto(message);  /* decrypt message from parent */
    fprintf(stdout, "\nparent: decrypted message          => '%s'\n\n", message);
    strcpy(message, "That doesn't surprise me!"); 
    crypto(message);    /* encrypt reply to child */
    // add a call to Write() to write the msgLen bytes in message array to sockd[1]
    Write(sockd[1], message, msgLen);
    Wait(NULL); /* call Wait to wait for child to die (sounds sad, but it's not) */
    Close(sockd[1]);
  } else {                    /* child */
    Close(sockd[1]);  /* we only need one end of the socket in the child (the parent is using sockd[1]), so we will close sockd[1] */
    char message[msgLen] = "Professor Erle has a \"MOM\" tattoo and wears a wig.";
    crypto(message);  /* encrypt message before sending to child */
    // add a call to Write() to write msgLen bytes in message array to sockd[0]
    Write(sockd[0], message, msgLen);
    // add a call to Read() to read msgLen bytes from sockd[0] into message array 
    Read(sockd[0], message, msgLen);
    fprintf(stdout, "child:  received encrypted reply   => '%s'\n", message);
    crypto(message);  /* decrypt reply from parent */
    fprintf(stdout, "\nchild:  decrypted reply            => '%s'\n\n", message);
    Close(sockd[0]);
  }

  return 0;
}

/* add functionality to crypto function here */
void crypto(char *buffer) {
    for (size_t i = 0; i < msgLen; i++) {
        buffer[i] ^= key[i % msgLen];
    }
}


/*
 * Q0: What are two attributes of socketpair()? This is called a "gimme", when someone gives you the answer.
 * A0: 1) a socketpair is bidirectional
 *     2) socketpairs can be datagram-oriented (some communication channels are only stream-oriented)
 *
 * Q1: Creating sockets with socketpair() is SO much easier than the whole socket()/bind()/listen()/connect()/accept() process. 
 *     Why don't we always just use socketpair() for all communications? Hint: read 'man 3p socketpair'... which refers you to 'man 2 socketpair'.
 * A1: The reason we dont use socketpair for all communications is because that function has limits compared to the actual walkthrough process. Limits that are on the manpage include only: sockets only may have desired properties for communication, limites to communicationg with various applications and clients, and invalid addresses/families to communicate with.
 *
 * Q2: What is the purpose of the wait system call? Hint: read 'man 3p wait'... which refers you to 'man 2 wait'.
 * A2: The purpose of the wait system call is to wait for changes in the communication process. When their is communication, sometimes it is necessary to delay in order to get/comfirm information is properly sent.
 *     
 * Q3: Wait a minute, why are there man pages for these system calls in chapter 3p and chapter 2? In fact, check out 'man -a socket'... all the chapters
 *     with pages on "socket" will be displayed one after the other. (Just hit 'q' to move on to the next man page.) When do we use which chapter? Hint:
 *     'man man' may help with some of this answer; but you'll probably want to access the ol' Internet.
 * A3: Different chapters are made for more specific cases when calling a function. For examply, the 2 is a more general overview of the function while 3p is the posix implementation and covers more depth in the UNIX environment.
 *
 * Q4: Why is the encrypted message received by the parent so short? And why is the encrypted message received by the child split over two lines?
 * A4: The reason that the encrypted parent message is so short is because it is the initial encrypted message that has yet to be communicated with the child. The child communication and encryption process is a bit different in that it is called write initially, which might have an effect on the encryption.
 *
 * Q5: In the parent (line 33), why didn't we simply assign "That doesn't surprise me!" to the message array variable? I.e., why not do the following?    
 *     message = "That doesn't surprise me!";                                                                                                             
 * A5: Since we use strcpy, we want to edit the pointer to the destination of the message. That way, we can actually do a successful encryption to the reference.
 *
 * Q6: Why is it that we can use the same crypto() function to both encrypt and decrypt?
 * A6: Since the crypto function allows a shift, it can also work interchangably with encryption and decryption. The process works kind of mathemetically so it kind of happens in a reverse operation.
 */
