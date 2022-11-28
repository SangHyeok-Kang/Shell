#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>
#include <signal.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <setjmp.h>
#include <sys/types.h>

#define BUFSIZE 256

sigjmp_buf jbuf;
pid_t pid;

char path[BUFSIZE];

int main()
{
	signal(SIGINT, handler_SIGINT);
	signal(SIGTSTP, handler_SIGQUIT);

	char buf[256];
	char * argv[50];
	int narg;
	pid_t pid;

	while (1)
    	{
		char *argv[50] = {'\0'};

		getcwd(path, BUFSIZE);
        	printf("%s$ ", path);
        	gets(buf);

        if(!strcmp(buf, "exit")) {
			printf("Bye Bye shell :(\n");
			exit(0);
	}

        else if(!strcmp(buf,"") || !strcmp(buf,"\t"))
            	continue;

        narg = getargs(buf, argv);
        handler(narg, argv);
    }
}
