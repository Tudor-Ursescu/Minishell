/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:32:37 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/19 12:18:23 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*str;

	str = (char *)s;
	while (n > 0)
	{
		*str = c;
		str++;
		n--;
	}
	return (s);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <strings.h>

// int main(void)
// {

//     char testString[] = "Hello, World!";
//     printf("Original String: %s\n", testString);
//     ft_memset(testString, '+', ft_strlen(testString));
//     printf("Modified String: %s\n", testString);
//     return 0;
// }