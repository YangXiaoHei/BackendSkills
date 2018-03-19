#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

#define MAP_LEN 0X1000

void sys_err(char *str, int exitno) {
    perror(str);
    exit(exitno);
}

int main(int argc, char *argv[]) {
    
    char *mm;
    int fd, i = 0;
    if (argc < 2) {
        printf("至少需要一个命令行参数");
        exit(1);
    }
    
    fd = open(argv[1], O_RDWR | O_CREAT, 0777);
    if (fd < 0) {
        sys_err("open", 1);
    }
    /**
     *   If whence is SEEK_SET, the offset is set to offset bytes.
     
     If whence is SEEK_CUR, the offset is set to its current location plus offset bytes.
     
     If whence is SEEK_END, the offset is set to the size of the file plus offset bytes.
     
     If whence is SEEK_HOLE, the offset is set to the start of the next hole greater than or
     equal to the supplied offset.  The definition of a hole is provided below.
     
     If whence is SEEK_DATA, the offset is set to the start of the next non-hole file region
     greater than or equal to the supplied offset.
     */
    if (lseek(fd, MAP_LEN - 1, SEEK_SET) < 0)
        sys_err("lseek", 3);
    
    if (write(fd, "\0", 1) < 0)
        sys_err("write", 4);
    
    mm = mmap(NULL, MAP_LEN, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    if (mm == MAP_FAILED) {
        sys_err("mmap", 5);
    }
    
    close(fd);
    
    while (1) {
        sprintf(mm, "hello%d", i++);
        sleep(1);
    }
    
    munmap(mm, MAP_LEN);
    return 0;
}
