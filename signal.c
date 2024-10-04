/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:04:59 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/04 15:27:55 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	setup_signal_handlers(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_sigint(int signum)
{
	// int status;
	// if (signum == SIGINT && wait(&status) == -1)
	// {
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	// }
}
void	mini_newline(int signum)
{
	(void)signum;
	write(1, "\n", 1);
}

void	load_ammo(int signum)
{
	(void)signum;
	g_sig = 1;
}