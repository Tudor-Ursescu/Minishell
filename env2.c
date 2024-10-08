/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:57:44 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/08 13:09:00 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_env	*find_env_var(t_env *env_list, char *name)
{
	t_env	*temp;
	int		len;
	
	temp = env_list;
	len = ft_strlen(name);
	while (temp)
	{
		if (ft_strncmp(temp->value, name, len) == 0 &&
			temp->value[len] == '=')
			return (temp);
		temp = temp-> next;
	}
	return (NULL);
}

void	ft_export(t_env **env_list, char *name, char *value)
{
	t_env	*var;
	t_env	*new_var;
	char	*new_value;
	char	*temp;
	
	new_value = ft_strjoin(name, "=");
	temp = new_value;
	new_value = ft_strjoin(new_value, value);
	free(temp);
	var = find_env_var(*env_list, name);
	if (var)
	{
		free(var->value);
		var->value = ft_strdup(new_value);
	}
	else
	{
		new_var = create_env(new_value);
		append_env(env_list, new_var);
	}
	free(new_value);
}

void	ft_unset(t_env **env_list, char *name)
{
	t_env	*temp;
	t_env	*prev;
	int		len;

	temp = *env_list;
	prev = NULL;
	len = ft_strlen(name);
	while(temp)
	{
		if (ft_strncmp(temp->value, name, len) == 0 &&
			temp->value[len] == '=')
		{
			if (prev)
				prev->next = temp->next;
			else
				*env_list = temp->next;
			free(temp->value);
			free(temp);
			return;
		}
		prev = temp;
		temp = temp->next;
	}
}

char *ft_getenv(t_env *env_list, char *name)
{
	t_env *var = find_env_var(env_list, name);
	if (var)
	{
		char *value = ft_strchr(var->value, '=') + 1;
		return (value);
	}
	return (NULL);
}
