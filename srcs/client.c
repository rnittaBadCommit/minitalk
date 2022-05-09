/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnitta <rnitta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:35:48 by rnitta            #+#    #+#             */
/*   Updated: 2022/05/09 17:35:57 by rnitta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_flag_or_pid;

void	catch_sig(int signal, siginfo_t *info, void *ucontext)
{
	if (info->si_pid != g_flag_or_pid * -1)
		return ;
	if (ucontext)
		ucontext = NULL;
	if (signal == SIGACK || signal == SIGEOB)
		g_flag_or_pid = signal;
	usleep(1);
}

int	ft_atoi(char *s)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		ret = ret * 10 + s[i] - '0';
		if (ret < 0)
			return (-1);
		i++;
	}
	return (ret);
}

void	sig_init(int pid)
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) == -1)
		ft_error(SIGEMPTY_ERROR);
	sa.sa_sigaction = catch_sig;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGACK, &sa, NULL) == -1)
		ft_error(SIGACTION_ERROR);
	if (sigaction(SIGEOB, &sa, NULL) == -1)
		ft_error(SIGACTION_ERROR);
	g_flag_or_pid = pid * -1;
	kill(pid, SIGACK);
	while (g_flag_or_pid == pid * -1)
		pause();
}

void	send_8bit(int pid, char *buf)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		g_flag_or_pid = pid * -1;
		if (buf[i])
			kill(pid, CODE1);
		else
			kill(pid, CODE0);
		while (1)
		{
			if (pause() != -1)
				ft_error(PAUSE_ERROR);
			else if (i < 7 && g_flag_or_pid == SIGACK)
				break ;
			else if (g_flag_or_pid == SIGEOB)
				return ;
			else if (g_flag_or_pid != pid * -1)
				ft_error(EOB_ERROR2);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		i;
	char	buf[8];
	int		pid;

	if (argc != 3)
		return (BAD_ARGNUM);
	pid = ft_atoi(argv[1]);
	if (pid < 0 || pid > PID_MAX)
		return (BAD_PID);
	sig_init(pid);
	i = 0;
	while (argv[2][i])
	{
		encoder(argv[2][i], buf);
		send_8bit(pid, buf);
		i++;
	}
	i = 0;
	while (i < 8)
	{
		buf[i] = 0;
		i++;
	}
	send_8bit(pid, buf);
}
