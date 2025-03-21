/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:57:44 by tursescu          #+#    #+#             */
/*   Updated: 2025/03/21 10:20:03 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	u_a_env(t_env **env_list, t_env *var, char *name, char *value)
{
	t_env	*new_var;
	char	*new_value;
	char	*temp;

	new_value = ft_strjoin(name, "=");
	temp = new_value;
	new_value = ft_strjoin(new_value, value);
	free(temp);
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

void	ft_export(t_env **env_list, char *name, char *value, t_data *data)
{
	t_env	*var;

	if (!is_valid_identifier(name))
	{
		printf("export: `%s=%s': not a valid identifier\n", name, value);
		data->exit = 1;
		return ;
	}
	var = find_env_var(*env_list, name);
	if (value == NULL)
	{
		if (var)
			return ;
		var = create_env(name);
		append_env(env_list, var);
		return ;
	}
	u_a_env(env_list, var, name, value);
}

int	comapre_env_var(t_env *temp, char *name)
{
	char	*equal_sign;
	int		var_name_len;
	int		len;

	len = ft_strlen(name);
	equal_sign = ft_strchr(temp->value, '=');
	if (equal_sign)
		var_name_len = equal_sign - temp->value;
	else
		var_name_len = ft_strlen(temp->value);
	if (ft_strncmp(temp->value, name, len) == 0 && var_name_len == len)
		return (1);
	return (0);
}

void	ft_unset(t_env **env_list, char *name)
{
	t_env	*temp;
	t_env	*prev;

	temp = *env_list;
	prev = NULL;
	while (temp)
	{
		if (comapre_env_var(temp, name))
		{
			if (prev)
				prev->next = temp->next;
			else
				*env_list = temp->next;
			free(temp->value);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}
