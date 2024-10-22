/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:59:37 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/22 14:44:03 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <errno.h>
int		g_sig_nb = 0;
t_data *g_data = NULL;

void	sig_handle(int sig_nb)
{
	if (sig_nb == SIGCHLD)
	{
		while (wait(NULL) > 0);
		g_sig_nb = SIGCHLD;
	}
	else if(sig_nb == SIGINT)
	{
		write(1, "\n", 1);
		if (sig_nb == SIGCHLD)
		{
			g_sig_nb = 0;
			return;
		}
		rl_replace_line("", 0);
		g_sig_nb = 0;
	}
}


void signal_init(t_data *data)
{
	struct	sigaction sa;
	g_data = data;
	sa.sa_handler = sig_handle;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGCHLD, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGTSTP, &sa, NULL);
}