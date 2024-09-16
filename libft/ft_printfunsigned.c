/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfunsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:05:25 by ckonneck          #+#    #+#             */
/*   Updated: 2024/07/09 13:54:10 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	length(unsigned int nb)
{
	unsigned int	len;

	len = 0;
	if (nb == 0)
		return (1);
	else if (nb < 0)
		len++;
	while (nb != 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

int	ft_printfunsigned(unsigned int n)
{
	int		count;
	char	c;

	count = length(n);
	if (n > 9)
	{
		ft_printfnumber(n / 10);
		ft_printfnumber(n % 10);
	}
	if (n < 10)
	{
		c = n + 48;
		write(1, &c, 1);
	}
	return (count);
}
