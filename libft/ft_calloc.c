/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:31:36 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/18 16:16:10 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;

	ptr = NULL;
	if (nmemb >= 0)
	{
		ptr = (char *) malloc(nmemb * size);
		if (!ptr)
			return (NULL);
		ft_bzero(ptr, nmemb * size);
	}
	return (ptr);
}

// #include <stdio.h>
// int main(void)
// {
//     size_t count = 5;
//     size_t size = 5;
//     int *array = (int *)ft_calloc(count, size);
//     if (!array)
//     {
//         printf("Allocation failed!");
//         return (1);
//     }
//     printf("Elements of array after ft_calloc:\n");
//     size_t i = 0;
//     while (i < count)
//     {
//         printf("array [%zu] = %d\n", i, array[i]);
//         i++;
//     }
//     free(array);

//     int *array2 = (int *)calloc(count, size);
//     if (!array2)
//     {
//         printf("Allocation failed!");
//         return (1);
//     }
//     printf("Elements of array after calloc:\n");
//     i = 0;
//     while (i < count)
//     {
//         printf("array [%zu] = %d\n", i, array2[i]);
//         i++;
//     }
//     free(array2);
//     return (0);
// }