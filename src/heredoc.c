/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:00:39 by ckonneck          #+#    #+#             */
/*   Updated: 2025/03/21 10:20:29 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	heredoc(char *tempfile, t_token *redtemp)
{
	int	temp_fd;

	temp_fd = 0;
	temp_fd = open(tempfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp_fd == -1)
	{
		free(tempfile);
		return ;
	}
	if (heredoc_loop(temp_fd, redtemp->value) == 1)
	{
		free(tempfile);
		return ;
	}
	close(temp_fd);
}

int	heredoc_loop(int temp_fd, char *red_args)
{
	char	*input;

	input = NULL;
	signal(SIGINT, killchild);
	while (1)
	{
		input = readline(">");
		if (!input)
		{
			perror("heredoc error\n");
			close(temp_fd);
			return (1);
		}
		if (checkheredoc(input, temp_fd, red_args) == 0)
			break ;
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

void	handle_all_heredocs(t_data *data)
{
	t_cmd	*temp;
	t_token	*redtemp;
	int		heredoc_num;

	heredoc_num = 0;
	temp = data->cmd_list;
	while (temp)
	{
		redtemp = temp->redirections;
		while (redtemp)
		{
			if (redtemp->type == T_HEREDOC)
			{
				handle_heredocpre(data, heredoc_num, redtemp);
				heredoc_num++;
			}
			redtemp = redtemp->next;
		}
		temp = temp->next;
	}
}

void	handle_heredocpre(t_data *data, int heredoc_num, t_token *redtemp)
{
	int		pid;
	char	*tempfile;
	char	*num;

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
