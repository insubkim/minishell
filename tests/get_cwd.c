#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    struct stat buf;
    stat("a.out", &buf);
    printf("st_dev: %d", buf.st_uid);
}

/*
int stat(const char *path, struct stat *buf);
int fstat(int fd, struct stat *buf);
int lstat(const char *path, struct stat *buf);

Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

lstat():
_BSD_SOURCE || _XOPEN_SOURCE >= 500 || _XOPEN_SOURCE && _XOPEN_SOURCE_EXTENDED
|| Since glibc 2.10:  _POSIX_C_SOURCE >= 200112L
Description
These functions return information about a file. No permissions are required on the file itself, but-in the case of stat() and lstat() - execute (search) permission is required on all of the directories in path that lead to the file.

stat() stats the file pointed to by path and fills in buf.

lstat() is identical to stat(), except that if path is a symbolic link, then the link itself is stat-ed, not the file that it refers to.

fstat() is identical to stat(), except that the file to be stat-ed is specified by the file descriptor fd.

All of these system calls return a stat structure, which contains the following fields:

struct stat {
    dev_t     st_dev;     /* ID of device containing file 
    ino_t     st_ino;     /* inode number 
    mode_t    st_mode;    /* protection 
    nlink_t   st_nlink;   /* number of had links 
    uid_t     st_uid;     /* user ID of owner 
    gid_t     st_gid;     /* group ID of owner 
    dev_t     st_rdev;    /* device ID (if special file) /
    off_t     st_size;    /* total size, in bytes /
    blksize_t st_blksize; /* blocksize for file system I/O /
    blkcnt_t  st_blocks;  /* number of 512B blocks allocated /
    time_t    st_atime;   /* time of last access *
    time_t    st_mtime;   /* time of last modification *
    time_t    st_ctime;   /* time of last status change *
};



*/