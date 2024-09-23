/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:29:44 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/20 15:13:40 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command_table(void)
{
	t_command	*command_table;

	command_table = malloc(11 * sizeof(t_command));
	if (!command_table)
	{
		perror("Failed to allocate memory for command table");
		exit(1);
	}
	// Initialize commands
	command_table[0] = (t_command){"echo", echo};
	command_table[1] = (t_command){"cd", cd_function};
	command_table[2] = (t_command){"pwd", pwd_function};
	command_table[3] = (t_command){"ls", ls_function};
	command_table[4] = (t_command){"uwu", uwu_function};
	command_table[5] = (t_command){"punch", punch_or_hit_function};
	command_table[6] = (t_command){"hit", punch_or_hit_function};
	command_table[7] = (t_command){"clear", clear_function};
	command_table[8] = (t_command){"env", env_function};
	command_table[9] = (t_command){"export", export_function};
	command_table[10] = (t_command){NULL, NULL};
	return (command_table);
}

void	uwu_function(char **argv)
{
	(void)argv;
	printf("UWU COMRADE\n");
}

void punch_or_hit_function(char **argv)
{
	(void)argv;
	printf("ow that hurt you baka. piece of unko >:[\n");
}

void clear_function(char **argv)
{
	(void)argv;
	printf("\033[H\033[J");
}
void env_function(char **argv)
{
	(void)argv;
    while (*g_env) 
	{
        printf("%s\n", *g_env);  // Print each environment variable
        g_env++;  // Move to the next environment variable
    }
}


