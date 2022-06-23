#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int error()
{
	perror(strerror(errno));
	return 1;
}

int errclose(int fd)
{
	perror(strerror(errno));
	close(fd);
	return 1;
}

int errclose2(int fd1, int fd2)
{
	perror(strerror(errno));
	close(fd1);
	close(fd2);
	return 1;
}

int main(int argc, char *argv[])
{
	if(argc<3)
	{
		printf("Usage: infile outfile command arg1 arg2 arg3 ...\n");
		return 1;
	}
	char *const in = argv[1];
	char *const out = argv[2];
	char *const command = argv[3];

	int pid = fork();
	if (pid == -1)
		return (error());
	else if (pid == 0)
	{
		int fdout = open(out, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
		if (fdout == -1)
			return (error());
		if (close(STDOUT_FILENO)==-1)
			return (error());
		if(dup2(fdout, STDOUT_FILENO)==-1)
			return errclose(fdout);
		int fdin = open(in, O_RDONLY);
		if (fdin == -1)
			return errclose(fdout);
		if(close(STDIN_FILENO)==-1)
			return errclose2(fdout, fdin);
		if(dup2(fdin, STDIN_FILENO)==-1)
			return errclose2(fdout, fdin);
		char **args = (char **)malloc((argc - 2) * sizeof(char *));
		if(args==NULL)
			return errclose2(fdout, fdin);
		int i = 3;
		while (i < argc)
		{
			args[i - 3] = argv[i];
			i++;
		}
		args[i - 3] = NULL;
		execvp(command, args);
		return errclose2(fdout, fdin);
	}
	else
	{
		int exitstatus;
		if(waitpid(pid, &exitstatus, 0)==-1)
			return error();
		if (WIFEXITED(exitstatus))
		{
			exitstatus = WEXITSTATUS(exitstatus);
			return (exitstatus);
		}
		return (1);
	}
	return 0;
}
