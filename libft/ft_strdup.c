/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:00:46 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/19 14:47:53 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		j;
	char	*copy;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	copy = malloc(i + 1);
	if (!copy)
		return (NULL);
	while (s[j])
	{
		copy[j] = s[j];
		j++;
	}
	copy[i] = '\0';
	return (copy);
}

// #include <stdio.h>
// #include <string.h>

// int main(void)
// {	
// 	char *copy = "who";
// 	printf("string before duplicate: \"%s\"\n",copy);
// 	char *str = "ababa";
// 	copy = ft_strdup(str);
//     printf("string  after duplicate: \"%s\"\n",copy);
//     free(copy);
// 	char *copy2 = "who";
// 	printf("stringman before duplicate: \"%s\"\n",copy2);
// 	char *str2 = "ababa";
// 	copy2 = strdup(str);
//     printf("stringman  after duplicate: \"%s\"\n",copy2);
//     free(copy2);
// }