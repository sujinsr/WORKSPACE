#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define WORKING_DIR "/home/ubuntu/workspace/myworkspace/c"
#define LOCK_FILE "lockfile.lock"
#define LOG_FILE "logfile.log"

void make_daemon();
void logging(char *file, char *log);

void logging(char *file, char *log)
{
        FILE *fp;
        if ((fp = fopen(file, "a")) == NULL)
                return;
        fprintf(fp, "%s\n", log);
        fclose(fp);
}

void make_daemon()
{
        int pid, lockfd, i;
        char pidstr[16];

        pid = fork();
        if (pid < 0) {
                printf("fork error.\n");
                exit(1);
        }
        if (pid > 0)
                exit(0);

        setsid();

        for (i = getdtablesize(); i >= 0; i--)
                close(i);

        i = open("/dev/null", O_RDWR);
        dup(i);
        dup(i);

        umask(027);

        chdir(WORKING_DIR);

        lockfd = open(LOCK_FILE, O_RDWR|O_CREAT, 0640);
        if (lockfd < 0)
                exit(1);

        if (lockf(lockfd, F_TLOCK, 0) < 0)
                exit(1);

        sprintf(pidstr, "%d\n", getpid());
        write(lockfd, pidstr, strlen(pidstr));

}

int main(int argc, char *argv[])
{
        make_daemon();
        sleep(5);
        while(1)
        {
                /* Do server work */
                logging(LOG_FILE, "This is write from main server.\n");
        }

        return 0;
}
