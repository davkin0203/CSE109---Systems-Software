/*
 * File: syscalls.c
 * UserID: Ivanna B. Kewl
 */

#include <stdio.h>       /* for fprintf */
#include <stdlib.h>      /* for exit */
#include <errno.h>       /* for errno */
#include <string.h>      /* for strerror */
#include <unistd.h>      /* for pipe, fork, read, write, close */
#include <sys/wait.h>    /* for wait */
#include <sys/socket.h>  /* for socketpair */

pid_t Fork(){
    pid_t pid;

    if ((pid = fork()) < 0){
        fprintf(stderr, "Fork() error: %s\n", strerror(errno));
    }

    return pid;
}

int Socketpair(int domain, int type, int protocol, int socket_vector[2]){
    int check;

    if ((check = socketpair(domain, type, protocol, socket_vector)) < 0){
        fprintf(stderr, "Socketpair() error: %s\n", strerror(errno));
    }

    return check;
}

pid_t Wait(int *stat_lock){
    pid_t pid;

    if ((pid = wait(stat_lock)) < 0){
        fprintf(stderr, "Wait() error: %s\n", strerror(errno));
    }

    return pid;
}

ssize_t Write(int fildes, const void *buf, size_t nbyte){
    ssize_t bytes;

    if ((bytes = write(fildes, buf, nbyte)) < 0){
            fprintf(stderr, "Write() error: %s\n", strerror(errno));
    }

    return bytes;
}

ssize_t Read(int fildes, void *buf, size_t nbyte){
    ssize_t bytes;

    if ((bytes = read(fildes, buf, nbyte)) < 0){
        fprintf(stderr, "Read() error: %s\n", strerror(errno));
    }

    return bytes;
}

int Close(int fildes){
    int check;
    if ((check = close(fildes)) < 0){
        fprintf(stderr, "Close() error: %s\n", strerror(errno));
    }

    return check;
}
