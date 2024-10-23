/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:12:18 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/23 14:15:12 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

void	cd_function(char **argv, char **envp, t_data *data)
{
	data->exit = 0;
	(void)envp;
	errno = 0;
	if (argv[0] && argv[1] && argv[2])
	{
		printf("cd: too many arguments\n");
		data->exit = 1;
		return ;
	}
	if (cd_function2(argv, data) == 1)
		return ;
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
}

int	cd_function2(char **argv, t_data *data)
{
	char		*home_dir;
	struct stat	statbuf;

	if (!argv[1])
	{
		home_dir = getenv("HOME");
		if (chdir(home_dir) != 0)
			perror("cd");
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

void	pwd_function(char **argv, char **envp, t_data *data)
{
	char	path[1024];
	int		argc;

	(void)envp;
	argc = 0;
	while (argv[argc])
		argc++;
	if (argc == 1)
	{
		getcwd(path, sizeof(path));
		printf("%s\n", path);
		data->exit = 0;
	}
	else
	{
		printf("pwd: too many arguments\n");
		data->exit = 1;
	}
}

int dollarcheck(t_data *data)
{
	if (ft_strncmp(data->line, "$?", ft_strlen("$?")) == 0)
		printf("%d: ", data->exit);
	check_and_print_exit(data);
	if (check_and_print_env(data) == 1)
		return (1);
	return(0);
}