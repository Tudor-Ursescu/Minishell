/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:12:18 by ckonneck          #+#    #+#             */
/*   Updated: 2025/03/21 10:23:45 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	lstatcheck(char **argv, t_data *data)
{
	if (errno == ENOENT)
	{
		printf("cd: no such files or directory: %s\n", argv[1]);
		data->exit = 1;
	}
	else if (errno == EACCES)
	{
		printf("cd: permission denied: %s\n", argv[1]);
		data->exit = 1;
	}
	else
	{
		data->exit = 1;
		perror("cd");
	}
}

int	cd_function(char **argv, char **envp, t_data *data)
{
	data->exit = 0;
	(void)envp;
	errno = 0;
	if (argv[0] && argv[1] && argv[2])
	{
		printf("cd: too many arguments\n");
		data->exit = 1;
		return (1);
	}
	if (cd_function2(argv, data) == 1)
		return (1);
	if (chdir(argv[1]) != 0)
	{
		if (errno == EACCES)
		{
			printf("cd: permission denied: %s\n", argv[1]);
			data->exit = 1;
		}
		else
			perror("cd");
	}
	return (0);
}

int	cd_function2(char **argv, t_data *data)
{
	char		*home_dir;
	struct stat	statbuf;
	t_env		*temp;

	home_dir = NULL;
	temp = find_env_var(data->env, "HOME");
	if (!argv[1])
	{
		cd_home(temp, home_dir);
		return (1);
	}
	if (lstat(argv[1], &statbuf) != 0)
	{
		lstatcheck(argv, data);
		return (1);
	}
	if (!S_ISDIR(statbuf.st_mode))
	{
		printf("cd: not a directory: %s\n", argv[1]);
		return (1);
	}
	return (0);
}

void	cd_home(t_env *temp, char *home_dir)
{
	if (temp != NULL)
		home_dir = ft_substr(temp->value, 5, (ft_strlen(temp->value) - 5));
	if (home_dir != NULL && (chdir(home_dir) != 0))
		perror("cd");
	else if (!home_dir)
		printf("cd: HOME not set\n");
	free(home_dir);
}

void	cd_function_wrap(char **argv, char **envp, t_data *data)
{
	char	path[1024];
	char	*currentpwd;
	char	*newpwd;
	t_env	*temp;
	char	*tmp;

	currentpwd = NULL;
	currentpwd = getcwd(path, sizeof(path));
	newpwd = NULL;
	if (cd_function(argv, envp, data) == 0)
	{
		temp = find_env_var(data->env, "OLDPWD");
		free(temp->value);
		temp->value = ft_strdup("OLDPWD=");
		tmp = temp->value;
		temp->value = ft_strjoin(temp->value, currentpwd);
		free(tmp);
		newpwd = getcwd(path, sizeof(path));
		temp = find_env_var(data->env, "PWD");
		free(temp->value);
		temp->value = ft_strdup("PWD=");
		tmp = temp->value;
		temp->value = ft_strjoin(temp->value, newpwd);
		free(tmp);
	}
}
