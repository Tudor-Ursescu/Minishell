/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:21:18 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/24 12:06:40 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_function(char **argv, char **envp)
{
	char	*equal_sign;
	char	*var;
	char	*value;

	if (argv[1] == NULL)
		exportnullarg(envp);
	else if (argv[1])
	{
		if (ft_strchr(argv[1], '='))
		{
			equal_sign = ft_strchr(argv[1], '=');
			*equal_sign = '\0';
			var = argv[1];
			value = equal_sign + 1;
			set_env_variable(var, value, envp);
		}
		else
		{
			set_env_variable(argv[1], "", envp);
		}
	}
}

void	set_env_variable(const char *var, const char *value, char **envp)
{
	int		i;
	char	*new_var;
	int		var_len;
	int		value_len;

	i = 0;
	var_len = ft_strlen(var);
	value_len = ft_strlen(value);
	new_var = malloc(var_len + value_len + 2);
	if (!new_var)
		return ;
	ft_strlcpy(new_var, var, var_len + 1);
	ft_strlcat(new_var, "=", var_len + 2);
	ft_strlcat(new_var, value, var_len + value_len + 2);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, var_len) == 0 && envp[i][var_len] == '=')
		{
			free(envp[i]);
			envp[i] = new_var;
			return ;
		}
		i++;
	}
	envp[i] = new_var;
	envp[i + 1] = NULL;
}

void	sort_env(char **env)
{
	int		count;
	int		swapped;
	int		i;
	char	*temp;

	count = 0;
	while (env[count] != NULL)
		count++;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < count - 1)
		{
			if (ft_strncmp(env[i], env[i + 1], ft_strlen(env[i])) > 0)
			{
				temp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = temp;
				swapped = 1;
			}
			i++;
		}
	}
}

void	exportnullarg(char **envp)
{
	char	**env_ptr;

	env_ptr = copy_env(envp);
	sort_env(env_ptr);
	while (*env_ptr)
	{
		printf("declare -x %s\n", *env_ptr);
		env_ptr++;
	}
}

char	**copy_env(char **env)
{
	int		i;
	int		count;
	char	**env_copy;

	i = 0;
	count = 0;
	while (env[count])
		count++;
	env_copy = (char **)malloc((count + 1) * sizeof(char *));
	if (!env_copy)
		return (NULL);
	while (i < count)
	{
		env_copy[i] = (char *)malloc(ft_strlen(env[i]) + 1);
		if (!env_copy[i])
		{
			while (i > 0)
				free(env_copy[--i]);
			free(env_copy);
			return (NULL);
		}
		ft_strlcpy(env_copy[i], env[i], ft_strlen(env[i]) + 1);
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}
