/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:00:39 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/25 18:14:19 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	killchild(int sig_nb)
{
	if (sig_nb == SIGINT)
	{
		g_sig_nb  = SIGINT;
		exit(130);
	}
}

void	heredoc(char *tempfile, t_cmd *cmd_list)
{
	int	temp_fd;
	temp_fd = 0;
	temp_fd = open(tempfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp_fd == -1)
	{
		free(tempfile);
		return ;
	}
	if (heredoc_loop(temp_fd, cmd_list->redirections->value) == 1)
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
