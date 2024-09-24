/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:27:51 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/24 12:31:38 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_firstcmd	*command_table;
	int i;
	int found;
	command_table = init_command_table();
	printf("\033[H\033[J"); // clears terminal
	while (1)
	{
		input = prompt();
		argv = ft_split(input, ' ');
		argc = 0;
		i = 0;
		found = 0;
		while (argv[argc])
			argc++;
		if (argc > 0)
		{
			while (command_table[i].name != NULL)
			{
				if (ft_strncmp(argv[0], command_table[i].name,
						ft_strlen(command_table[i].name)) == 0)
				{
					command_table[i].func(argv, envp);
					found = 1;
					break ;
				}
				i++;
			}
			if (ft_strncmp(argv[0], "exit", ft_strlen("exit")) == 0)
				exit_function(command_table, argv, input);
			else if(!found)
				execute_path(argv, envp);
		}
		free_call(argv, input);
	}
}

void	free_call(char **argv, char *input)
{
	int	i;

	free(input);
	i = 0;
	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void exit_function(t_firstcmd *command_table, char **argv, char *input)
{
	printf("GOODBYE NYA\n");
	free(command_table);
	free_call(argv, input);
	exit(0);
}