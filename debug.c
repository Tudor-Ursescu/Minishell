/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:29:43 by tursescu          #+#    #+#             */
/*   Updated: 2024/09/30 17:33:03 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void    print_cmd_list(t_cmd *cmd_list)
{
    int     i;
    t_token *redirections;
    while (cmd_list)
    {
        i = 0;
        redirections = cmd_list->redirections;
        printf("Args: ");
        while (cmd_list->args != NULL && cmd_list->args[i] != NULL)
            printf("[%s]", cmd_list->args[i++]);
        printf("\nRedirections: ");
        while (redirections != NULL)
        {
            printf("[%s]", redirections->value);
            redirections = redirections->next;
        }
        printf("\n");
        cmd_list = cmd_list->next;
    }
}

void print_token_list(t_token *head)
{
	t_token *temp;

	temp = head;
	while (temp)
	{
		printf("Token:%s, Type:%d\n", temp->value, temp->type);
		temp = temp->next;
	}
}

void print_env_list(t_env *head)
{
    t_env *temp;

    temp = head;
    while (temp)
    {
        printf("%s\n", temp->value);
        temp = temp->next;
    }
}
