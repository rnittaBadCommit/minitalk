/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnitta <rnitta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:36:00 by rnitta            #+#    #+#             */
/*   Updated: 2022/05/10 02:54:49 by rnitta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_printf(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	write(2, s, len);
}

void	ft_error(int err)
{
	ft_printf("Error\n");
	if (err == SIGACTION_ERROR)
		ft_printf("SIGACTION_ERROR\n");
	else if (err == SIGEMPTY_ERROR)
		ft_printf("SIGEMPTY_ERROR\n");
	else if (err == PAUSE_ERROR)
		ft_printf("PAUSE_ERROR\n");
	else if (err == EOB_ERROR)
		ft_printf("BIT_LOST\n");
	else if (err == EOB_ERROR2)
		ft_printf("BIT_LOST\n");
	else if (err == INVALID_PID)
		ft_printf("INVALID_PID\n");
	exit(-1);
}
