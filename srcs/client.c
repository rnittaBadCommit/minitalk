#include "minitalk.h"

struct s_flag
{
	int pid;
	int g_ack_flag;
	int g_eob_flag;
} t_flag;

void catch_ack(int signal, siginfo_t *info, void *ucontext)
{
	if (signal || ucontext)
		;
	if (info->si_pid == t_flag.pid)
		t_flag.g_ack_flag = 1;
}

void catch_eob(int signal, siginfo_t *info, void *ucontext)
{
	if (signal || ucontext)
		;
	if (info->si_pid == t_flag.pid)
	{
		t_flag.g_eob_flag = 1;
		t_flag.g_ack_flag = 1;
	}
}

int ft_atoi(char *s)
{
	int i;
	int ret;

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

void sig_init(struct sigaction *sa)
{
	if (sigemptyset(&sa->sa_mask) == -1)
		ft_error(SIGEMPTY_ERROR);
	sa->sa_sigaction = catch_ack;
	sa->sa_flags = SA_SIGINFO;
	if (sigaction(SIGACK, sa, NULL) == -1)
		ft_error(SIGACTION_ERROR);
	sa->sa_sigaction = catch_eob;
	if (sigaction(SIGEOB, sa, NULL) == -1)
		ft_error(SIGACTION_ERROR);
}

void send_8bit(int pid, char *buf)
{
	int i;

	i = 0;
	t_flag.g_eob_flag = 0;
	while (i < 8)
	{
		t_flag.g_ack_flag = 0;
		if (buf[i])
			kill(pid, CODE1);
		else
			kill(pid, CODE0);
		while (1)
			if (pause() != -1)
				ft_error(PAUSE_ERROR);
			else if (t_flag.g_ack_flag)
				break;
		i++;
	}
	if (!t_flag.g_eob_flag)
		ft_error(EOB_ERROR);
}

int main(int argc, char **argv)
{
	int i;
	char buf[8];
	struct sigaction sa;

	if (argc != 3)
		return (BAD_ARGNUM);
	t_flag.pid = ft_atoi(argv[1]);
	if (t_flag.pid < 0)
		return (BAD_PID);
	sig_init(&sa);
	i = 0;
	while (argv[2][i])
	{
		encoder(argv[2][i], buf);
		send_8bit(t_flag.pid, buf);
		i++;
	}
	i = 0;
	while (i < 8)
	{
		buf[i] = 0;
		i++;
	}
	send_8bit(t_flag.pid, buf);
}
