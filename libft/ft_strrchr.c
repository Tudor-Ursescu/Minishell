/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 08:17:07 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/19 16:31:15 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if (s[i] == (char)c)
		return ((char *)s + i);
	while (i >= 0)
	{
		if (s[i] == (char) c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
// 	char *s = "there is so \0ma\0ny \0 \\0 in t\0his stri\0ng !\0\0\0\0";
// 	int c = '\0';
// 	printf("mine: %s\n", ft_strrchr(s, c));
// 	printf("man: %s", strrchr(s, c));
// 	return (0);
// }
