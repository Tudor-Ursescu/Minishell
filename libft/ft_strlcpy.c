/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:38:26 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/19 15:57:21 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = ft_strlen(src);
	if (!size)
		return (i);
	while (--size && *src)
		*dest++ = *src++;
	*dest = '\0';
	return (i);
}

// decrementing size first because null terminator
// #include <string.h>
// #include <strings.h>
// #include <stdio.h>
// /* strlcpy based on OpenBSDs strlcpy */ 
// #include <stdio.h>
// #include <sys/types.h>
// int main(void)
// {
// 	char src[] = "12345";
// 	char dest[] = "";
// 	ft_strlcpy(dest, src, 5);
// 	printf("mine %s \n", dest);
// }