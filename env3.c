/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:44:25 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/08 12:08:50 by tursescu         ###   ########.fr       */
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