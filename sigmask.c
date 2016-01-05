#include <stdio.h>
#include <signal.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void pr_mask(char *str) {
    fprintf(stderr, "%s: ", str);
    sigset_t check;
    sigprocmask(SIG_BLOCK, NULL, &check);
    if (sigismember(&check, SIGINT)) fprintf(stderr, "INT ");
    if (sigismember(&check, SIGUSR1)) fprintf(stderr, "USR1 ");
    if (sigismember(&check, SIGUSR2)) fprintf(stderr, "USR2 ");
    if (sigismember(&check, SIGALRM)) fprintf(stderr, "ALRM ");
    fprintf(stderr, "\n");
}

void sig_int(int signo) {
    pr_mask("in sig_int");
}

int main(void) {
    sigset_t newmask, oldmask, waitmask;

    signal(SIGINT, sig_int);
    signal(SIGUSR1, sig_int);
    signal(SIGUSR2, sig_int);
    signal(SIGALRM, sig_int);

    sigemptyset(&waitmask);
    sigemptyset(&newmask);
    sigaddset(&waitmask, SIGALRM);
    sigaddset(&waitmask, SIGUSR1);
    sigaddset(&newmask, SIGINT);

    sigprocmask(SIG_BLOCK, &newmask, &oldmask);
    pr_mask("before");
    sigsuspend(&waitmask);
    pr_mask("after");

}

