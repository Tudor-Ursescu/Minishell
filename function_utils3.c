/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:01:41 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/25 10:57:26 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <string.h>

char	*concat_2d_arr(char **arr)
{
	int		i;
	int		total_len;
	char	*res;

	i = 0;
	total_len = find_total_length(arr);
	res = (char *)malloc(total_len + 1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	i = 0;
	while (arr[i])
	{
		ft_strcat(res, arr[i]);
		if (arr[i + 1])
			ft_strcat(res, " ");
		i++;
	}
	return (res);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	dest_len;

	dest_len = 0;
	while (dest[dest_len])
		dest_len++;
	i = 0;
	while (src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}

int	find_total_length(char **arr)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (arr[i])
	{
		res += ft_strlen(arr[i]);
		if (arr[i + 1])
			res += 1;
		i++;
	}
	return (res);
}
