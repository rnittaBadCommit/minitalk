#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#define SIGACTION_ERROR 1
#define SIGEMPTY_ERROR 2

int g_flag = 0;

void handler(int signal)
{
	printf("handler\n%d\n", signal);
	g_flag = 1;
}

void handler2(int signal, siginfo_t *info, void *ucontext)
{
	printf("handler 2\nSending PID: %d\n", info->si_pid);
	g_flag = 1;
}

void ft_error(int err)
{
	if (err == SIGACTION_ERROR)
		printf("SIGACTION_ERROR");
	if (err == SIGEMPTY_ERROR)
		printf("SIGEMPTY_ERROR");
	exit(-1);
}

int main(void)
{
	pid_t pid;
	struct sigaction sa;

	pid = getpid();
	if (sigemptyset(&sa.sa_mask) == -1)
		ft_error(SIGEMPTY_ERROR);
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		ft_error(SIGACTION_ERROR);
	while (!g_flag)
		;
	g_flag = 0;
	sa.sa_sigaction = handler2;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		ft_error(SIGACTION_ERROR);
	while (!g_flag)
		;
	printf("END!\n");
}
