/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:59:47 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/04 17:36:27 by tursescu         ###   ########.fr       */
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
    char *line;
	
	cmd_list = NULL;
	token_list = NULL;
    while (1)
    {
		line = readline("minishell> ");
		if (strcmp(line, "env") == 0)
		{
			ft_env(envp);
			continue;
		}
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
			print_token_list(token_list);
			cmd_list = create_cmd_list(token_list);
		}
		if (!cmd_list)
		{
			printf("Parsing failed!\n");
			free(line);
			free_tokens(&token_list);
			return (0);
		}
		else
			print_cmd_list(cmd_list);
		free_all(cmd_list, token_list);
		free(line);
    }
	return (0);
}