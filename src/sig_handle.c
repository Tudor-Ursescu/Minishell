/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:59:37 by tursescu          #+#    #+#             */
/*   Updated: 2025/03/21 10:20:56 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include <errno.h>

int		g_sig_nb = 0;

void	sig_handle(int sig_nb)
{
	if (sig_nb == SIGCHLD)
	{
		g_sig_nb = SIGCHLD;
	}
	else if (sig_nb == SIGINT)
	{
		write(1, "\n", 1);
		g_sig_nb = 130;
		wait(NULL);
		if (g_sig_nb == SIGCHLD)
		{
			g_sig_nb = 130;
			return ;
		}
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_init(void)
{
	struct sigaction	sa;

	sa.sa_handler = sig_handle;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGCHLD, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	waitandsave(int pid, t_data *data)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		data->exit = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
		data->exit = 128 + WTERMSIG(status);
}

void	killchild(int sig_nb)
{
	if (sig_nb == SIGINT)
	{
		g_sig_nb = SIGINT;
		exit(130);
	}
}
