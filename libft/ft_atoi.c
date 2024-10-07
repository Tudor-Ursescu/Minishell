/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:35:54 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/18 15:02:58 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	count;
	int	res;
	int	sign;

	count = 0;
	res = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		count++;
		str++;
	}
	if (count > 1)
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (res * sign);
}

// #include <stdio.h>

// int main(void)
// {
// 	char str[] = "0";
// 	printf("my atoi %d \n", ft_atoi(str));
// 	printf("man atoi %d", atoi(str));

// }