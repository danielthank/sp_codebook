#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAXLINE 1000

void err_sys(char *str) {
    fprintf(stderr, "%s\n", str);
    exit(-1);
}

void pr_exit(int status) {
    if (WIFEXITED(status))
        printf("normal terminalt, exit status=%d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number=%d\n", WTERMSIG(status));
    else if (WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}

int main(void) {
    int n;
    int fd[2];
    pid_t pid;
    char line[MAXLINE];

    if (pipe(fd) < 0)
        err_sys("pipe error");
    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid > 0) {
        close(fd[0]);
        write(fd[1], "hello world\n", 12);
        printf("parent: %d %d\n", getpid(), getppid());
        int status;
        if (wait(&status) != pid)
            err_sys("wait_error");
        pr_exit(status);
    }
    else {
        close(fd[1]);
        n = read(fd[0], line, MAXLINE);
        write(STDOUT_FILENO, line, n);
        printf("child: %d %d\n", getpid(), getppid());
    }
}
