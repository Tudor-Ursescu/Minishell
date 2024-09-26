/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:18:06 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/26 13:33:53 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	echo(char **argv, char **envp)
{
	int	i;

	i = 1;
	if (argv[1])
	{
		if (echo3(argv, envp) == 1)
			return ;
		if (!(ft_strncmp(argv[1], "-n", ft_strlen(argv[1])) == 0))
		{
			while (argv[i])
			{
				printf("%s", argv[i]);
				if (argv[i + 1])
					printf(" ");
				i++;
			}
			printf("\n");
		}
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
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		else if (!argv[i + 1] && (ft_strncmp(argv[1], "-n",
					ft_strlen(argv[1])) == 0))
			printf("\033[30;47m%%\033[0m");
		i++;
	}
	printf("\n");
}
int	echo3(char **argv, char **envp)
{
	if (argv[1] && argv[1][0] == '$')
		return (handle_env(argv[1], envp));
	else if (argv[2] && (ft_strncmp(argv[1], "-n", ft_strlen(argv[1])) == 0)
		&& argv[2][0] == '$')
		return (handle_n_flag(argv[2], envp));
	return (0);
}

int	handle_env(char *arg, char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(arg + 1, *envp, ft_strlen(arg + 1)) == 0
			&& (*envp)[ft_strlen(arg + 1)] == '=')
		{
			printf("%s", *envp + ft_strlen(arg));
			printf("\n");
			return (1);
		}
		envp++;
	}
	return (0);
}

int	handle_n_flag(char *arg, char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(arg + 1, *envp, ft_strlen(arg + 1)) == 0
			&& (*envp)[ft_strlen(arg + 1)] == '=')
		{
			printf("%s", *envp + ft_strlen(arg));
			printf("\033[30;47m%%\033[0m");
			printf("\n");
			return (1);
		}
		envp++;
	}
	return (0);
}