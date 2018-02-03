/*
 * Fork
 *
 * oxben <oxben@free.fr>
 */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define COUNT     1000000
#define BUF_COUNT 1024

/**
 * @brief In loop, write a buffer to a file, read it from starts and check data is correct.
 *
 * @param count Number of times the file must be written and read
 * @param indent Indentation for informative messages
 *
 * @returns 0 on success
 * @returns -1 on failure
 */
int
write_read(int count, int indent)
{
    char filename[256];
    pid_t pid;
    int fd;
    pid_t wbuf[BUF_COUNT];
    pid_t rbuf[BUF_COUNT];
    size_t bufsize = BUF_COUNT * sizeof(pid_t);
    off_t offset;
    int i, n, rc;

    pid = getpid();

    snprintf(filename, sizeof(filename), "/tmp/forktest.%d", pid);

    printf("INFO: %*s[%d] Writing %d times to %s\n", indent*6, "", pid, count, filename);

    fd = open(filename, O_CREAT|O_RDWR|O_TRUNC, S_IRUSR|S_IWUSR);
    if (fd < 0) {
        printf("ERROR: [%d] creat() failed, fd=%d - %s\n", pid, fd, strerror(errno));
        return -1;
    }

    for (i = 0; i < BUF_COUNT; i++) {
        wbuf[i] = pid;
    }

    for (i = 0; i < count; i++) {
        n = write(fd, wbuf, bufsize);
        if (n != bufsize) {
            printf("ERROR: [%d] write() failed, n=%d\n", pid, n);
            rc = -1;
            goto out;
        }

        offset = lseek(fd, 0, SEEK_SET);
        if (offset < 0) {
            printf("ERROR: [%d] lseek() failed, offset=%ld - %s\n", pid, offset, strerror(errno));
            rc = -1;
            goto out;
        }

        n = read(fd, rbuf, bufsize);
        if (n != bufsize) {
            printf("ERROR: [%d] read() failed, n=%d - %s\n", pid, n, strerror(errno));
            rc = -1;
            goto out;
        }

        rc = memcmp(wbuf, rbuf, bufsize);
        if (rc != 0) {
            printf("ERROR: [%d] memcmp() failed, rc=%d\n", pid, rc);
            rc = -1;
            goto out;
        }
    }
    rc = 0;
    printf("INFO: %*s[%d] Success\n", indent*6, "",  pid);
out:
    close(fd);
    unlink(filename);
    return rc;

}

/**
 * @brief Fork child and write/read to file.
 *
 * @param childcount Number of children for the current process
 * @param indent Indentation for informative messages
 *
 * @returns 0 on success
 * @returns -1 on failure
 */
int
procfunc(int childcount, int indent)
{
    pid_t pid;
    int status;
    int rc;
    int es = -1;

    rc = write_read(1, indent);
    if (rc) {
        return rc;
    }

    if (childcount > 0) {
        pid = fork();
        if (pid > 0) {
            /* Parent */
            rc = write_read(COUNT, indent);

            waitpid(pid, &status, 0);
            if ( WIFEXITED(status) ) {
                es = WEXITSTATUS(status);
            }
            if (rc || es) {
                rc = -1;
            }
            printf("INFO: %*s[%d] Done - rc=%d\n", indent*6, "",  getpid(), rc);
        } else {
            rc = procfunc(childcount - 1, indent + 1);
        }
    } else {
        rc = write_read(COUNT, indent);
        printf("INFO: %*s[%d] Done - rc=%d\n", indent*6, "",  getpid(), rc);
    }
    return rc;
}

int
main(int argc, char **argv)
{
    int rc;
    int child_count;
    char *endptr;

    if (argc != 2) {
        printf("Usage: %s <child_count>\n", argv[0]);
        return 1;
    }

    child_count = strtol(argv[1], &endptr, 10);
    if (child_count < 0 || endptr == argv[1]) {
        printf("Usage: %s <child_count>\n", argv[0]);
        return 1;
    }

    rc = procfunc(atoi(argv[1]), 0);

    return (rc == 0 ? 0 : 1);
}
