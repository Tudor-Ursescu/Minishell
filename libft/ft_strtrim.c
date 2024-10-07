/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:26:04 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/19 16:55:15 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	char	*str;

	str = NULL;
	start = 0;
	if (s1 != 0 && set != 0)
	{
		end = ft_strlen(s1);
		while (s1[start] && ft_strchr(set, s1[start]))
			start++;
		while (ft_strchr(set, s1[end - 1]) && end > start)
			end--;
		str = malloc(sizeof(char) * (end - start + 1));
		if (str == NULL)
			return (NULL);
		ft_strlcpy(str, &s1[start], end - start + 1);
	}
	return (str);
}

// #include <stdio.h>
// int main (void)
// {
// 	char str[] = "abcdba";
// 	char set[] = "ba";
// 	char *new = ft_strtrim(str,set);
// 	printf("trimmed:%s",new) ;
// 	free(new);
// 	return (0);
// }
