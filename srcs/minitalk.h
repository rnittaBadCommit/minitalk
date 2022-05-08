#ifndef MINITALK_H
# define MINITALK_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#define SIGACTION_ERROR 1
#define SIGEMPTY_ERROR 2
#define PAUSE_ERROR 3
#define EOB_ERROR 4

#define BAD_ARGNUM 1
#define BAD_PID 2

#define CODE0 SIGUSR1
#define CODE1 SIGUSR2
#define SIGACK SIGUSR1
#define SIGEOB SIGUSR2

#define INI_PID -1

void handler(int signal);
void handler2(int signal, siginfo_t *info, void *ucontext);
void ft_error(int err);
int ft_atoi(char *s);
void encoder(char c, char *buf);
char decoder(char *buf);

#endif