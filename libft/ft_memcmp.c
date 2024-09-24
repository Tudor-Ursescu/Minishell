/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:21:53 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/18 17:30:07 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*ptr1;
	const char	*ptr2;

	ptr1 = (char *)s1;
	ptr2 = (char *)s2;
	while (n-- > 0)
	{
		if (*ptr1 != *ptr2)
			return (*(unsigned char *)ptr1 - *(unsigned char *)ptr2);
		ptr1++;
		ptr2++;
	}
	return (0);
}

// #include <stdio.h>

// int main() {
//     char array1[] = "hellpi";
//     char array2[] = "hellio";
//     int result1 = memcmp(array1, array2, 6);
//     printf("%d man memcmp \n", result1);

//     int result2 = ft_memcmp(array1, array2,6);
//     printf("%d my memcmp", result2);

//     return 0;
// }