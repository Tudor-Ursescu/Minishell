/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:27:51 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/21 11:42:46 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

int g_exit = 0;
int	main(int argc, char **argv, char **envp)
{
	t_data data;

	(void)argv;
	t_token *token_list;
	t_cmd	*cmd_list;
	t_pipeinfo pipeinfo;
	char		*line;
	cmd_list = NULL;
	token_list = NULL;
	line = NULL;
	printf("\033[H\033[J");
	signal_init();
	data.env = init_env_list(envp);
	while (1)
	{
		line = prompt();
		token_list = tokenize(line);
		if (!token_list)
		{
			free(line);
			continue;
		}	
		if (check_syntax(token_list))
		{
			free_tokens(&token_list);
			free(line);
			continue;
		}
		cmd_list = create_cmd_list(token_list);
		if (!cmd_list)
		{
			printf("Parsing failed!\n");
			free(line);
			free_tokens(&token_list);
			return (0);
		}
		argc = 0;
		while (cmd_list->args[argc])
			argc++;
		if (argc > 0)
		{	
			if (ft_strncmp(line, "$?", ft_strlen("$?")) == 0)
				printf("%d ", g_exit);
			if (ft_strncmp(line, "exit", ft_strlen("exit")) == 0)
			{
				exit_function(cmd_list->args, line);
			}
			pipeinfo = initialize_pipeinfo(token_list);
			if (pipeinfo.number_of_pipes > 0)
			{
				handle_pipe(cmd_list, envp, pipeinfo);
			}
			else if (pipeinfo.number_of_pipes == 0)
				handle_redirect_or_execute(cmd_list, envp);
		}
		free_all(cmd_list, token_list);
		free(line);
	}
	free_env(&data.env);
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

void    exit_function(char **argv, char *input)
{
    printf("GOODBYE NYA\n");
    free_call(argv, input);
    exit(0);
}

void restore_fds(int saved_stdin, int saved_stdout)
{
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
}


