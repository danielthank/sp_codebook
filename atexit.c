#include <stdio.h>
#include <stdlib.h>

void err_sys(char *str) {
    fprintf(stderr, "%s\n", str);
    exit(-1);
}

/*
 * Static functions are function that are only visible to otherfunctions in the
 * same file (more precisely the same translation unit).
 */

static void my_exit1(void) {
    printf("First exit\n");
}

static void my_exit2(void) {
    printf("Second exit\n");
}

int main(void) {
    if (atexit(my_exit2) != 0)
        err_sys("can't register mu_exit2");
    if (atexit(my_exit1) != 0)
        err_sys("can't register mu_exit1");
    if (atexit(my_exit1) != 0)
        err_sys("can't register mu_exit1");
    printf("main done\n");
}

