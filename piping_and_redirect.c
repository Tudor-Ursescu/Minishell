/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_and_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:48:50 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/25 08:57:49 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if pipe = 1, argv 0 pipe to argv 1

void	handle_pipe(char **argv, int pipeflag)
{
	// somehow get this function triggered only if there was a piping symbol in argv
	int pipefd[2];
	int i;
	int pid;
	i = 0;
	if (argv[i + 1] != NULL && pipeflag == 1)
		pipe(pipefd);
	pid = fork();
	while (argv[i])
	{
		
	}
}