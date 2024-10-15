/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:00:39 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/15 15:57:12 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//BIG FYI In terms of shell redirection, the first argument after <, >, or >> is strictly 
//interpreted as a file. If it is not a file, the shell will either fail or behave unexpectedly.
void	heredoc(char **argv, char **envp, char *red_args) // <<
{
	char *input = NULL;
	int temp_fd= 0;
	(void)argv;
	(void)envp;
	int saved_stdin = dup(STDIN_FILENO);
	int saved_stdout = dup(STDOUT_FILENO);
	dup2(temp_fd, 1);
	temp_fd = open("tempfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		input = readline(">");
		
		if (!input)
		{
			perror("somethignnotgood\n");
			close(temp_fd);
			return ;
		}
		if (checkheredoc(input, temp_fd, red_args) == 0)
		{	
			restore_fds(saved_stdin, saved_stdout);
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
