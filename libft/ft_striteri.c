/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:26:46 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/19 15:30:39 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// #include <stdio.h>

// #include <ctype.h>

// // Function to modify characters
// void	to_uppercase(unsigned int i, char *c)
// {
// 	if (*c >= 'a' && *c <= 'z')
// 		*c = *c - 32; // Convert lowercase to uppercase
// }

// int main()
// {
// 	char str[] = "hello world!";
// 	printf("Original string: %s\n", str);

// 	ft_striteri(str, to_uppercase);

// 	printf("Modified string: %s\n", str);
// 	return 0;
// }
