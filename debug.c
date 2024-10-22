/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:29:43 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/22 17:49:28 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_cmd_list(t_cmd *cmd_list)
{
	int		i;
	int		j;
	t_token	*redirections;

	while (cmd_list)
	{
		i = 1;
		j = 0;
		redirections = cmd_list->redirections;
		printf("Cmd: [%s]\n", cmd_list->args[0]);
		printf("Args: ");
		while (cmd_list->args != NULL && cmd_list->args[i] != NULL)
			printf("[%s]", cmd_list->args[i++]);
		printf("\nRedirections: ");
		while (redirections != NULL)
		{
			printf("Value:[%s]Type:[%d]\t", redirections->value,
				redirections->type);
			redirections = redirections->next;
		}
		printf("\n");
		cmd_list = cmd_list->next;
	}
}

void	print_token_list(t_token *head)
{
	t_token	*temp;

	temp = head;
	while (temp)
	{
		printf("Token:%s, Type:%d, Append:%d\n", temp->value, temp->type,
			temp->append);
		temp = temp->next;
	}
}

void	print_env_list(t_env **head)
{
	t_env	*temp;
	char	*equal_sign_pos;

	temp = *head;
	while (temp)
	{
		equal_sign_pos = ft_strchr(temp->value, '=');
		if (equal_sign_pos)
			printf("%s\n", temp->value);
		temp = temp->next;
	}
}

void	print_sorted_env(t_env *env_list)
{
	t_env	*temp;
	char	*equal_sign_pos;
	char	*name;
	char	*value;

	temp = env_list;
	while (temp)
	{
		equal_sign_pos = ft_strchr(temp->value, '=');
		if (equal_sign_pos)
		{
			name = ft_strndup(temp->value, equal_sign_pos - temp->value);
			value = ft_strdup(equal_sign_pos + 1);
			printf("declare -x %s=\"%s\"\n", name, value);
			free(name);
			free(value);
		}
		else
		{
			name = ft_strdup(temp->value);
			printf("declare -x %s\n", name);
			free(name);
		}
		temp = temp->next;
	}
}
