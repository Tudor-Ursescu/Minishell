/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:29:44 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/22 17:30:16 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_firstcmd	*init_command_table(void)
{
	t_firstcmd	*command_table;

	command_table = malloc(7 * sizeof(t_firstcmd));
	if (!command_table)
	{
		perror("Failed to allocate memory for command table");
		exit(1);
	}
	command_table[0] = (t_firstcmd){"cd", cd_function, NULL};
	command_table[1] = (t_firstcmd){"pwd", pwd_function, NULL};
	command_table[2] = (t_firstcmd){"export", NULL, handle_export};
	command_table[3] = (t_firstcmd){"echo", echo, NULL};
	command_table[4] = (t_firstcmd){"env", NULL, handle_env_tudor};
	command_table[5] = (t_firstcmd){"unset", NULL, handle_unset};
	command_table[6] = (t_firstcmd){NULL, NULL, NULL};
	return (command_table);
}

int	execbuiltin(char **envp, t_firstcmd *command_table, t_cmd *cmd_list,
		t_data *data)
{
	int	i;

	i = 0;
	while (command_table[i].name != NULL)
	{
		if (cmd_list->args[0])
		{
			if (ft_strncmp(cmd_list->args[0], command_table[i].name,
					ft_strlen(cmd_list->args[0])) == 0)
			{
				if (command_table[i].func != NULL)
					command_table[i].func(cmd_list->args, envp, data);
				else if (command_table[i].func2 != NULL)
					command_table[i].func2(&data->env, data->token_list, data);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_if_builtin(char **envp, t_cmd *cmd_list, t_data *data)
{
	t_firstcmd	*command_table;

	command_table = init_command_table();
	if (execbuiltin(envp, command_table, cmd_list, data) == 1)
	{
		free(command_table);
		return (1);
	}
	free(command_table);
	return (0);
}

int	check_fork(int *pid)
{
	*pid = fork();
	if (*pid < 0)
		return (1);
	return (0);
}

void	exit_function(t_data *data, char *input)
{
	printf("GOODBYE NYA\n");
	free_call(data->cmd_list->args, input);
	exit(0);
}
