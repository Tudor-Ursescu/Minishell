/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:36:28 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/19 17:26:05 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	srclen;
	unsigned int	destlen;

	i = 0;
	destlen = ft_strlen(dest);
	j = destlen;
	srclen = ft_strlen(src);
	if (size == 0 || size <= destlen)
		return (srclen + size);
	while (src[i] && i < (size - destlen -1))
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (srclen + destlen);
}

// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
// 	char src[] = "aiuwbdyuia";
// 	char dest[] = "";
// 	ft_strlcat(dest, src, 5);
// 	printf("%s", dest);
// }