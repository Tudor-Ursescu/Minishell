/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:59:37 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/21 11:10:38 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <errno.h>
int g_sig_nb = 0;

void	sig_handle(int sig_nb)
{
	if (sig_nb == SIGCHLD)
		g_sig_nb = SIGCHLD;
	else if(sig_nb == SIGINT)
	{
		write(1, "\n", 1);
		wait(NULL);
		if (sig_nb == SIGCHLD)
		{
			g_sig_nb = 0;
			return;
		}
		rl_replace_line("", 0);
		g_sig_nb = 0;
	}
	// while (wait(NULL) != -1 || errno != ECHILD);
}

void signal_init(void)
{
	struct	sigaction sa;

	sa.sa_handler = sig_handle;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGCHLD, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGTSTP, &sa, NULL);
}