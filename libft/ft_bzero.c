/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 08:44:50 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/17 13:43:44 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*ptr;

	ptr = (char *)s;
	while (n > 0)
	{
		*ptr = 0;
		ptr++;
		n--;
	}
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <strings.h>

// int main(void)
// {
//     char buffer[10] = "Hello";

// 	int n = 4;
//     printf("Before ft_bzero: %s\n", buffer);
//     ft_bzero(buffer, n);
//     printf("After ft_bzero:");
//     int i = 0;
//     while (i < 10)
//     {
//         printf("%02x", (unsigned char)buffer[i]);
// pirnt in hexadeciaml format to show that all
//         i++;                       //bytes have been set to 0
//     }
//     printf("\n");

// 	   char buffer2[10] = "Hello";

// 	n = 4;
//     printf("Before ft_bzero: %s\n", buffer2);
//     bzero(buffer2, n);
//     printf("After bzero:   ");
//     i = 0;
//     while (i < 10)
//     {
//         printf("%02x", (unsigned char)buffer2[i]);
// pirnt in hexadeciaml format to show that all
//         i++;                       //bytes have been set to 0
//     }
//     printf("\n");
//     return (0);
// }