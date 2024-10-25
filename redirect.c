/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:54:23 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/25 18:09:48 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	handle_redirect_or_execute(t_data *data, t_cmd *cmd_list)
{
	int		fd;
	int		saved_stdin;
	int		saved_stdout;
	int		flag;

	flag = 0;
	fd = 0;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (handle_all_but_heredoc(cmd_list, fd) == 1)
		return ;

	execute_path(cmd_list, data);
	restore_fds(saved_stdin, saved_stdout);
	// unlink("tempfile.txt");gotta unlink all of them
}

int	handle_all_but_heredoc(t_cmd *cmd_list, int fd)
{
	char	*file;
	t_token *temp;
	temp = cmd_list->redirections;
	while (temp)
	{
		file = ft_strdup(temp->value);
		if (temp->type == T_APPEND
			|| temp->type == T_OUT)
			handle_append_and_out(cmd_list, fd);
		else if (temp->type == T_IN 
			|| temp->type == T_HEREDOC)
		{
			if (handle_input_redirection(fd, file) == 1)
			{
				free(file);
				return (1);
			}
		}
		temp = temp->next;
		free(file);
	}
	return (0);
}

void	handle_heredocpre(t_cmd *cmd_list, t_data *data, int heredoc_num)
{
	int	pid;
	char *tempfile;
	char *num;
	num = ft_itoa(heredoc_num);
	tempfile = ft_strjoin("tempfile", num);
	free(num);
	pid = fork();
	if (pid == 0)
	{
		heredoc(tempfile, cmd_list);
		exit(0);
	}
	else
	{
		waitandsave(pid, data);
		free(cmd_list->redirections->value);
		cmd_list->redirections->value = ft_strdup(tempfile);
		free(tempfile);
	}
}

int	handle_input_redirection(int fd, char *file)
{
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
