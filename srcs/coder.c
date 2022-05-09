/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnitta <rnitta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:36:36 by rnitta            #+#    #+#             */
/*   Updated: 2022/05/09 17:36:38 by rnitta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	encoder(char c, char *buf)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		buf[7 - i] = c & 1;
		c >>= 1;
		i++;
	}
}

char	decoder(char *buf)
{
	int		i;
	char	ret;

	i = 0;
	ret = 0;
	while (i < 8)
	{
		ret = (ret << 1) + (buf[i] == 1);
		i++;
	}
	return (ret);
}

/*
   int main()
   {
   char input[] = {0, 0, 0, 1, 0, 1, 1, 1};
   printf("%hd\n", decoder(input));
   encoder('b', input);
   printf("%c\n", decoder(input));
   }
   */
