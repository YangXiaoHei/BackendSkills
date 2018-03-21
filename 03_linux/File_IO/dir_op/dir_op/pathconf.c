//
//  pathconf.c
//  dir_op
//
//  Created by YangHan on 2018/3/11.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 *   _PC_LINK_MAX
 
     The maximum file link count.
 
     _PC_MAX_CANON
 
     The maximum number of bytes in terminal canonical input line.
 
     _PC_MAX_INPUT
 
     The minimum maximum number of bytes for which space is available
     in a terminal input queue.
 
     _PC_NAME_MAX
 
     The maximum number of bytes in a file name.
 
     _PC_PATH_MAX
     The maximum number of bytes in a pathname.
 
     _PC_PIPE_BUF
 
     The maximum number of bytes which will be written atomically to a
     pipe.
 
     _PC_CHOWN_RESTRICTED
 
     Return 1 if appropriate privileges are required for the chown(2)
     system call, otherwise 0.
 
     _PC_NO_TRUNC
 
     Return 1 if file names longer than KERN_NAME_MAX are truncated.
 
     _PC_VDISABLE
 
     Returns the terminal character disabling value.
 
     _PC_XATTR_SIZE_BITS
 
     Returns the number of bits used to store maximum extended
     attribute size in bytes.  For example, if the maximum attribute
     size supported by a file system is 128K, the value returned will
     be 18.  However a value 18 can mean that the maximum attribute
     size can be anywhere from (256KB - 1) to 128KB.  As a special
     case, the resource fork can have much larger size, and some file
     system specific extended attributes can have smaller and preset
     size; for example, Finder Info is always 32 bytes.
 
     _PC_MIN_HOLE_SIZE
 
     If a file system supports the reporting of holes (see lseek(2)),
     pathconf() and fpathconf() return a positive number that repre-
     sents the minimum hole size returned in bytes.  The offsets of
     holes returned will be aligned to this same value.  A special
     value of 1 is returned if the file system does not specify the
     minimum hole size but still reports holes.
 */

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("至少需要 1 个命令行参数\n");
        exit(1);
    }
    
    int len;
    if ((len = pathconf(argv[1], _PC_NAME_MAX)) < 0) {
        perror("pathconf fail ");
        exit(1);
    }
    printf("最大文件名字符数 : %zd\n", len);
    
    return 0;
}




