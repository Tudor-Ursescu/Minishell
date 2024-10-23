/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:04:01 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/23 18:39:38 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_env	*create_env(char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void	append_env(t_env **list, t_env *new)
{
	t_env	*temp;

	if (*list)
	{
		temp = find_last_env(*list);
		temp->next = new;
		new->next = NULL;
	}
	else
	{
		*list = new;
		(*list)->next = NULL;
	}
}

t_env	*init_env_list(char **envp)
{
	int		i;
	t_env	*env_list;
	t_env	*new;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		new = create_env(envp[i]);
		append_env(&env_list, new);
		i++;
	}
	return (env_list);
}

char	**env_to_array(t_env *env_list)
{
	int	count;

	count = count_env_vars(env_list);
	if (count == 0)
		return (NULL);
	return (copy_env_vars(env_list, count));
}

void	handle_export(t_env **env_list, t_token *tokens, t_data *data)
{
	t_token	*token;

	tokens = tokens->next;
	if (!tokens)
	{
		handle_export_no_args(env_list);
		return ;
	}
	tokens = merge_tokens(tokens);
	token = tokens;
	while (token)
	{
		if (token->type <= 2)
			prcs_token(env_list, token, data);
		token = token->next;
	}
}
