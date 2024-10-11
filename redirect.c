/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:00:39 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/11 15:35:57 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	input_redirect(char **argv, char **envp, char *red_args) //<
{
	// we go by the assumption that by the time this function is called,
	// it has been determined that there is a < in the arguments,
	//	same for the following functions in this file
	// filename = whatever we get out of this. tudorparse.exe
	// ALSO THIS WILL NEVER TRIGGER IF ARGV0 IS NOT A COMMAND!!!!
	int fd;
	int pid;
	char *path;
	pid = fork();
	if (pid == 0)
	{
		fd = open(red_args, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		path = find_path(argv[0]);
		if (execve(path, argv, envp) == -1)
		{
			perror("execve failed");
			exit(127);
		}
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		perror("fork");
}

void	output_redirect(char **argv, char **envp, char *red_args) //>
{
	int fd;
	int pid;
	char *path;
	pid = fork();
	if (pid == 0)
	{
		fd = open(red_args, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		path = find_path(argv[0]);
		if (execve(path, argv, envp) == -1)
		{
			perror("execve failed");
			exit(127);
		}
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		perror("SPOON");
}
//BIG FYI In terms of shell redirection, the first argument after <, >, or >> is strictly 
//interpreted as a file. If it is not a file, the shell will either fail or behave unexpectedly.
void	heredoc(char **argv, char **envp, char *red_args) // <<
{
	char *input = NULL;
	int temp_fd;
	(void)argv;
	(void)envp;
	temp_fd = open("tempfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		input = readline(">");
		
		// printf("input: %s", input);
		if (!input)
		{
			perror("somethignnotgood\n");
			close(temp_fd);
			return ;
		}
		if (checkheredoc(input, temp_fd, red_args) == 0)
		{
			break;
		}
		write(temp_fd, input, ft_strlen(input));
		write(temp_fd, "\n", 1);
		free(input);
	}
	close(temp_fd);
	// unlink("tempfile.txt"); // need to ahndle this somewhere
}


int	checkheredoc(char *input, int temp_fd, char *red_args)
{

	if (ft_strncmp(input, red_args, strlen(red_args)) == 0
		&& (input[ft_strlen(red_args)] == '\n' || input[ft_strlen(red_args)] == '\0'))
	{
		free(input);
		close(temp_fd);
		return(0);
	}
	return (1);
}
void	output_append(char **argv, char **envp, char *red_args) // >>
{
	int fd;
	int pid;
	char *path;
	pid = fork();
	if (pid == 0)
	{
		printf("red_args[0]%s\n", red_args);
		fd = open(red_args, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		path = find_path(argv[0]);
		if (execve(path, argv, envp) == -1)
		{
			perror("execve failed");
			exit(127);
		}
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		perror("SPork");
}