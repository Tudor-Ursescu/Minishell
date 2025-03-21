/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:56:32 by tursescu          #+#    #+#             */
/*   Updated: 2025/03/21 10:20:24 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int	is_n_flag(char *str)
{
	int	i;

	i = 2;
	if (str[0] == '-' && str[1] == 'n')
	{
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	else
		return (0);
}

int	dollarcheck(t_data *data)
{
	if (ft_strncmp(data->line, "$?", ft_strlen("$?")) == 0)
		printf("%d: ", data->exit);
	check_and_print_exit(data);
	if (check_and_print_env(data) == 1)
		return (1);
	return (0);
}

void	pwd_function(char **argv, char **envp, t_data *data)
{
	char	path[1024];
	int		argc;

	(void)envp;
	argc = 0;
	while (argv[argc])
		argc++;
	if (argc == 1)
	{
		getcwd(path, sizeof(path));
		printf("%s\n", path);
		data->exit = 0;
	}
	else
	{
		printf("pwd: too many arguments\n");
		data->exit = 1;
	}
}

char *ft_strcpy(char *dest, const char *src)
{
	int i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size)
{
	size_t	i;
	size_t	src_len;
	
	src_len = 0;
	while(src[src_len])
		src_len++;
	if (dest_size == 0)
		return (src_len);
	i = 0;
	while (src[i] && i < (dest_size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}

char *ft_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len;
	size_t i;
	
	dest_len = 0;
	while (dest[dest_len])
		dest_len++;
	i = 0;
	while (src[i] && i < n)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}