/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:18:06 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/23 14:13:48 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	echo(char **argv, char **envp, t_data *data)
{
	int	i;

	data->exit = 0;
	i = 1;
	if (argv[1])
	{
		if (echo3(argv, envp) == 1)
			return ;
		if (!(ft_strncmp(argv[1], "-n", ft_strlen(argv[1])) == 0))
			print_spaces(argv);
		else
			echo2(argv, i);
	}
	else
		printf("\n");
}

void	echo2(char **argv, int i)
{
	i = 2;
	if (!argv[2])
		return ;
	while (argv[i])
	{
		while (argv[i + 1] && ((ft_strncmp(argv[i], "-n",
						ft_strlen(argv[i])) == 0)))
			i++;
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
}

int	echo3(char **argv, char **envp)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] && argv[i][0] == '$')
			argv[i] = handle_env(argv[i], envp);
		else if (argv[i] && (ft_strncmp(argv[i], "-n", ft_strlen(argv[i])) == 0)
			&& argv[i][0] == '$')
			return (handle_n_flag(argv[i], envp));
		i++;
	}
	return (0);
}

char	*handle_env(char *arg, char **envp)
{
	char	*env_value;

	while (*envp)
	{
		if (ft_strncmp(arg + 1, *envp, ft_strlen(arg + 1)) == 0
			&& (*envp)[ft_strlen(arg + 1)] == '=')
		{
			env_value = *envp + ft_strlen(arg + 1) + 1;
			free(arg);
			arg = ft_strdup(env_value);
			return (arg);
		}
		envp++;
	}
	free(arg);
	arg = ft_strdup("");
	return (arg);
}

int	handle_n_flag(char *arg, char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(arg + 1, *envp, ft_strlen(arg + 1)) == 0
			&& (*envp)[ft_strlen(arg + 1)] == '=')
		{
			printf("%s", *envp + ft_strlen(arg));
			return (1);
		}
		envp++;
	}
	return (0);
}
