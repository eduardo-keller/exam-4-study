#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int	ft_popen(const char *file, const char **argv, char type)
{
	int	pipefd[2];

	if (!file || !argv || (type != 'w' && type != 'r'))
		return (-1);

	
	return (0);
}

int main (void)
{
	int ret;
	const char *file = "ls";
	const char **argv = {"ls", NULL};
	char type = 'b';

	ret = ft_popen(file, argv, type);
	printf("%i\n", ret); 
}