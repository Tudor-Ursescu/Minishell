/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_and_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:48:50 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/08 10:30:21 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// if pipe = 1, argv 0 pipe to argv 1

void	handle_pipe(t_cmd *cmd_list, int number_of_pipes, char **envp) //maybe do recursive...
{
	// somehow get this function triggered only if there was a piping symbol in argv
	int pipefd[2];
	int i;
	int pid;
	int saved_stdin = dup(STDIN_FILENO);  // Save the original stdin
	int saved_stdout = dup(STDOUT_FILENO); // Save the original stdout
	if (number_of_pipes == 0)
	{
		handle_redirect_or_execute(cmd_list, envp);
		dup2(saved_stdin, STDIN_FILENO);   
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return;
	}
	i = 0;
	if (number_of_pipes > 0)
		pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execute_path(cmd_list, envp);
        exit(0);
	}
	else
    {
        close(pipefd[1]); 
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        // Recursively handle the remaining commands
		printf("WE GOING DOWN BOIS\n");
        handle_pipe(cmd_list->next, number_of_pipes - 1, envp); // tudorparse argv plssss
        waitpid(pid, NULL, 0);
    }
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}