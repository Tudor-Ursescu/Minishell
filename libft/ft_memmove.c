/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:14:13 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/12 11:16:25 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	void	*dest_ptr;

	dest_ptr = dst;
	if ((!dst && !src) || dst == src)
		return (dst);
	if (dst >= src)
	{
		while (n--)
			((char *)dst)[n] = ((char *)src)[n];
	}
	else if (dst < src)
	{
		while (n--)
			*(char *)dst++ = *(char *)src++;
	}
	return (dest_ptr);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <strings.h>

// int main(void)
// {
// 	char buffer[10] = "67890";
// 	char dest[10] = "123450000";
// 	int n = 10;
// 	printf("Before ft_memmove: %s\n", dest);
// 	ft_memmove(dest,buffer,n);
// 	printf("After ft_memmove:");
// 	int i = 0;
// 	while (i < 10)
// 	{
// 		printf("%c", (unsigned char)dest[i]);
// 		i++;                    
// 	}
// 	printf("\n");

// 	   char buffer2[10] = "67890";
// 	   char dest2[10]	= "123450000";

// 	printf("Before memmove: %s\n", dest2);
// 	memmove(dest2,buffer2, n);
// 	printf("After memmove:   ");
// 	i = 0;
// 	while (i < 10)
// 	{
// 		printf("%c", (unsigned char)dest2[i]);
// 		i++;                      
// 	}
// 	printf("\n");
// 	return (0);
// }