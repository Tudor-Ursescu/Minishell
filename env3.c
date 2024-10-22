/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:44:25 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/22 19:34:20 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	handle_unset(t_env **env_list, t_token *tokens, t_data *data)
{
	t_token	*token;

	data->exit = 0;
	token = tokens;
	while (token)
	{
		if (token->type <= 2)
			ft_unset(env_list, token->value);
		token = token->next;
	}
}

void	handle_env_tudor(t_env **env_list, t_token *tokens, t_data *data)
{
	if (!tokens || !tokens->next)
	{
		print_env_list(env_list);
		data->exit = 0;
	}
	else
	{
		printf("Syntax error: 'env' does not accept arguments.\n");
		data->exit = 1;
	}
}

t_token	*merge_next_token(t_token *current)
{
	t_token	*next_token;
	char	*new_value;

	while (current->next)
	{
		new_value = ft_strjoin(current->value, current->next->value);
		free(current->value);
		current->value = new_value;
		next_token = current->next;
		current->next = next_token->next;
		free(next_token->value);
		free(next_token);
		if (next_token->append == 0)
			break ;
	}
	return (current);
}

t_token	*merge_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current && current->next)
	{
		if (current->append)
			current = merge_next_token(current);
		current = current->next;
	}
	return (tokens);
}
