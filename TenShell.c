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


int getargs(char *cmd, char **argv){
	int narg = 0;
	
	while(*cmd){
		if(*cmd == '' || *cmd == '\t')
			*cmd++ = '\0';
		else{
			argv[narg++] = cmd++;
			while(*cmd != '\0' && *cmd != ''&&*cmd != '\t')
			cmd++;
		}
	}
	argv[narg] = NULL;
	return narg;
}

void handler_SIGINT(int signo, pid_t pid){
	if (kill(pidd, SIGTERM) != 0){
		printf("\n");
	}
}

void handler_SIGQUIT(int signo){
	printf("Ctrl + Z \n");
	printf("quit (core dumped)\n");
	
	exit(1);
}

void pwd(){
	char *buf = (char *)malloc(sizeof(char)*(BUFSIZE));
	
	if(getcwd(buf,BUFSIZE)==NULL){
		perror("(Error) Pwd");
		exit(EXIT_FAILURE);
	}
	else
		printf("%s \n",buf);
	
	free(buf);
}

void ls(int narg, char **argv){
	char temp[256];
	if(narg == 1){
		getcwd(temp, 256);
		printf("%s", temp);
		argv[1] = temp;
	}
	
	DIR *pdir;
	struct dirent *pde;
	int i = 0;
	if((pdir = opendir(argv[1])) < 0) {
		perror("(Error) Opendir: ");
	}
	printf("\n");
	while((pde = readdir(pdir)) != NULL) {
		printf("%-20s", pde->d_name);
		if(++i % 3 == 0)
			printf("\n");
		}
	printf("\n");
	closedir(pdir);
}

void cd(int narg, char **argv){
	if(narg == 1){
		chdir("Home");
	}
	else{
		if(chdir(argv[1]) == -1){
			printf("%s : no search file or directory \n", argv[1]);
		}
	}
}

void mkdir_(int narg, char **argv){
	umask(0);
	if(argv)
	
	if(narg < 2)
		fprintf(stderr, "Pathname does not exists \n");
	else{
		if(mkdir(argv[1], umask(0)) < 0) {
			perror("(Error) mkdir");
			exit(EXIT_FAILURE);
		}
	}
}


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








