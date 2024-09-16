/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:27:51 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/16 16:54:23 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (void)
{
	char *argv[100];
    int argc;
	while (1)
	{
		char *input;
		input = prompt();

		argc = 0;
		char **tokens = ft_split(input, ' ');
        while (tokens[argc] != NULL)
        {
            argv[argc] = tokens[argc];
            argc++;
        }
        argv[argc] = NULL;
		if (argc > 0)
		{
			if(ft_strncmp(argv[0], "echo", ft_strlen(argv[0])) == 0)
				echo(argv);
			else if(ft_strncmp(argv[0], "exit", ft_strlen(argv[0])) == 0)
			{
				free(input);
                free_tokens(tokens);
				break;
			}
			else if(ft_strncmp(argv[0], "punch", ft_strlen(argv[0])) == 0)
				printf("ow that hurt you bitch. piece of shit\n");
		}
		
		free(input);
        free_tokens(tokens);
	}
}	


void free_tokens(char **tokens)
{
    int i = 0;
    while (tokens[i] != NULL)
    {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}
	
	// char *command;
	// input = NULL;
		// command = prompt(input);


	// free(input);