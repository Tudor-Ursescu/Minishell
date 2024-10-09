/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:59:47 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/09 14:37:27 by tursescu         ###   ########.fr       */
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
			// print_token_list(token_list);
			cmd_list = create_cmd_list(token_list);
		}
		if (!cmd_list)
		{
			free(line);
			free_tokens(&token_list);
			return (0);
		}
		if (cmd_list->args[0])
		{
			if (ft_strcmp(cmd_list->args[0], "export") == 0 && cmd_list->args[1])
			{
				char *name = NULL;
				char *value = NULL;
				int i = 0;
				while (cmd_list->args[1][i] && cmd_list->args[1][i] != '=')
					i++;
				if (cmd_list->args[1][i] == '=')
				{
					name = ft_strndup(cmd_list->args[1], i);
					value = ft_strdup(&cmd_list->args[1][i + 1]);
				}
				ft_export(&env_list, name, value);
				free(name);
				free(value);
			}
			else if (ft_strcmp(cmd_list->args[0], "export") == 0 && !cmd_list->args[1])
			{
				t_env	*sorted_list;
				sorted_list = copy_env_list(env_list);
				print_sorted_env(sorted_list);
				free_env(&sorted_list);
			}
			else if (ft_strcmp(cmd_list->args[0], "unset") == 0 && cmd_list->args[1])
				ft_unset(&env_list, cmd_list->args[1]);
			else if (ft_strcmp(cmd_list->args[0], "env") == 0)
				print_env_list(env_list);
		}
		print_cmd_list(cmd_list);
		free_all(cmd_list, token_list);
		free(line);
    }
	free_env(&env_list);
	return (0);
}