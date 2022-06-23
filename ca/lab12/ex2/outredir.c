#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	char *const command = argv[1];
	char *const out = argv[2];

	switch (fork())
	{
	case -1:
	{
		return -1;
	}
	case 0:
	{
		int fd = open(out, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
		close(STDOUT_FILENO);
		dup2(fd, STDOUT_FILENO);
		execlp(command, command, NULL);
		break;
	}
	default:
	{
		wait(NULL);
		break;
	}
	}
	return 0;
}
