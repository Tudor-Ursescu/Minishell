/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:27:51 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/08 11:23:06 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"
// int g_sig = 0;

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	t_token *token_list;
	t_cmd	*cmd_list;

	cmd_list = NULL;
	token_list = NULL;
	char		*line;
	t_firstcmd	*command_table;
	int			i;
	int			found;
	// g_sig = 0;
	command_table = init_command_table();
	line = NULL;
	setup_signal_handlers();
	while (1)
	{
		line = prompt();
		
		if (strcmp(line, "env") == 0)
		{
			ft_env(envp);
			continue;
		}
		token_list = tokenize(line);
		if (token_list == NULL)
		{
			if (line)
			{
				free(line);
				continue;
			}
			printf("Tokenization failed(no line inputted)!\n");
			free(line);
			continue;
		}
		else
		{
			// print_token_list(token_list); // DISABLED PRINT
			cmd_list = create_cmd_list(token_list);
		}
		if (!cmd_list)
		{
			printf("Parsing failed!\n");
			free(line);
			free_tokens(&token_list);
			return (0);
		}
		
		found = 0;
		int pipenumber = 0;
		argc = 0;
		while (cmd_list->args[argc])
			argc++;
		i = 0;
		if (argc > 0)
		{
			while (command_table[i].name != NULL)
			{
				if (ft_strncmp(cmd_list->args[0], command_table[i].name,
						ft_strlen(command_table[i].name)) == 0)
				{
					command_table[i].func(cmd_list->args, envp);
					found = 1;
					break ;
				}
				i++;
			}
			if (ft_strncmp(line, "exit", ft_strlen("exit")) == 0)
			{
				exit_function(command_table, cmd_list->args, line);
			}
			t_token *temp = token_list;
			while (temp)
			{
				if (temp->type == T_PIPE)
					pipenumber++;
				temp = temp->next;
			}
			free(temp);
			if (pipenumber > 0)
				handle_pipe(cmd_list, pipenumber, envp);
			else if (!found)
				handle_redirect_or_execute(cmd_list, envp);
		}
		free_all(cmd_list, token_list);
		free(line);
		// print_cmd_list(cmd_list);
		// free_call(argv, line);
	}
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
void    exit_function(t_firstcmd *command_table, char **argv, char *input)
{
    printf("GOODBYE NYA\n");
    free(command_table);
    free_call(argv, input);
    exit(0);
}

void	handle_redirect_or_execute(t_cmd *cmd_list, char **envp)
{
	if (!cmd_list->redirections)
	{
		execute_path(cmd_list, envp);
		return;
	}
	if (cmd_list->redirections->type == T_HEREDOC) // <<
	{
		printf("triggered T HEREDOC (<<)\n");
		heredoc(cmd_list->args, envp);
	}
	else if (cmd_list->redirections->type == T_APPEND) // >>
	{
		printf("triggered T APPEND (>>)\n");
		output_append(cmd_list->args, envp);
	}
	else if (cmd_list->redirections->type == T_IN) // <
	{
		printf("triggered T IN (<)\n");
		input_redirect(cmd_list->args, envp);
	}
	else if (cmd_list->redirections->type == T_OUT) //>
	{
		printf("triggered T OUT (>)\n");
		output_redirect(cmd_list->args, envp);
	}
}
