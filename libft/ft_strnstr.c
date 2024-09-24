/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:24:41 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/19 16:24:20 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while ((i < len && big[i]))
	{
		j = 0;
		while (big[i + j] == little[j] && ((i + j) < len))
		{
			j++;
			if (little[j] == '\0')
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}

// #include <stdio.h>

// int main(void)
// {
// 	char *big = "aabaiuhferxe";
// 	char *little = "x";
// 	size_t len = 20;
// 	printf("%s", ft_strnstr(big, little, len));

// }