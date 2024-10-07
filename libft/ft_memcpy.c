/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:04:10 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/19 13:41:38 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*dest_ptr;

	dest_ptr = dst;
	if ((!dst && !src) || dst == src)
		return (dst);
	while (n--)
		*(char *)dst++ = *(char *)src++;
	return (dest_ptr);
}
// line 23 can also be typed as;
// ((char *)dst)[i] = ((char *)src)[i];
// i++;
// #include <stdio.h>
// #include <stdlib.h>
// #include <strings.h>

// int main(void)
// {
// 	char src[10] = "hello";
// 	char dest[9] = "";
// 	int n = 5;
// 	printf("Before ft_memcpy: %s\n", dest);
// 	ft_memcpy(dest,src,n);
// 	printf("After ft_memcpy: %s", dest);
// 	printf("\n");

// }