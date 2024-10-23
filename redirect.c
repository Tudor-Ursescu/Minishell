/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:54:23 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/23 17:55:04 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	handle_redirect_or_execute(t_data *data, t_cmd *cmd_list)
{
	int		fd;
	int		saved_stdin;
	int		saved_stdout;
	int		flag;
	t_token	*temp;

	flag = 0;
	fd = 0;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	temp = cmd_list->redirections;
	while (cmd_list->redirections)
	{
		if (cmd_list->redirections->type == T_HEREDOC)
			flag = handle_heredocpre(cmd_list, flag, fd, data);
		cmd_list->redirections = cmd_list->redirections->next;
	}
	cmd_list->redirections = temp;
	if (handle_all_but_heredoc(cmd_list, fd, flag) == 1)
		return ;
	execute_path(cmd_list, data);
	restore_fds(saved_stdin, saved_stdout);
	free_tokens(&temp);
	unlink("tempfile.txt");
}

int	handle_all_but_heredoc(t_cmd *cmd_list, int fd, int flag)
{
	char	*file;

	while (cmd_list->redirections)
	{
		file = cmd_list->redirections->value;
		if (cmd_list->redirections->type == T_APPEND
			|| cmd_list->redirections->type == T_OUT)
			handle_append_and_out(cmd_list, fd);
		else if (cmd_list->redirections->type == T_IN)
		{
			if (handle_input_redirection(flag, fd, file) == 1)
				return (1);
		}
		cmd_list->redirections = cmd_list->redirections->next;
	}
	return (0);
}

int	handle_heredocpre(t_cmd *cmd_list, int flag, int fd, t_data *data)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		heredoc(cmd_list->redirections->value);
		exit(0);
	}
	else
	{
		waitandsave(pid, data);
		flag = 1;
		free(cmd_list->redirections->value);
		cmd_list->redirections->value = ft_strdup("tempfile.txt");
		fd = open("tempfile.txt", O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		return (flag);
	}
}

int	handle_input_redirection(int flag, int fd, char *file)
{
	if (flag == 1)
		file = "tempfile.txt";
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("fd error");
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

void	handle_append_and_out(t_cmd *cmd_list, int fd)
{
	if (cmd_list->redirections->type == T_OUT)
		fd = open(cmd_list->redirections->value, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	else
		fd = open(cmd_list->redirections->value, O_WRONLY | O_CREAT | O_APPEND,
				0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
