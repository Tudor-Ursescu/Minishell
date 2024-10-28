/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:54:23 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/28 14:44:00 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	handle_redirect_or_execute(t_data *data, t_cmd *cmd_list)
{
	int		saved_stdin;
	int		saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (handle_all_redirections(cmd_list) == 1)
		return ;

	execute_path(cmd_list, data);
	restore_fds(saved_stdin, saved_stdout);
}

int handle_all_redirections(t_cmd *cmd_list)
{
	t_token *temp;
	char *file;

	temp = cmd_list->redirections;
	while (temp)
	{
		if (temp->type == T_IN || temp->type == T_HEREDOC)
		{
			file = ft_strdup(temp->value);
			if (handle_input_redirection(file) == 1)
			{
				free(file);
				return (1);
			}
			free(file);
		}
		temp = temp->next;
	}
	temp = cmd_list->redirections;
	output_redirections(temp, file);
	return (0);
}

void		output_redirections(t_token *temp, char *file)
{
	while (temp)
	{
		if (temp->type == T_APPEND || temp->type == T_OUT)
		{
			file = ft_strdup(temp->value);
			handle_append_and_out(temp->type, file);
			free(file);
		}
		temp = temp->next;
	}
}

int handle_input_redirection(char *file)
{
	int input_fd;

	input_fd = open(file, O_RDONLY);
	if (input_fd < 0)
	{
		perror("fd error");
		return (1);
	}
	dup2(input_fd, STDIN_FILENO);
	close(input_fd);
	return (0);
}

void handle_append_and_out(t_token_types type, char *file)
{
	int output_fd;

	if (type == T_OUT)
		output_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		output_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);

	if (output_fd < 0)
	{
		perror("fd error");
		return;
	}
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);
}

void	handle_heredocpre(t_data *data, int heredoc_num, t_token *redtemp)
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
		heredoc(tempfile, redtemp);
		exit(0);
	}
	else
	{
		waitandsave(pid, data);
		free(redtemp->value);
		redtemp->value = ft_strdup(tempfile);
		free(tempfile);
	}
}
