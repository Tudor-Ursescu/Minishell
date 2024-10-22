/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:25:58 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/22 11:50:41 by ckonneck         ###   ########.fr       */
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
	if (cmd_list->args[0][0] == '/')
	{
		execute_absolute(path, cmd_list->args, data);
		return ;	
	}
	else if (cmd_list->args[0][0] == '.')
	{
		execute_relative(path, cmd_list->args, data);
		return ;
	}
	
	path = find_path(cmd_list->args[0]);
	if (path != NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			// signal(SIGINT, SIG_DFL);
			if (execve(path, cmd_list->args, data->new_env) == -1)
			{
				perror("cat_shell: ");
				exit(1);
			}
		}
		else
		{
			waitandsave(pid, data);
			// signal(SIGINT, load_ammo);
			// while(waitpid(pid, NULL, 0))
			// {
				// if(g_sig == 1)
				// {
				// 	printf("\n");
				// 	kill(pid, SIGKILL);
				// 	break;
				// }
			// }
			// g_sig = 0;
			// signal(SIGINT, handle_sigint);
			 // maybe handle with the child ignoring the signal, and parent
			free(path);// killing the child when the signal is received. would involve global signal though maybe
		}
	}
	else
	{
		printf("command not found: %s\n", cmd_list->args[0]);
		data->exit = 127;
		// exit(127);
		// if (pid == 0)
		// {
		// 	free(path);
		// 	exit(126);
		// }
	}

}

void waitandsave(int pid, t_data *data)
{
	int status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		data->exit = WEXITSTATUS(status);
	}
}

int check_if_builtin(char **envp, t_cmd *cmd_list, t_data *data)
{
	t_firstcmd	*command_table;
	command_table = init_command_table();

	if(execbuiltin(envp, command_table, cmd_list, data) == 1)
	{
		free(command_table);
		g_exit = 0;
		return (1);
	}
	free(command_table);
	return(0);
}

void execute_absolute(char *path, char **argv, t_data *data)
{
	int		pid;

	pid = 1;
	path = argv[0];
	if (path != NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(path, argv, data->new_env) == -1)//same as below, can be summarized
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
		printf("command not found: %s\n", argv[0]);
		// if (pid == 0)
		// 	exit(1);
	}
}

void execute_relative(char *path, char **argv, t_data *data)
{
	int		pid;

	pid = 1;
	path = argv[0];
	if (path != NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(path, argv, data->new_env) == -1)//same as above, can be summarized
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
		printf("command not found: %s\n", argv[0]);
		// if (pid == 0)
		// 	exit(1);
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
	free_tokensexec(tokens);
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

void	free_tokensexec(char **tokens)
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
