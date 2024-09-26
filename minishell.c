/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:27:51 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/26 15:10:52 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parser.h"
int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_firstcmd	*command_table;
	int			i;
	int			found;
	int 		count;
	t_args *arg_list;
	argc = 0;
	argv = 0;
	command_table = init_command_table();
	while (1)
	{
		count = 0;
		arg_list = NULL;
		input = prompt();
		count = parse_args(&arg_list, input);
		print_arg_list(arg_list);
		i = 0;
		found = 0;
		// int pipenumber = 0;
		if (count > 0)
		{
			while (command_table[i].name != NULL)
			{
				if (ft_strncmp(arg_list->value, command_table[i].name,
						ft_strlen(command_table[i].name)) == 0)
				{
					command_table[i].func(arg_list, envp);
					found = 1;
					break ;
				}
				i++;
			}
			if (ft_strncmp(arg_list->value, "exit", ft_strlen("exit")) == 0)
				exit_function(command_table, argv, input, arg_list);
			// int k = 0;
			// while (arg_list != NULL)
			// {
			// 	if (ft_strncmp(argv[k], "|", ft_strlen("|")) == 0)
			// 		pipenumber++;
			// 	arg_list = arg_list->next;
			// }
			// if (pipenumber > 0)
			// 	handle_pipe(argv, k, envp);
			
			if (!found)
				handle_redirect_or_execute(arg_list, envp);
		}
		free_args(&arg_list);
		free(input);
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

void	exit_function(t_firstcmd *command_table, char **argv, char *input, t_args *arg_list)
{
	(void)argv;
	printf("GOODBYE NYA\n");
	free(command_table);
	free_args(&arg_list);
	// free_call(argv, input);
	free(input);
	exit(0);
}

void	handle_redirect_or_execute(t_args *arg_list, char **envp)
{
	// if (argv[1] && ft_strncmp(argv[1], "<<", ft_strlen("<<")) == 0)
	// 	heredoc(argv, envp);
	// else if (argv[1] && ft_strncmp(argv[1], "<", ft_strlen("<")) == 0)
	// 	input_redirect(argv, envp);
	// else if (argv[1] && ft_strncmp(argv[1], ">>", ft_strlen(">>")) == 0)
	// 	output_append(argv, envp);
	// else if (argv[1] && ft_strncmp(argv[1], ">", ft_strlen(">")) == 0)
	// 	output_redirect(argv, envp);
	// else
		execute_path(arg_list, envp);
}