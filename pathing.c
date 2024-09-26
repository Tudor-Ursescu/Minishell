/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:25:58 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/26 13:33:53 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execute_path(char **argv, char **envp)
{
	char	*path;
	int		pid;

	pid = 1;
	path = find_path(argv[0]);//too static, need to change
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
			free(path);
			exit(1);
		}
	}
}

char	*find_path(const char *cmd)
{
	char	*path;
	char	*full_path;
	char	**tokens;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	tokens = ft_split(path, ':');
	if (!tokens)
		return (NULL);
	full_path = stitching(tokens, cmd);
	free_tokens(tokens);
	return (full_path);
}

char	*stitching(char **tokens, const char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (tokens[i])
	{
		full_path = malloc(1024);
		if (!full_path)
			return (NULL);
		ft_strlcpy(full_path, tokens[i], 1024);
		ft_strlcat(full_path, "/", ft_strlen(full_path) + 2);
		ft_strlcat(full_path, cmd, ft_strlen(full_path) + ft_strlen(cmd) + 2);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
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
