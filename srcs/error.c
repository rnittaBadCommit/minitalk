#include "minitalk.h"

void ft_error(int err)
{
	if (err == SIGACTION_ERROR)
		printf("SIGACTION_ERROR");
	if (err == SIGEMPTY_ERROR)
		printf("SIGEMPTY_ERROR");
	exit(-1);
}