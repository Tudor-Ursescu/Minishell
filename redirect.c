/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:00:39 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/25 16:45:55 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_redirect(char **argv, char **envp) //<
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
		fd = open(argv[2], O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		argv[1] = NULL;
		path = find_path(argv[0]);
		if (execve(path, argv, envp) == -1)
		{
			perror("execve failed");
			exit(1);
		}
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		perror("fork");
}

void	output_redirect(char **argv, char **envp) //>
{
	int fd;
	int pid;
	char *path;
	pid = fork();
	if (pid == 0)
	{
		fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		argv[1] = NULL;
		path = find_path(argv[0]);
		if (execve(path, argv, envp) == -1)
		{
			perror("execve failed");
			exit(1);
		}
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0); // Parent waits for child
	else
		perror("SPOON");
}

void	heredoc(char **argv, char **envp) //<<
{
	char *input = NULL;
	int temp_fd;

	temp_fd = open("tempfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		input = get_next_line(STDIN_FILENO);
		if (!input)
		{
			perror("get_next_line");
			break ;
		}
		if (ft_strncmp(input, argv[2], strlen(argv[2])) == 0
			&& (input[strlen(argv[2])] == '\n'
				|| input[strlen(argv[2])] == '\0'))
		{
			free(input);
			close(temp_fd);
			argv[1] = NULL;
			free(argv[2]);
			argv[2] = "tempfile.txt";
			break ;
		}
		write(temp_fd, input, ft_strlen(input));
		free(input);
	}
	close(temp_fd);
	input_redirect(argv, envp);
	unlink("tempfile.txt");
}

void	output_append(char **argv, char **envp) // >>
{
	int fd;
	int pid;
	char *path;
	pid = fork();
	if (pid == 0)
	{
		fd = open(argv[2], O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		argv[1] = NULL;
		path = find_path(argv[0]);
		if (execve(path, argv, envp) == -1)
		{
			perror("execve failed");
			exit(1);
		}
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0); // Parent waits for child
	else
		perror("SPork");
}