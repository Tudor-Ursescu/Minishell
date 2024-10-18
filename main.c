/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:59:47 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/18 11:07:36 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <string.h>


int main (int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
    t_token *token_list;
	t_cmd	*cmd_list;
    char 	*line;
	t_env	*env_list;
	
	cmd_list = NULL;
	token_list = NULL;
	env_list = init_env_list(envp);
    while (1)
    {
		line = readline("minishell> ");
		if (line == NULL || strcmp(line, "exit") == 0)
		{
			free(line);
			break;
		}
		if(line[0] != '\0')
			add_history(line);
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
			free(line);
			free_tokens(&token_list);
			return (0);
		}
		if (cmd_list->args[0])
		{
			if (ft_strcmp(cmd_list->args[0], "export") == 0)
				handle_export(&env_list, token_list->next);
			else if (ft_strcmp(cmd_list->args[0], "unset") == 0)
				handle_unset(&env_list, token_list->next);
			else if (ft_strcmp(cmd_list->args[0], "env") == 0)
				handle_env_tudor(env_list, token_list->next);
		}
		free_all(cmd_list, token_list);
		free(line);
    }
	free_env(&env_list);
	return (0);
}
