/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:22:05 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/19 10:00:53 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)ptr == (unsigned char)c)
			return ((unsigned char *)ptr);
		ptr++;
		i++;
	}
	return (NULL);
}

// #include <stdio.h>

// int main(void) {
//     char *s = "hello friend i have arrived";
//     int c = 'a';
//     size_t len = 18;
//     void *result_my_memchr = ft_memchr(s, c, len);
//     void *result_man_memchr = memchr(s, c, len);

//     //Print the characters at the returned addresses
//     if (result_my_memchr!= NULL) {
// printf("Character found by my memchr: %c\n",*((char *)result_my_memchr));
//     } else {
//         printf("Character not found by my memchr\n");
//     }

//     if (result_man_memchr!= NULL) {
//         printf("found by man memchr: %c\n", *((char *)result_man_memchr));
//     } else {
//         printf("Char not found by man memchr\n");
//     }

//     return 0;
// }