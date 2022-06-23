#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

void errExit(const char *err)
{
	perror(err);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	char *const command1 = argv[1];
	char *const command2 = argv[2];
	int pfd[2];

	if (pipe(pfd) == -1)
		errExit("pipe");

	pid_t fork1 = fork();
	switch (fork1)
	{
	case -1:
		errExit("fork");

	case 0:
		if (close(pfd[0]) == -1)
			errExit("close 1");

		if (pfd[1] != STDOUT_FILENO)
		{
			if (dup2(pfd[1], STDOUT_FILENO) == -1)
				errExit("dup2 1");
			if (close(pfd[1]) == -1)
				errExit("close 2");
		}

		execlp(command1, command1, (char *)NULL);
		errExit("execvp command1");

	default:
		break;
	}

	pid_t fork2 = fork();
	switch (fork2)
	{
	case -1:
		errExit("fork");

	case 0:
		if (close(pfd[1]) == -1)
			errExit("close 3");

		if (pfd[0] != STDIN_FILENO)
		{
			if (dup2(pfd[0], STDIN_FILENO) == -1)
				errExit("dup2 2");
			if (close(pfd[0]) == -1)
				errExit("close 4");
		}

		char **args = (char **)malloc((argc - 1) * sizeof(char *));
		int i = 2;
		while (i < argc)
		{
			args[i - 2] = argv[i];
			i++;
		}
		args[i - 2] = NULL;
		execvp(command2, args);
		errExit("execvp command2");

	default:
		break;
	}

	if (close(pfd[0]) == -1)
		errExit("close 5");
	if (close(pfd[1]) == -1)
		errExit("close 6");
	int exitst;
	int i = 1;
	while (wait(&exitst) != -1)
		printf("Exit status %d: %d\n", i++, exitst);

	exit(EXIT_SUCCESS);
}
