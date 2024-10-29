/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:27:51 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/29 11:34:04 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	init_tdata(argc, argv, envp, &data);
	signal_init();
	while (1)
	{
		data.line = prompt();
		if (init_loop(&data) == 1)
			continue ;
		// print_env_list(&data.env);
		catloop(&data);
		if (g_sig_nb == 130)
		{
			data.exit = 130;
			g_sig_nb = 0;
		}
		free_all(&data);
	}
	free_all_env(&data);
}

void	init_tdata(int argc, char **argv, char **envp, t_data *data)
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
	data->nb_heredoc = 0;
}

void	catloop(t_data *data)
{
	if (data->line)
	{
		if (dollarcheck(data) == 1)
			return ;
		if (data->cmd_list->args[0] && ft_strcmp(data->cmd_list->args[0],
				"exit") == 0)
		{
			exit_function(data, data->line);
		}
		data->pipeinfo = initialize_pipeinfo(data->token_list);
		handle_all_heredocs(data);
		if (data->pipeinfo.number_of_pipes > 0)
		{
			handle_pipe(data, data->cmd_list, data->pipeinfo);
		}
		else if (data->pipeinfo.number_of_pipes == 0)
			handle_redirect_or_execute(data, data->cmd_list);
	}
}

int	init_loop(t_data *data)
{
	if (data->new_env)
		free_matrix(data->new_env);
	data->new_env = env_to_array(data->env);
	data->token_list = tokenize(data->line, data);
	if (!data->token_list)
	{
		free(data->line);
		return (1);
	}
	if (check_syntax(data))
	{
		free_tokens(&data->token_list);
		free(data->line);
		return (1);
	}
	data->nb_heredoc = get_here_nb(data->token_list);
	data->cmd_list = create_cmd_list(data->token_list);
	if (!data->cmd_list)
	{
		printf("Parsing failed!\n");
		free(data->line);
		free_tokens(&data->token_list);
		return (0);
	}
	return (0);
}
