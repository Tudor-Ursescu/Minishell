/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:55:05 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/19 14:38:29 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	else
		return (NULL);
}

// #include <string.h>
// #include <stdio.h>
// int main(void)
// {
// 	char *s = "he8llo";
// 	int c = '8';
// 	printf("%s \n", ft_strchr(s, c));
// 	printf("%s \n", strchr(s, c));
// }