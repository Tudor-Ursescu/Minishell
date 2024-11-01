/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:33:00 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/19 09:55:48 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	length(int nb)
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

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	nb;
	unsigned int	len;

	len = length(n);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		nb = (unsigned int )(-n);
	}
	else
		nb = (unsigned int)n;
	if (n == 0)
		str[0] = '0';
	while (nb != 0)
	{
		str[--len] = (nb % 10) + 48;
		nb = nb / 10;
	}
	return (str);
}

// #include <stdio.h>
// int main() 
// {
// 	int number = 0;
// 	char* str = ft_itoa(number);

// 	if (str) {
// 		printf("The number as a string is: %s\n", str);
// 		free(str); // Don't forget to free the allocated memory
// 	} else {
// 		printf("Failed to allocate memory.\n");
// 	}
// }

//     return 0;
// }
	// while (n != 0)
	// {				for testing
	// 	printf(" before%d", n);
	// 	str[count -i - 1] = (n % 10) + '0';
	// 	printf(" after 1 %d", n);
	// 	n /= 10;
	// 	printf(" after 2 %d", n);
	// 	printf("string: %s",str );
	// 	i++;
	// }