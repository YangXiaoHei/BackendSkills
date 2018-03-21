
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <time.h>

//struct stat {
//    /* when _DARWIN_FEATURE_64_BIT_INODE is NOT defined */
//    dev_t    st_dev;    /* device inode resides on */
//    ino_t    st_ino;    /* inode's number */
//    mode_t   st_mode;   /* inode protection mode */
//    nlink_t  st_nlink;  /* number of hard links to the file */
//    uid_t    st_uid;    /* user-id of owner */
//    gid_t    st_gid;    /* group-id of owner */
//    dev_t    st_rdev;   /* device type, for special file inode */
//    struct timespec st_atimespec;  /* time of last access */
//    struct timespec st_mtimespec;  /* time of last data modification */
//    struct timespec st_ctimespec;  /* time of last file status change */
//    off_t    st_size;   /* file size, in bytes */
//    quad_t   st_blocks; /* blocks allocated for file */
//    u_long   st_blksize;/* optimal file sys I/O ops blocksize */
//    u_long   st_flags;  /* user defined flags for file */
//    u_long   st_gen;    /* file generation number */
//};

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("请输入文件路径\n");
        exit(1);
    }
    
    struct stat st;
    stat(argv[1], &st);
    struct stat *ptr = &st;
    printf("\n");
    printf("主设备号 :\t%zd\n",major(ptr->st_dev));//主设备号
    
    printf("从设备号 :\t%zd\n",minor(ptr->st_dev));//从设备号
    
    printf("inode :\t\t%zd\n",ptr->st_ino);//文件节点号
    
    printf("访问模式 :\t%zd\n",ptr->st_mode);//文件的访问模式
    
    printf("硬链接数 :\t%zd\n",ptr->st_nlink);//文件的硬链接数目
    
    printf("文件拥有者 ID :\t%zd\n",ptr->st_uid);//文件拥有者的ID
    
    printf("文件组 ID :\t%zd\n",ptr->st_gid);//文件的组ID
    
    printf("文件大小 B : \t%zd B\n",ptr->st_size);//文件的大小
    printf("文件大小 KB : \t%zd KB\n",ptr->st_size / 1024);//文件的大小
    printf("文件大小 MB : \t%zd MB\n",ptr->st_size / 1024 / 1024);//文件的大小
    printf("IO块 :\t%zd KB\n",ptr->st_blksize / 1024);//文件占用的块数量
    
    printf("为文件分配块数量 (512B):\t%zd\n",ptr->st_blocks);//文件分配块数量
    
    struct tm * accesstime, * lmodifytime, * lchangetime;//访问时间，修改时间，最后一个改变时间（属性）
    
    accesstime = localtime(&(ptr->st_atime));
    
    lmodifytime = localtime(&(ptr->st_mtime));
    
    lchangetime = localtime(&(ptr->st_ctime));
    
    printf("最后访问时间 :\t%zd::%zd::%zd\n", accesstime->tm_hour, accesstime->tm_min, accesstime->tm_sec);
    
    printf("最后更改时间 :\t%zd::%zd::%zd\n", lmodifytime->tm_hour, lmodifytime->tm_min, lmodifytime->tm_sec);
    
    printf("最后改动时间 :\t%zd::%zd::%zd\n", lchangetime->tm_hour, lchangetime->tm_min, lchangetime->tm_sec);
    printf("\n");
    
}
