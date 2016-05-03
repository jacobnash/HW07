#include "csapp.h"
#include <signal.h>// this is for the sig handler
#define BUF_SIZE 30

void handle_sigchld(int sig) {
    //don't fuck up the last errno, as that may not be what you want.
    int saved_errno = errno;
    //check the status, and if it is there.
    while (waitpid((pid_t)(-1), 0, WNOHANG) > 0) {}
    //hing and now you have a shit error.
    errno = saved_errno;
}
int main(int argc, char * argv[]) {
    struct sigaction sa;
    //set the handler to the function I created
    sa.sa_handler = &handle_sigchld;
    //to see if it dead or alive
    sigemptyset(&sa.sa_mask);
    //set the masks flags if any.
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    // this is where it kills the proccess.
    if (sigaction(SIGCHLD, &sa, 0) == -1) {
        perror(0);
        exit(1);
    }
    short sleep_parent;
    if (argc > 1) 
    {
        printf("Parent delayed 1 second\n");
        sleep_parent = 1;
    } 
    else 
    {
        printf("Parent not delayed\n");
        sleep_parent = 0;
    }

    //setup environment
    char * path = "file_to_read.txt";
    char buf[BUF_SIZE];
    short bytes_to_read = 5;
    short bytes_read;

    //create file descriptor
    int fd = Open(path,O_RDONLY,S_IREAD);

    //fork()
    int pid = Fork();

    //starting reading from file
    //include info as to which process is reading
    if (pid == 0) 
    {  //child process
        printf("Child PID = %d\n", pid);
        bytes_read = Read(fd, buf, bytes_to_read);
        printf("Child reads: %s\n", buf);
    } 
    else 
    {  //parent process
        printf("Parent PID = %d\n", pid);
        if (sleep_parent) 
        { //control whether parent will sleep before reading
            sleep(1);
        }
        bytes_read = Read(fd, buf, bytes_to_read);
        printf("Parent reads: %s\n", buf);
    }	
    Close(fd);
    return 0;
}
