#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void err_sys(char *str) {
    fprintf(stderr, "%s\n", str);
    exit(-1);
}

int main(void ) {
    pid_t pid;
    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0) {
        if ((pid = fork()) < 0)
            err_sys("fork error");
        else if (pid > 0)
            exit(0);
        //The grand child
        sleep(2);
        printf("second child, parent pid = %d\n", getppid());
        exit(0);
    }
    if (waitpid(pid, NULL, 0) != pid)
        err_sys("waitpid error");
    // The parent
    exit(0);
}
