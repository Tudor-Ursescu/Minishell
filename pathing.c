/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:25:58 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/25 15:12:58 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_path(char **argv, char **envp)
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
			if (execve(path, argv, envp) == -1) 
			{
				perror("execve failed");
				exit(1);
			}
		}
		else
		{
			waitpid(pid, NULL, 0);
			free(path);
		}
	}
	else
	{
		printf("uwushell: command not found: %s\n", argv[0]);
		if (pid == 0)
		{
			exit(1);
		} // If path not found, also exit the child
	}
}

char	*find_path(const char *cmd)
{
	char	*path;
	char	*full_path;
	char	**tokens;

	full_path = NULL;
	path = getenv("PATH");
	tokens = ft_split(path, ':');
	if (!full_path || !tokens)
	{
		free_tokens(tokens);
		free(full_path);
		return (NULL);
	}
	full_path = stitching(NULL, tokens, cmd);
	if (full_path != NULL)
		return(full_path);
	free_tokens(tokens);
	free(full_path);
	return (NULL);
}

char	*stitching(char *full_path, char **tokens, const char *cmd)
{
	int i;

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
	return(NULL);
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
