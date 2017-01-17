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

	strcpy(buff_wrt,"/tmp/test.file");
	max_len = MAX_LEN;
	ret = pipe(pipe_fd);
	if((child_pid=fork())==0)
	{
		close(pipe_fd[1]);
/*		n = read(pipe_fd[0],buff_rd,max_len);
		buff_rd[n] = '\0';
		printf("string is %s\n",buff_rd);
*/		exit(0);
	}
	else if(child_pid>0)
	{
		close(pipe_fd[0]);
//		n = write(pipe_fd[1],buff_wrt,max_len);
		//buff[n] = '\0';
		//printf("string is %s\n",buff);
	}
	else
	{
		printf("error in fork()\n");
		exit(1);
	}
	waitpid(child_pid,NULL,0);
}

int client(int in_fd,int out_fd
