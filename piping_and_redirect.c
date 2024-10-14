/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_and_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:48:50 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/14 16:35:11 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

void	handle_pipe(t_cmd *cmd_list, int number_of_pipes, char **envp, int prev_fd, int prev_pid)
{
	int pipefd[2];
	int i;
	int saved_stdin;
	int saved_stdout;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	i = 0;
	if (number_of_pipes > 0)
		pipe(pipefd);
	prev_pid = fork();
	if (prev_pid == 0)
		child_function(pipefd, cmd_list, envp, prev_fd);
	else
    {
		parent_function(pipefd, cmd_list, &prev_fd);
		// waitpid(prev_pid, NULL, 0);
	}
	if (number_of_pipes == 0)
	{
		// printf("prev fd: %i\n", prev_pid);
		// waitpid(prev_fd, NULL, 0);
		restore_fds(saved_stdin, saved_stdout);
		return;
	}
		// printf("WE GOING DOWN BOIS\n");
	handle_pipe(cmd_list->next, number_of_pipes -1, envp, prev_fd, prev_pid);
	waitpid(prev_pid, NULL, 0);
}

void	check_next(int pipefd[2], t_cmd *cmd_list)
{
	if (cmd_list->next)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(1);
		}
	}
}

void	child_function(int *pipefd, t_cmd *cmd_list, char **envp, int prev_fd)// need to handle this better, if i handle shit first i forgor the pipes, if last my output gets eaten
{
	
	if (prev_fd != -1)
	{
		// printf("big reveal\n");
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd_list->next)
	{
		// printf("tit\n");
		close(pipefd[0]); 
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		// close(pipefd[0]);
	}
	// execute_path(cmd_list, envp);
	// printf("executing\n");
	handle_redirect_or_execute(cmd_list, envp);
	exit(0);
}

void	parent_function(int *pipefd, t_cmd *cmd_list, int *prev_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd_list->next)
	{
		// printf("tit2\n");
		close(pipefd[1]); 
		*prev_fd = pipefd[0];
	}
	else
	{
		//  printf("suffer\n");
    	close(pipefd[0]);
		close(pipefd[1]);
	}

	// handle_redirect_or_execute(cmd_list, envp);
    
}
// void	last_pipe(t_cmd *cmd_list, char **envp, int saved_stdin, int saved_stdout)
// {
// 	// execute_path(cmd_list, envp);
// 	// handle_redirect_or_execute(cmd_list, envp);
// 	dup2(saved_stdin, STDIN_FILENO);   
// 	dup2(saved_stdout, STDOUT_FILENO);
// 	close(saved_stdin);
// 	close(saved_stdout);
// }
void	pipe_end_function(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}