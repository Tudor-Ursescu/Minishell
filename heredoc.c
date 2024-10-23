/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:00:39 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/23 15:48:28 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	heredoc(char *red_args)
{
	int	temp_fd;
	int	saved_stdin;
	int	saved_stdout;

	temp_fd = 0;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	dup2(temp_fd, 1);
	temp_fd = open("tempfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_loop(temp_fd, saved_stdin, saved_stdout, red_args) == 1)
		return ;
	close(temp_fd);
}

int	heredoc_loop(int temp_fd, int saved_stdin, int saved_stdout, char *red_args)
{
	char	*input;

	input = NULL;
	
	while (1)
	{
		input = readline(">");
		if (!input)
		{
			perror("heredoc error\n");
			close(temp_fd);
			restore_fds(saved_stdin, saved_stdout);
			return (1);
		}
		if (checkheredoc(input, temp_fd, red_args) == 0)
		{
			restore_fds(saved_stdin, saved_stdout);
			break ;
		}
		write(temp_fd, input, ft_strlen(input));
		write(temp_fd, "\n", 1);
		free(input);
	}
	return (0);
}

int	checkheredoc(char *input, int temp_fd, char *red_args)
{
	if (ft_strncmp(input, red_args, ft_strlen(red_args)) == 0
		&& (input[ft_strlen(red_args)] == '\n'
			|| input[ft_strlen(red_args)] == '\0'))
	{
		free(input);
		close(temp_fd);
		return (0);
	}
	return (1);
}
