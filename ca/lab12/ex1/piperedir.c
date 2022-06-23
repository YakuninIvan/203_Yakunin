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

	int pfd[2]; /* Pipe file descriptors */

	if (pipe(pfd) == -1) /* Create pipe */
		errExit("pipe");

	switch (fork())
	{
	case -1:
		errExit("fork");

	case 0:						 /* First child: exec 'ls' to write to pipe */
		if (close(pfd[0]) == -1) /* Read end is unused */
			errExit("close 1");

		/* Duplicate stdout on write end of pipe; close duplicated descriptor */

		if (pfd[1] != STDOUT_FILENO)
		{ /* Defensive check */
			if (dup2(pfd[1], STDOUT_FILENO) == -1)
				errExit("dup2 1");
			if (close(pfd[1]) == -1)
				errExit("close 2");
		}

		execlp(command1, command1, (char *)NULL); /* Writes to pipe */
		errExit("execlp ls");

	default: /* Parent falls through to create next child */
		break;
	}

	switch (fork())
	{
	case -1:
		errExit("fork");

	case 0:						 /* Second child: exec 'wc' to read from pipe */
		if (close(pfd[1]) == -1) /* Write end is unused */
			errExit("close 3");

		/* Duplicate stdin on read end of pipe; close duplicated descriptor */
		if (pfd[0] != STDIN_FILENO)
		{ /* Defensive check */
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
		errExit("execlp wc");

	default: /* Parent falls through */
		break;
	}

	/* Parent closes unused file descriptors for pipe, and waits for children */

	if (close(pfd[0]) == -1)
		errExit("close 5");
	if (close(pfd[1]) == -1)
		errExit("close 6");
	if (wait(NULL) == -1)
		errExit("wait 1");
	if (wait(NULL) == -1)
		errExit("wait 2");

	exit(EXIT_SUCCESS);
}
