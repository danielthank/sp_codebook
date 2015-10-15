#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

void err_sys(char *str) {
    fprintf(stderr, "%s\n", str);
    exit(-1);
}

int main(void) {
    int i = 1;
    struct timeval timeout;
    fd_set master_set, working_set;
    char buf[1024];

    FD_ZERO(&master_set);
    FD_SET(0, &master_set);
    while (1) {
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        memcpy(&working_set, &master_set, sizeof(master_set));
        
        select(1, &working_set, NULL, NULL, &timeout);
        if (FD_ISSET(0, &working_set)) {
            fgets(buf, sizeof(buf), stdin);
            fputs(buf, stdout);
        }
        printf("iteration: %d\n", i++);
    }
    return 0;
}
