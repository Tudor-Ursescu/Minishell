/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfnumber.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:07:43 by ckonneck          #+#    #+#             */
/*   Updated: 2024/07/09 13:54:20 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	length(int nb)
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

int	ft_printfnumber(int n)
{
	int		count;
	char	c;

	count = length(n);
	if (n == -2147483648)
	{
		write(1, "-2", 2);
		n = 147483648;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
	}
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
