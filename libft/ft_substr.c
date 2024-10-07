/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 08:46:07 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/19 17:26:34 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*substring;
	unsigned int	slen;

	i = 0;
	slen = ft_strlen(s);
	if (start > slen)
		len = 0;
	else if (len > (slen - start))
		len = slen - start;
	substring = malloc((len + 1) * sizeof(char));
	if (substring == NULL)
		return (NULL);
	while (i < len)
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

// #include <stdio.h>
// int main(void)
// {
//     // Test case 1: Normal operation expected result : world
//     {
//         char str[] = "01234";
//         char* sub = ft_substr(str, 0, 4);
//         printf("Test 1: %s\n",sub);
//         free(sub); // Don't forget to free the allocated memory
//     }
//     return 0;
// }