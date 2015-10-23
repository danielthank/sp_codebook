#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len) {
    struct flock lock;
    lock.l_type = offset;
    lock.l_start = whence;
    lock.l_len = len;
    return (fcntl(fd, cmd, &lock));
}

int main() {
    int fd1 = open("tmp", O_RDWR);
    char buffer;
    while (1) {
        if (read(fd1, &buffer, 1) < 1) break;
        printf("%c", buffer);
    }
    struct flock lock;
    printf("%d\n", fd1);
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 2;
    lock.l_len = 5;
    printf("%d\n", fcntl(fd1, F_SETLK, &lock));
    getchar();
    printf("%d %d %d\n", lock.l_start, lock.l_len, lock.l_pid);
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 1;
    lock.l_len = 6;
    printf("%d\n", fcntl(fd1, F_GETLK, &lock));
    if (lock.l_type == F_UNLCK) printf("Failed\n");
    printf("%d %d %d\n", lock.l_start, lock.l_len, lock.l_pid);
    return 0;
}
