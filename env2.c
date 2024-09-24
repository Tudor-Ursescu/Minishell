/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:57:44 by tursescu          #+#    #+#             */
/*   Updated: 2024/09/24 15:24:01 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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