/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:25:58 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/23 17:27:22 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_path(char **argv, char **g_env)
{
	char	*path;
	int		pid;

	pid = 1;
	path = find_path(argv[0]);
	if (path != NULL)
	{
		if (check_fork(&pid))
			return ;
		if (pid == 0)
		{
			if (execve(path, argv, g_env) == -1) // shit still breaks with stuff like open or code . // 
												//prolly g_env error. need accurate environment path
			{
				perror("execve failed"); // Use perror to explain the error
				exit(1);                 // Terminate the child if execve fails
			}
		}
		else
			waitpid(pid, NULL, 0);
	}
	else
	{
		printf("uwushell: command not found: %s\n", argv[0]);
		if (pid == 0) // If path not found, also exit the child
			exit(1);
	}
}

char	*find_path(const char *cmd)
{
	char	*path;
	char	**tokens;
	char	*full_path;
	int		i;

	path = getenv("PATH");
	tokens = ft_split(path, ':');
	full_path = malloc(1024);
	if (!full_path || !tokens)
	{
		free(full_path);
		return (NULL);
	}
	i = 0;
	while (tokens[i])
	{
		ft_strlcpy(full_path, tokens[i], 1024);
		ft_strlcat(full_path, "/", ft_strlen(full_path) + 2);
		ft_strlcat(full_path, cmd, ft_strlen(full_path) + ft_strlen(cmd) + 2);
		if (access(full_path, X_OK) == 0)
		{
			free_tokens(tokens);
			return (full_path);
		}
		i++;
	}
	i = 0;
	free_tokens(tokens);
	free(full_path);
	return (NULL);
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

int	check_fork(int *pid)
{
	*pid = fork();
	if (*pid < 0)
		return (1);
	return (0);
}
