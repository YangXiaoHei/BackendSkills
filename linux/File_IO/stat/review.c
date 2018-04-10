#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

typedef enum {
    yh_size_B,
    yh_size_KB,
    yh_size_MB,
    yh_size_GB
} yh_size_level;

yh_size_level szlevel(unsigned long fsz) {
    unsigned int sz_level = yh_size_B; // B
    if (fsz > 1024) {  // KB
        sz_level++;
        fsz /= 1024;
        if (fsz > 1024) {  // MB
            sz_level++;
            fsz /= 1024;
            if (fsz > 1024) { // GB
                sz_level++;
            }
        }
    }
    return sz_level;
}

void printsz(const char *pre, unsigned long fsz) {
    unsigned long sz_level = szlevel(fsz);
    switch (sz_level) {
        case yh_size_B:
            printf("%s %zd B\n",pre ? pre : '\0', fsz);
            break;
        case yh_size_KB:
            printf("%s  %zd KB\n",pre ? pre : '\0', fsz / 1024);
            break;
        case yh_size_MB:
            printf("%s %zd MB\n",pre ? pre : '\0', fsz / 1024 / 1024);
            break;
        case yh_size_GB:
            printf("%s %zd GB\n",pre ? pre : '\0', fsz / 1024 / 1024 / 1024);
            break;
        default: break;
    }
}

int main(int argc, char *argv[]) {
    
    struct stat st;
    
    if (stat(argv[1], &st) < 0) {
        perror(argv[1]);
        exit(1);
    }
    
    printf("\n");
    printsz("文件大小 : ", st.st_size);
    printsz("IO 块 : ", st.st_blksize);
    printf("blocks num : %zd\n", st.st_blocks);
    
    struct tm * lac, * lmdi, * lch;
    
    lac = localtime(&(st.st_atime));
    lmdi = localtime(&(st.st_mtime));
    lch = localtime(&(st.st_ctime));
    
    printf("最后访问时间 : %zd年%zd月%zd日 %02zd:%02d:%02d\n",
           lac->tm_year + 1900, lac->tm_mon + 1, lac->tm_mday,
           lac->tm_hour, lac->tm_min, lac->tm_sec);
    printf("最后更改时间 : %zd年%zd月%zd日 %02zd:%02d:%02d\n",
           lmdi->tm_year + 1900, lmdi->tm_mon + 1, lmdi->tm_mday,
           lmdi->tm_hour, lmdi->tm_min, lmdi->tm_sec);
    printf("最后修改时间 : %zd年%zd月%zd日 %02zd:%02d:%02d\n",
           lch->tm_year + 1900, lch->tm_mon + 1, lch->tm_mday,
           lch->tm_hour, lch->tm_min, lch->tm_sec);
    
    printf("\n");
    
    return 0;
}
