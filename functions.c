/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:29:44 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/24 12:26:55 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_firstcmd	*init_command_table(void)
{
	t_firstcmd	*command_table;

	command_table = malloc(6 * sizeof(t_firstcmd));
	if (!command_table)
	{
		perror("Failed to allocate memory for command table");
		exit(1);
	}
	// Initialize commands
	command_table[0] = (t_firstcmd){"cd", cd_function};
	command_table[1] = (t_firstcmd){"pwd", pwd_function};
	command_table[2] = (t_firstcmd){"export", export_function};
	command_table[3] = (t_firstcmd){"echo", echo};
	command_table[4] = (t_firstcmd){"env", env_function};
	command_table[5] = (t_firstcmd){NULL, NULL};
	return (command_table);
}

void env_function(char **argv, char **envp)
{
	(void)argv;
    while (*envp) 
	{
        printf("%s\n", *envp);  // Print each environment variable
        envp++;  // Move to the next environment variable
    }
}


