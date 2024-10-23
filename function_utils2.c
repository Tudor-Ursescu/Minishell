/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:14:10 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/23 15:00:43 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	print_spaces(char **argv)
{
	int	first_word;
	int	i;

	i = 1;
	first_word = 1;
	while (argv[i])
	{
		if (argv[i][0] != '\0')
		{
			if (!first_word)
				printf(" ");
			printf("%s", argv[i]);
			first_word = 0;
		}
		i++;
	}
	printf("\n");
}

int	check_and_print_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd_list->args[i])
	{
		if (data->cmd_list->args[i] && data->cmd_list->args[0][0] == '$')
		{
			data->cmd_list->args[i] = handle_env(data->cmd_list->args[i],
					data->new_env);
			printf("%s ", data->cmd_list->args[i]);
			free(data->cmd_list->args[i]);
			data->cmd_list->args[i] = ft_strdup("");
			printf("command not found:\n");
			data->exit = 127;
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_and_print_exit(t_data *data)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (data->cmd_list->args[i])
	{
		if (data->cmd_list->args[i] && (ft_strncmp(data->cmd_list->args[i],
					"$?", ft_strlen("$?")) == 0))
		{
			free(data->cmd_list->args[i]);
			data->cmd_list->args[i] = ft_itoa(data->exit);
			flag = 1;
		}
		i++;
	}
	return (0);
}

void	cmd_not_found(t_cmd *cmd_list, t_data *data)
{
	char	*exit_str;

	exit_str = ft_itoa(data->exit);
	if ((ft_strncmp(cmd_list->args[0], exit_str,
				ft_strlen(cmd_list->args[0])) == 0))
	{
		free(cmd_list->args[0]);
		cmd_list->args[0] = ft_strdup("");
	}
	printf("command not found: %s\n", cmd_list->args[0]);
	data->exit = 127;
	free(exit_str);
}

void	fork_and_execute(char *path, t_cmd *cmd_list, t_data *data, int pid)
{
	if (check_fork(&pid) == 1)
		return ;
	if (pid == 0)
	{
		if (execve(path, cmd_list->args, data->new_env) == -1)
		{
			perror("cat_shell ");
			exit(1);
		}
	}
	else
	{
		waitandsave(pid, data);
		free(path);
	}
}
