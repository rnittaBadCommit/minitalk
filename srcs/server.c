#include "minitalk.h"

volatile sig_atomic_t	g_value_or_pid;

void	handler2(int signal, siginfo_t *info, void *ucontext)
{
	if ((signal != CODE0 && signal != CODE1) || info->si_pid == 0)
		return ;
	if (ucontext)
		ucontext = NULL;
	if (g_value_or_pid == INI_PID)
		g_value_or_pid = info->si_pid;
	else if (g_value_or_pid * -1 == info->si_pid)
		g_value_or_pid = signal;
	else
		g_value_or_pid = FROM_INVALID_PID;
	usleep(1);
}

void	init(void)
{
	pid_t				pid;
	struct sigaction	sa;

	g_value_or_pid = INI_PID;
	pid = getpid();
	printf("%d\n", pid);
	if (sigemptyset(&sa.sa_mask) == -1)
		ft_error(SIGEMPTY_ERROR);
	sa.sa_sigaction = handler2;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		ft_error(SIGACTION_ERROR);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_error(SIGACTION_ERROR);
}

void	recieve_8bit(int pid, char *buf, int *flag)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		printf("server: %d\n", i);
		g_value_or_pid = pid * -1;
		if (*flag == NORMAL)
			kill(pid, SIGACK);
		else if (*flag == EOB)
		{
			*flag = NORMAL;
			kill(pid, SIGEOB);
		}
		while (g_value_or_pid == pid * -1)
			;
		if (g_value_or_pid == FROM_INVALID_PID)
			ft_error(FROM_INVALID_PID);
		buf[i] = (g_value_or_pid == CODE1);
		i++;
	}
}

int	main(void)
{
	pid_t	pid;
	char	buf[8];
	int		flag;

	init();
	while (1)
	{
		while (g_value_or_pid == INI_PID)
			pause();
		pid = g_value_or_pid;
		flag = NORMAL;
		while (1)
		{
			recieve_8bit(pid, buf, &flag);
			buf[0] = decoder(buf);
			if (buf[0] == '\0')
			{
				write(1, "\n", 1);
				g_value_or_pid = INI_PID;
				kill(pid, SIGEOB);
				break ;
			}
			write(1, buf, 1);
			flag = EOB;
		}
	}
}

// int main(void)
// {
// 	pid_t pid;
// 	struct sigaction sa;

// 	pid = getpid();
// 	if (sigemptyset(&sa.sa_mask) == -1)
// 		ft_error(SIGEMPTY_ERROR);
// 	sa.sa_handler = handler;
// 	sa.sa_flags = 0;
// 	if (sigaction(SIGINT, &sa, NULL) == -1)
// 		ft_error(SIGACTION_ERROR);
// 	while (!g_flag)
// 		;
// 	g_flag = 0;
// 	sa.sa_sigaction = handler2;
// 	sa.sa_flags = SA_SIGINFO;
// 	if (sigaction(SIGINT, &sa, NULL) == -1)
// 		ft_error(SIGACTION_ERROR);
// 	while (!g_flag)
// 		;
// 	printf("END!\n");
// }
