/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:50:47 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/19 17:25:57 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*newstr;
	int		srl;
	int		i;

	i = 0;
	srl = (ft_strlen(s1)) + (ft_strlen(s2));
	newstr = malloc((srl + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	if (!s1 || !s2)
		return (NULL);
	while (*s1)
		newstr[i++] = *s1++;
	while (*s2)
		newstr[i++] = *s2++;
	newstr[i] = '\0';
	return (newstr);
}

// #include <stdio.h>

// int main(void)
// {
//  char *str1 = "Hello";
//  char *str2 = " world";
//  char  *res = ft_strjoin(str1, str2);
//  printf("%s", res);
//  free(res);
//  return (0);
// }
