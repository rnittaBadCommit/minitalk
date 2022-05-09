/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnitta <rnitta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:36:20 by rnitta            #+#    #+#             */
/*   Updated: 2022/05/10 02:20:58 by rnitta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_value_or_pid;

void	print_pid(int pid)
{
	char	c;

	if (pid > 0)
	{
		print_pid(pid / 10);
		c = pid % 10 + '0';
		write(1, &c, 1);
	}
}

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
}

void	init(int *flag)
{
	pid_t				pid;
	struct sigaction	sa;

	*flag = NORMAL;
	g_value_or_pid = INI_PID;
	pid = getpid();
	print_pid(pid);
	if (sigemptyset(&sa.sa_mask) == -1)
		ft_error(SIGEMPTY_ERROR);
	sa.sa_sigaction = handler2;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		ft_error(SIGACTION_ERROR);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_error(SIGACTION_ERROR);
}

int	recieve_8bit(int pid, char *buf, int *flag)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		g_value_or_pid = pid * -1;
		if (*flag == NORMAL)
			kill(pid, SIGACK);
		else if (*flag == EOB)
		{
			*flag = NORMAL;
			kill(pid, SIGEOB);
		}
		while (g_value_or_pid == pid * -1)
			usleep(1);
		if (g_value_or_pid == FROM_INVALID_PID)
			ft_error(FROM_INVALID_PID);
		else if (g_value_or_pid != CODE0 && g_value_or_pid != CODE1)
			ft_error(INVALID_SIGNAL);
		buf[i] = (g_value_or_pid == CODE1);
		i++;
	}
	return (1);
}

int	main(void)
{
	pid_t	pid;
	char	buf[8];
	int		flag;

	init(&flag);
	while (1)
	{
		while (g_value_or_pid == INI_PID)
			if (pause() != -1)
				ft_error(PAUSE_ERROR);
		pid = g_value_or_pid;
		while (recieve_8bit(pid, buf, &flag))
		{
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
