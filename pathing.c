/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:25:58 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/23 15:00:33 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

void	execute_path(t_cmd *cmd_list, t_data *data)
{
	char	*path;
	int		pid;

	path = NULL;
	pid = 1;
	if (check_if_builtin(data->new_env, cmd_list, data) == 1)
		return ;
	if (cmd_list->args[0] && (cmd_list->args[0][0] == '/'
		|| cmd_list->args[0][0] == '.'))
	{
		execute_absolute_or_relative(path, cmd_list->args, data);
		return ;
	}
	path = find_path(cmd_list->args[0], data);
	if (path != NULL)
		fork_and_execute(path, cmd_list, data, pid);
	else if (cmd_list->args[0])
		cmd_not_found(cmd_list, data);
}

void	execute_absolute_or_relative(char *path, char **argv, t_data *data)
{
	int	pid;

	pid = 1;
	path = argv[0];
	if (path != NULL)
	{
		if (check_fork(&pid) == 1)
			return ;
		if (pid == 0)
		{
			if (execve(path, argv, data->new_env) == -1)
			{
				perror("cat_shell");
				exit(1);
			}
		}
		else
			waitandsave(pid, data);
	}
	else
	{
		printf(":command not found %s\n", argv[0]);
		data->exit = 127;
	}
}

char	*find_path(const char *cmd, t_data *data)
{
	char	*path;
	char	*full_path;
	char	**tokens;

	path = getpath("PATH=", data);
	if (!path)
		return (NULL);
	tokens = ft_split(path, ':');
	if (!tokens)
		return (NULL);
	full_path = stitching(tokens, cmd);
	free_tokensexec(tokens);
	return (full_path);
}

char *getpath(char *pathstring, t_data *data)
{
	int i;

	i = 0;
	while(data->new_env[i])
	{
		if (ft_strncmp(data->new_env[i], pathstring, ft_strlen(pathstring)) == 0)
			return(data->new_env[i] + ft_strlen(pathstring));
		i++;
	}
	return (NULL);
}

char	*stitching(char **tokens, const char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	if (cmd)
	{
		while (tokens[i])
		{
			full_path = malloc(1024);
			if (!full_path)
				return (NULL);
			ft_strlcpy(full_path, tokens[i], 1024);
			ft_strlcat(full_path, "/", ft_strlen(full_path) + 2);
			ft_strlcat(full_path, cmd, ft_strlen(full_path) + ft_strlen(cmd)
				+ 2);
			if (access(full_path, X_OK) == 0)
				return (full_path);
			free(full_path);
			i++;
		}
	}
	return (NULL);
}
