/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnitta <rnitta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:36:00 by rnitta            #+#    #+#             */
/*   Updated: 2022/05/09 17:36:02 by rnitta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_error(int err)
{
	printf("Error %d\n", err);
	if (err == SIGACTION_ERROR)
		printf("SIGACTION_ERROR");
	if (err == SIGEMPTY_ERROR)
		printf("SIGEMPTY_ERROR");
	exit(-1);
}
