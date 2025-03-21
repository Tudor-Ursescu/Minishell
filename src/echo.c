/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:18:06 by ckonneck          #+#    #+#             */
/*   Updated: 2025/03/21 10:19:50 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"


void	echo(char **argv, char **envp, t_data *data)
{
	int	i;

	data->exit = 0;
	i = 1;
	if (argv[1])
	{
		if (echo3(argv, envp, data) == 1)
			return ;
		if (is_n_flag(argv[1]))
			i = 2;
		else
			i = 1;
		echo2(argv, i, is_n_flag(argv[1]));
	}
	else
	{
		printf("\n");
	}
}

void	echo2(char **argv, int i, int no_newline)
{
	// Loop through arguments starting from i
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}

	// Print newline only if `-n` flag is not present
	if (!no_newline)
		printf("\n");
}


int	echo3(char **argv, char **envp, t_data *data)
{
	int		i;
	t_token	*temp;

	temp = data->token_list;
	i = 0;
	while (argv[i] && argv[i + 1])
	{
		if (argv[i] && argv[i][0] == '$' && temp && temp->type != 1)
			argv[i] = handle_env(argv[i], envp);
		if (argv[i] && is_n_flag(argv[i]) && argv[i][0] == '$')
			return (handle_n_flag(argv[i], envp));
		i++;
		temp = temp->next;
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
	return (ft_strdup(""));
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
