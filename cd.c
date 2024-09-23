/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:12:18 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/18 10:56:11 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lstatcheck(char **argv)
{
	if (errno == ENOENT)
		printf("cd: no such file or directory: %s\n", argv[1]);
	else if (errno == EACCES)
		printf("cd: permission denied: %s\n", argv[1]);
	else
		perror("cd"); // Catch-all for other errors
}

void	cd_function(char **argv)
{
	struct stat	statbuf;

	if (!argv[1])
	{
		if (chdir("/home") != 0)
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

void	pwd_function(char **argv)
{
	(void)argv;
	char	path[1024];
	
	getcwd(path, sizeof(path));
	printf("%s\n", path);
}

void	ls_function(char **argv)
{
	(void)argv;
	DIR				*dir;
	struct dirent	*entry;

	// Open the current directory
	dir = opendir(".");
	if (dir == NULL)
	{
		perror("opendir");
		return ;
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			printf("%s  ", entry->d_name);
		}
	}
	printf("\n");
	closedir(dir);
}
