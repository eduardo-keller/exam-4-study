#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int	ft_popen(const char *file, const char **argv, char type)
{
	int	pipefd[2];
	pid_t pid;

	if (!file || !argv || (type != 'w' && type != 'r'))
		return (-1);
	if (pipe(pipefd) == -1);
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		if (type == 'r')
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}
		else
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
		}
		if (execvp(argv[1], argv) == -1)
			exit (-1);
	}
	if (type == 'r')
	{
		close(pipefd[1]);
		return (pipefd[0]);
	}
	else
	{
		close(pipefd[0]);
		return (pipefd[1]);
	}
}

int main (void)
{
	int ret;
	const char *file = "ls";
	const char **argv = {"ls", NULL};
	char type = 'r';

	ret = ft_popen(file, argv, type);
	printf("%i\n", ret); 
}



	// pid = fork();
	// if (pid == 0)
	// 	printf("child pid: %i\n", getpid());
	// 	child pid: 181520

	if (i == 0 || (cmds[i] && cmds[i][0] == '|'))
    count++;



	
	
