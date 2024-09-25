/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:22:00 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/25 16:21:14 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_array(size_t i, char **array)
{
	while (i > 0)
	{
		i--;
		free(array[i]);
	}
	free(array);
}

static size_t	wordlen(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static size_t	count_words(const char *s, char c)
{
	size_t	counter;
	size_t	i;

	counter = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			counter++;
			while (s[i] && s[i] != c)
				i++;
		}
		else if (s[i] == c)
			i++;
	}
	return (counter);
}

static char	**splat(const char *s, char c, char **array, size_t words_count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < words_count)
	{
		while (s[j] && s[j] == c)
			j++;
		array[i] = ft_substr(s, j, wordlen((s + j), c));
		if (array[i] == NULL)
		{
			free_array(i, array);
			return (NULL);
		}
		while (s[j] && s[j] != c)
			j++;
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(const char *s, char c)
{
	char	**array;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	array = malloc((words + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	if (!splat(s, c, array, words)) // Ensure splat works
    {
        free(array); // Free allocated memory if splat fails
        return (NULL);
    }
	return (array);
}

// #include <stdio.h>
// int main (void)
// {
//      const char *str1 = "hello world";
//      char **result1 = ft_split(str1, ' ');
//       // Print the result of test case 1
//      printf("Test case 1:\n");
// 	int i = 0;
// 	while (result1[i]) {
//     printf("%s\n", result1[i]);
//     free(result1[i]); // Free each substring
//     i++;
//      free(result1); 
// 	}
// }
// line 67 also okay as wordlen((&s[j]), c));