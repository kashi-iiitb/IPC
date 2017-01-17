#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LEN 1024

int main()
{
	int pipe_fd[2];
	pid_t child_pid;
	char buff_rd[MAX_LEN];
	char buff_wrt[MAX_LEN];
	int ret=0,max_len;
	int n=0;

	max_len = MAX_LEN;
	ret = pipe(pipe_fd);
	if((child_pid=fork())==0)
	{
		close(pipe_fd[1]);
		server(pipe_fd[0]);
/*		n = read(pipe_fd[0],buff_rd,max_len);
		buff_rd[n] = '\0';
		printf("string is %s\n",buff_rd);
*/		exit(0);
	}
	else if(child_pid>0)
	{
		close(pipe_fd[0]);
		client(pipe_fd[1]);
//		n = write(pipe_fd[1],buff_wrt,max_len);
	}
	else
	{
		printf("error in fork()\n");
		exit(1);
	}
	waitpid(child_pid,NULL,0);
}

int client(int wrt_fd)
{
	char buff_wrt[MAX_LEN];
	int len=0;
	strcpy(buff_wrt,"/tmp/test.file");
	int n=0;
	len = strlen(buff_wrt);
	n = write(wrt_fd,buff_wrt,len);
}
int server(int rd_fd)
{
	int n=0;
	char buff_rd[MAX_LEN];
	n = read(rd_fd,buff_rd,MAX_LEN);
	buff_rd[n] = '\0';
	printf("string is %s\n",buff_rd);
}


