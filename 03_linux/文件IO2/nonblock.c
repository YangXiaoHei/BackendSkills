#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define MSG_TRY "\ntry again\n"

int main() {
    char buf[10];
    
    int fd, len;
    
    fd = open("/dev/tty", O_RDONLY | O_NONBLOCK);
    
    if (fd < 0) {
        perror ("open /dev/tty ");
        exit (1);
    }
    
tryagain:
    len = read(fd, buf, sizeof(buf));
    if (len < 0) {
        if (errno == EAGAIN) {
            sleep(1);
            write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
            goto tryagain;
        }
        perror("read /dev/tty");
        exit(1);
    }
    write(STDOUT_FILENO, buf, len);
    close(fd);
    return 0;
}
