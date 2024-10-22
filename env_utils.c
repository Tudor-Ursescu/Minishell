/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:00:46 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/22 17:50:24 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**env_to_array(t_env *env_list)
{
	t_env *current;
	char **new_env;
	int i;
	int count;

	current = env_list;
	i = 0;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	current = env_list;
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

