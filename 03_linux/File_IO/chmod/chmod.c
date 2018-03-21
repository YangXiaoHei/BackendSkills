#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("至少需要 1 个命令行参数!\n");
        exit(1);
    }
    
    int rel = 0;
    
    rel = chmod(argv[1], S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP |
                 S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH);
//    rel += chmod(argv[1], S_IWUSR);
//    rel += chmod(argv[1], S_IXUSR);
//
//    rel += chmod(argv[1], S_IRGRP);
//    rel += chmod(argv[1], S_IWGRP);
//    rel += chmod(argv[1], S_IXGRP);
//
//    rel += chmod(argv[1], S_IROTH);
//    rel += chmod(argv[1], S_IWOTH);
//    rel += chmod(argv[1], S_IXOTH);
    
    if (rel != 0) {
        printf("修改失败!\n");
    }
    
    return 0;
}
