/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:37:01 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/19 17:26:21 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, char const *s2, size_t n)
{
	int				result;
	unsigned int	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
		{
			result = (unsigned char)s1[i] - (unsigned char)s2[i];
			return (result);
		}
		i++;
	}
	return (0);
}

// #include <string.h>
// #include <stdio.h>

// int main(void)
// {
// 	char *s1 = "5rr";
// 	char *s2 = "5r2";
// 	int n = 3;
// 	int result;
// 	printf("my function  %d \n", ft_strncmp(s1, s2, n));
// 	printf("man function %d", strncmp(s1, s2, n));
// }