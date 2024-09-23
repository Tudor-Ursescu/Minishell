/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:00:07 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/20 12:54:24 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo3(char **argv)
{
	if (argv[1] && argv[1][0] == '$')
		return (handle_env(argv[1]));
	else if (argv[2] && (ft_strncmp(argv[1], "-n", ft_strlen(argv[1])) == 0)
		&& argv[2][0] == '$')
		return (handle_n_flag(argv[2]));
	return (0);
}

int	handle_env(char *arg)
{
	while (*g_env)
	{
		if (ft_strncmp(arg + 1, *g_env, ft_strlen(arg + 1)) == 0
			&& (*g_env)[ft_strlen(arg + 1)] == '=')
		{
			printf("%s", *g_env + ft_strlen(arg));
			printf("\n");
			return (1);
		}
		g_env++;
	}
	return (0);
}

int	handle_n_flag(char *arg)
{
	while (*g_env)
	{
		if (ft_strncmp(arg + 1, *g_env, ft_strlen(arg + 1)) == 0
			&& (*g_env)[ft_strlen(arg + 1)] == '=')
		{
			printf("%s", *g_env + ft_strlen(arg));
			printf("\033[30;47m%%\033[0m");
			printf("\n");
			return (1);
		}
		g_env++;
	}
	return (0);
}