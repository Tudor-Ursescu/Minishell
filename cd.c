/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:12:18 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/04 13:35:56 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	lstatcheck(char **argv)
{
	if (errno == ENOENT)
		printf("cd: no such file or directory: %s\n", argv[1]);
	else if (errno == EACCES)
		printf("cd: permission denied: %s\n", argv[1]);
	else
		perror("cd"); // Catch-all for other errors
}

void	cd_function(char **argv, char **envp)
{
	struct stat	statbuf;
	(void)envp;
	char *home_dir;

	if (!argv[1])
	{
		home_dir = getenv("HOME");
		if (chdir(home_dir) != 0)
			perror("cd");
		return ;
	}
	if (lstat(argv[1], &statbuf) != 0)
	{
		lstatcheck(argv);
		return ;
	}
	if (!S_ISDIR(statbuf.st_mode))
	{
		printf("cd: not a directory: %s\n", argv[1]);
		return ;
	}
	if (chdir(argv[1]) != 0)
	{
		if (errno == EACCES)
			printf("cd: permission denied: %s\n", argv[1]);
		else
			perror("cd");
	}
}

void	pwd_function(char **argv, char **envp)
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
	}
	else
	{
		printf("pwd: too many arguments\n");
		// exit code 1
	}
}
