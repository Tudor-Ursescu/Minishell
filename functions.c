/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:29:44 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/22 09:58:48 by ckonneck         ###   ########.fr       */
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
	// command_table[4] = (t_firstcmd){"env", NULL, handle_env_tudor};
	// command_table[5] = (t_firstcmd){"unset", NULL, handle_unset};
	// command_table[6] = (t_firstcmd){NULL, NULL, NULL};
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


int execbuiltin(char **envp, t_firstcmd *command_table, t_cmd *cmd_list)
{
	int i;
	
	i = 0;
	while (command_table[i].name != NULL)
	{
		if (ft_strncmp(cmd_list->args[0], command_table[i].name,
				ft_strlen(command_table[i].name)) == 0)
		{
			if (command_table[i].func != NULL)
            {
                command_table[i].func(cmd_list->args, envp);//vlagrind conditional jump, prolly because of commented functions
				i++;
            }
            // // Check if the second function pointer is not NULL
            // else if (command_table[i].func2 != NULL)
            // {
            //     command_table[i].func2(&env_list, tokens); // Pass your env_list and tokens
            // }
            return (1); // Command found and executed
		}
		i++;
	}
	return(0);
}
