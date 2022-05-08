#include "minitalk.h"

struct s_flag {
	int g_flag;
	char g_value;
	int g_pid;
} t_flag;

void handler2(int signal, siginfo_t *info, void *ucontext)
{
	if (t_flag.g_pid == INI_PID)
		t_flag.g_pid = info->si_pid;
	if (t_flag.g_pid == info->si_pid)
	{
		t_flag.g_value = (signal == CODE1);
		t_flag.g_flag = 1;
		t_flag.g_pid = info->si_pid;
	}
	usleep(5);
}

int main(void)
{
	pid_t pid;
	struct sigaction sa;
	char buf[8];
	int i;
	int j;
	char output;

	t_flag.g_flag = 0;
	t_flag.g_pid = INI_PID;
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
	while (1)
	{
		i = 0;
		while (i < 8)
		{
			while (!t_flag.g_flag)
				;
			t_flag.g_flag = 0;
			buf[i] = t_flag.g_value;
			i++;
			if (i < 7)
				kill(t_flag.g_pid, SIGACK);
			else
				kill(t_flag.g_pid, SIGEOB);
		}
		output = decoder(buf);
		if (output == '\0')
		{
			t_flag.g_pid = INI_PID;
			write(1, "\n", 1);
		}
		else
			write(1, &output, 1);
	}
	printf("\nEND!\n");
}


/*
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
   */
