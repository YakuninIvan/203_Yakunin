#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char *const in = argv[1];
	char *const out = argv[2];
	char *const command = argv[3];

	int pid = fork();
	if (pid == -1)
		return -1;
	else if (pid == 0)
	{
		int fdout = open(out, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
		close(STDOUT_FILENO);
		dup2(fdout, STDOUT_FILENO);
		int fdin = open(in, O_RDONLY);
		close(STDIN_FILENO);
		dup2(fdin, STDIN_FILENO);
		char **args = (char **)malloc((argc - 2) * sizeof(char *));
		int i = 3;
		while (i < argc)
		{
			args[i - 3] = argv[i];
			i++;
		}
		args[i - 3] = NULL;
		execvp(command, args);
	}
	else
	{
		int exitstatus;
		waitpid(pid, &exitstatus, 0);
		if (WIFEXITED(exitstatus))
			exitstatus = WEXITSTATUS(exitstatus);
		//printf("wexitstatus %d\n", exitstatus);
	}
	return 0;
}
