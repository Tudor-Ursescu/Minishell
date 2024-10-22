/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:27:51 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/22 10:21:39 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

int g_exit = 0;
int	main(int argc, char **argv, char **envp)
{
	t_data data;
	init_tdata(argc, argv, envp, &data);
	signal_init();
	while (1)
	{
		data.line = prompt();
		if (data.new_env)
			free_matrix(data.new_env);
		data.new_env = env_to_array(data.env);
		data.token_list = tokenize(data.line);
		if (!data.token_list)
		{
			free(data.line);
			continue;
		}	
		if (check_syntax(data.token_list))
		{
			free_tokens(&data.token_list);
			free(data.line);
			continue;
		}
		data.cmd_list = create_cmd_list(data.token_list);
		if (!data.cmd_list)
		{
			printf("Parsing failed!\n");// if possible i want this block of code inside create_cmd_list
			free(data.line);
			free_tokens(&data.token_list);
			return (0);
		}
		if (data.line)
		{
			if (ft_strncmp(data.line, "$?", ft_strlen("$?")) == 0)
				printf("%d ", data.exit);
			if (ft_strncmp(data.line, "exit", ft_strlen("exit")) == 0)
			{
				exit_function(&data, data.line);
			}
			data.pipeinfo = initialize_pipeinfo(data.token_list);
			if (data.pipeinfo.number_of_pipes > 0)
			{
				handle_pipe(&data, data.cmd_list, data.pipeinfo);
			}
			else if (data.pipeinfo.number_of_pipes == 0)
				handle_redirect_or_execute(&data, data.cmd_list);
		}
		free_all(data.cmd_list, data.token_list);
		free(data.line);
		
	}
	if (data.new_env)
		free_matrix(data.new_env);
	free_env(&data.env);
}

void init_tdata(int argc, char **argv, char **envp, t_data *data)
{
	printf("\033[H\033[J");
	(void)argc;
	(void)argv;
	data->line = NULL;
    data->token_list = NULL;
    data->cmd_list = NULL;
    data->env = init_env_list(envp);
	data->new_env = NULL;
    data->exit = 0;
    data->is_heredoc = 0;
}

void    free_call(char **argv, char *input)
{
    int i;
    free(input);
    i = 0;
    while (argv[i] != NULL)
    {
        free(argv[i]);
        i++;
    }
    free(argv);
}

void    exit_function(t_data *data, char *input)
{
    printf("GOODBYE NYA\n");
    free_call(data->cmd_list->args, input);
    exit(0);
}

void restore_fds(int saved_stdin, int saved_stdout)
{
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
}


