/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:48:50 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/22 10:02:04 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

void	handle_pipe(t_data *data, t_cmd *cmd_list, t_pipeinfo pipeinfo)
{
	int	pipefd[2];
	int	saved_stdin;
	int	saved_stdout;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (pipeinfo.number_of_pipes >= 0)
		pipe(pipefd);
	pipeinfo.prev_pid = fork();
	if (pipeinfo.prev_pid == 0)
		child_function(pipefd, data, cmd_list, pipeinfo.prev_fd);
	else
		parent_function(pipefd, cmd_list, &pipeinfo.prev_fd);
	if (pipeinfo.number_of_pipes == 0)
	{
		restore_fds(saved_stdin, saved_stdout);
		return ;
	}
	pipeinfo.number_of_pipes--;
	handle_pipe(data, cmd_list->next, pipeinfo);
	waitandsave(pipeinfo.prev_pid, data);
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

void	child_function(int *pipefd, t_data *data, t_cmd *cmd_list, int prev_fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd_list->next)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	handle_redirect_or_execute(data, cmd_list);
	if (find_path(cmd_list->args[0]) != NULL)
		exit(0);
	else
		exit(127);
}

void	parent_function(int *pipefd, t_cmd *cmd_list, int *prev_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd_list->next)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
	else
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

t_pipeinfo	initialize_pipeinfo(t_token *token_list)
{
	t_pipeinfo	pipeinfo;
	t_token		*temp;

	temp = token_list;
	pipeinfo.number_of_pipes = 0;
	while (temp)
	{
		if (temp->type == T_PIPE)
			pipeinfo.number_of_pipes++;
		temp = temp->next;
	}
	free(temp);
	pipeinfo.prev_fd = -1;
	pipeinfo.prev_pid = -1;
	return (pipeinfo);
}
