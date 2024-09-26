/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_and_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:48:50 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/26 15:14:35 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parser.h"
// if pipe = 1, argv 0 pipe to argv 1

void	handle_pipe(char **argv, int number_of_pipes, char **envp) //maybe do recursive...
{
	// somehow get this function triggered only if there was a piping symbol in argv
	int pipefd[2];
	int i;
	int pid;

	if (number_of_pipes == 0)
		execute_path(argv, envp);//TUDOR
	i = 0;
	if (number_of_pipes > 0)//change this for tudorparse
		pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execute_path(argv, envp);//change for tudorparse
        exit(0);
	}
	else
    {
        close(pipefd[1]); 
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        // Recursively handle the remaining commands
        handle_pipe(argv, number_of_pipes - 1, envp); // tudorparse argv plssss
        waitpid(pid, NULL, 0);
    }
}