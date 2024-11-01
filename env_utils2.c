/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:47:12 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/23 18:39:26 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	handle_export_no_args(t_env **env_list)
{
	t_env	*sorted_list;

	sorted_list = copy_env_list(*env_list);
	sort_env_list(sorted_list);
	print_sorted_env(sorted_list);
	free_env(&sorted_list);
}

void	extr_name_value(t_token *token, char **name, char **value)
{
	int	i;

	i = 0;
	while (token->value[i] && token->value[i] != '=')
		i++;
	if (token->value[i] == '=')
	{
		*name = ft_strndup(token->value, i);
		*value = ft_strdup(&token->value[i + 1]);
	}
	else
	{
		*name = ft_strdup(token->value);
		*value = NULL;
	}
}

void	prcs_token(t_env **env_list, t_token *token, t_data *data)
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	extr_name_value(token, &name, &value);
	ft_export(env_list, name, value, data);
	free(name);
	if (value)
		free(value);
}

t_env	*copy_env_list(t_env *env_list)
{
	t_env	*new_list;
	t_env	*new_node;
	t_env	*temp;

	new_list = NULL;
	temp = env_list;
	while (temp)
	{
		new_node = create_env(temp->value);
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
		return ;
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
