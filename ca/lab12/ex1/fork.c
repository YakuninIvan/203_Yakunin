#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

void child1()
{
	int pid = fork();
	if(pid==-1)
		return ;
	else if(pid==0)//child
		printf("Hello from GrandChild\n");
	else //parent
	{
		printf("Hello from Child\n");
		wait(&pid);
	}
}

int main()
{
	int pid = fork();
	if(pid==-1)
		return -1;
	else if(pid==0)//child
		child1();
	else//parent
	{
		printf("Hello from Parent\n");
		wait(NULL);
	}
	return 0;
}
