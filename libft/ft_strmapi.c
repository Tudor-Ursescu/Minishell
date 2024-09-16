/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:45:29 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/19 17:26:16 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*newstring;

	i = 0;
	newstring = malloc(ft_strlen((char *)s) + 1 * sizeof(char));
	if (!newstring)
		return (NULL);
	while (s[i])
	{
		newstring[i] = f(i, s[i]);
		i++;
	}
	newstring[i] = '\0';
	return (newstring);
}

// #include <stdio.h>

// // Function to modify characters
// char	to_uppercase(unsigned int i, char c)
// {
// 	    if (c >= 'a' && c <= 'z')
//         return c - 'a' + 'A';
//     else
//         return c;
// }

// int main()
// {
// 	char *str = "hello world!";
// 	printf("Original string: %s\n", str);
// 	char *result = ft_strmapi(str, to_uppercase);

// 	printf("Modified string: %s\n", result);
// 	return 0;
// }
