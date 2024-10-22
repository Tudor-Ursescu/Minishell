/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:44:25 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/22 11:59:58 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_env   *copy_env_list(t_env *env_list)
{
    t_env   *new_list;
    t_env   *new_node;
    t_env   *temp;

    new_list = NULL;
    temp = env_list;
    while (temp)
    {
        new_node = create_env(temp->value);// maybe leaks
        append_env(&new_list, new_node);
        temp = temp->next;
    }
	return (new_list);
}

void	sort_env_list(t_env *env_list)
{
	t_env	*i;
	t_env	*j;
	char	*temp;
	
	if (!env_list)
		return;
	i = env_list;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (ft_strcmp(i->value, j->value) > 0)
			{
				temp = i->value;
				i->value = j->value;
				j->value = temp;
			}
			j = j->next;
		}
		i = i->next;
	}
}

void	handle_export(t_env **env_list, t_token *tokens)
{
	t_token	*token;
	char	*name;
	char	*value;
	int		i;
	tokens = tokens->next;
	if (!tokens)
	{
		t_env	*sorted_list;
		sorted_list = copy_env_list(*env_list);
		sort_env_list(sorted_list);
		print_sorted_env(sorted_list);
		free_env(&sorted_list);
		return;
	}
	tokens = merge_tokens(tokens);
	token = tokens;
	while (token)
	{
		name = NULL;
		value = NULL;
		if (token->type <= 2)
		{
			i = 0;
			while (token ->value[i] && token->value[i] != '=')
				i++;
			if (token->value[i] == '=')
			{
				name = ft_strndup(token->value, i);
				value = ft_strdup(&token->value[i + 1]);
			}
			else
				name = ft_strdup(token->value);
			ft_export(env_list, name, value);
			free(name);
			if (value)
				free(value);
		}
		token = token->next;
	}
}

void	handle_unset(t_env **env_list, t_token *tokens)
{
	t_token *token;

	token = tokens;
	while (token)
	{
		if (token->type <= 2)
			ft_unset(env_list, token->value);
		token = token->next;
	}
}

void	handle_env_tudor(t_env **env_list, t_token *tokens)
{
	if (!tokens || !tokens->next)
		print_env_list(env_list);
	else
		printf("Syntax error: 'env' does not accept arguments.\n");
}

t_token	*merge_tokens(t_token *tokens)
{
	t_token *current;
	t_token	*next_token;
	char	*new_value;

	current = tokens;
	while (current && current->next)
	{
		if (current->append)
		{
			while (current->next)
			{
				new_value = ft_strjoin(current->value, current->next->value);
				free(current->value);
				current->value = new_value;
				next_token = current->next;
				if (next_token->append == 0)
				{
					current->next = next_token->next;	
					free(next_token->value);
					free(next_token);
					break;
				}
				else
				{
					current->next = next_token->next;
					free(next_token->value);
					free(next_token);	
				}
			}
		}
		current = current->next;
	}
	return (tokens);
}
