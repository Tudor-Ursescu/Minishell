/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:45:14 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/11 12:59:06 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*copy;

	i = 0;
	copy = malloc(n + 1);
	if (!copy)
		return (NULL);
	while (s[i] && i < n)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

int	ft_strcmp(const char *s1, char const *s2)
{
	int				result;
	unsigned int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
		{
			result = (unsigned char)s1[i] - (unsigned char)s2[i];
			return (result);
		}
		i++;
	}
	return (0);
}

int skip_whitespace(char *line, int i)
{
    while(line[i] && ft_isspace(line[i]))
        i++;
    return (i);
}

void	remove_quotes(char ** value)
{
	size_t	len;
	char	*temp;

	if (!value || !*value)
		return;
	len = ft_strlen(*value);
	if ((*value[0] == '"' && (*value)[len - 1] == '"') ||
		(*value [0] == '\'' && (*value)[len - 1] == '\''))
	{
		temp = ft_strndup((*value) + 1, len - 2);
		if (temp)
		{
			free(*value);
			*value = temp;
		}
	}
}

int	has_char(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}