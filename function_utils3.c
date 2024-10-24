/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:01:41 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/24 15:36:18 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <string.h>


// char	*concat_2d_arr(char **arr)
// {
// 	int	i;
// 	char *res;
// 	char *temp;

// 	i = 1;
// 	res = ft_strdup(arr[0]);
// 	while (arr[i])
// 	{
// 		temp = res;
// 		res = ft_strjoin(res, arr[i]);
// 		free(temp);
// 		temp = res;
// 		res = ft_strjoin(res, " ");
// 		free(temp);
// 		i++;
// 	}
// 	res[ft_strlen(res) - 1] = '\0';
// 	return (res);
// }

char* concat_2d_arr(char **arr) {
	int		i;
	int		total_len;
	char	*res;

	i = 0;
	total_len = 0;

	// Calculate the total length needed for the final string
	while (arr[i])
	{
		total_len += strlen(arr[i]);  // Length of each string
		if (arr[i + 1]) // Add space between words (but not at the end)
			total_len += 1;
		i++;
	}

	// Allocate memory for the final string (+1 for null terminator)
	res = (char *)malloc(total_len + 1);
	if (!res)
		return (NULL);

	res[0] = '\0'; // Initialize empty string

	// Stitch the array into the final string
	i = 0;
	while (arr[i])
	{
		strcat(res, arr[i]);  // Append current word
		if (arr[i + 1])       // Add space if it's not the last word
			strcat(res, " ");
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