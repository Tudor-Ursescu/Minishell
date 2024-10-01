/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:59:47 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/01 16:15:22 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <string.h>

int main (void)
{
    t_token *token_list;
	t_cmd	*cmd_list;
    char *line;
	
	cmd_list = NULL;
	token_list = NULL;
    while (1)
    {
		line = readline("minishell> ");
		printf("%s\n", line);
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
			printf("Tokenization failed!\n");
			return (0);
		}
		else
			print_token_list(token_list);
		if (token_list)
			create_cmd_list(token_list);
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