#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("至少需要提供 1 个命令行参数\n");
        exit(1);
    }
    
    const char *value = getenv(argv[1]);
    if (value == NULL) {
        printf("错误的键！");
        exit(1);
    }
    
    printf("%s = %s\n", argv[1], value);
    
    return 0;
}
