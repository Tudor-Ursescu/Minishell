/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:00:46 by tursescu          #+#    #+#             */
/*   Updated: 2025/03/21 10:19:57 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	count_env_vars(t_env *env_list)
{
	t_env	*current;
	int		count;

	current = env_list;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**copy_env_vars(t_env *env_list, int count)
{
	t_env	*current;
	char	**new_env;
	int		i;

	current = env_list;
	i = 0;
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	while (current)
	{
		new_env[i] = ft_strdup(current->value);
		if (!new_env[i])
		{
			while (i > 0)
				free(new_env[--i]);
			free(new_env);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

t_env	*find_last_env(t_env *head)
{
	t_env	*temp;

	temp = head;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

int	is_valid_identifier(char *name)
{
	int	i;

	if (!(ft_isalpha(name[0]) || name[0] == '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!(ft_isalnum(name[i]) || name[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

t_env	*find_env_var(t_env *env_list, char *name)
{
	t_env	*temp;
	int		len;

	temp = env_list;
	len = ft_strlen(name);
	while (temp)
	{
		if (ft_strncmp(temp->value, name, len) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}
