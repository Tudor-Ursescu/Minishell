/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:27:51 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/16 14:07:15 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

int g_exit = 0;

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	t_token *token_list;
	t_cmd	*cmd_list;
	t_pipeinfo pipeinfo;
	char		*line;
	cmd_list = NULL;
	token_list = NULL;
	line = NULL;
	printf("\033[H\033[J");
	setup_signal_handlers();
	while (1)
	{
		line = prompt();
		if (strcmp(line, "env") == 0)
		{
			ft_env(envp);
			continue;
		}
		token_list = tokenize(line);
		if (!token_list)
		{
			free(line);
			continue;
		}	
		if (check_syntax(token_list))
		{
			free_tokens(&token_list);
			free(line);
			continue;
		}
		cmd_list = create_cmd_list(token_list);
		if (!cmd_list)
		{
			printf("Parsing failed!\n");
			free(line);
			free_tokens(&token_list);
			return (0);
		}
		argc = 0;
		while (cmd_list->args[argc])
			argc++;
		if (argc > 0)
		{	
			if (ft_strncmp(line, "$?", ft_strlen("$?")) == 0)
				printf("%d ", g_exit);
			if (ft_strncmp(line, "exit", ft_strlen("exit")) == 0)
			{
				exit_function(cmd_list->args, line);
			}
			pipeinfo = initialize_pipeinfo(token_list);
			if (pipeinfo.number_of_pipes > 0)
			{
				handle_pipe(cmd_list, envp, pipeinfo);
			}
			else if (pipeinfo.number_of_pipes == 0)
				handle_redirect_or_execute(cmd_list, envp);
		}
		free_all(cmd_list, token_list);
		free(line);
	}
}

t_pipeinfo initialize_pipeinfo(t_token *token_list)
{
	t_pipeinfo pipeinfo;
	t_token *temp = token_list;
	pipeinfo.number_of_pipes = 0;
	while (temp)
	{
		if (temp->type == T_PIPE)
			pipeinfo.number_of_pipes++;
		temp = temp->next;
	}
	free(temp);
	pipeinfo.prev_fd = -1;
	pipeinfo.prev_pid = -1;
	return (pipeinfo);
}

void    free_call(char **argv, char *input)
{
    int i;
    free(input);
    i = 0;
    while (argv[i] != NULL)
    {
        free(argv[i]);
        i++;
    }
    free(argv);
}

void    exit_function(char **argv, char *input)
{
    printf("GOODBYE NYA\n");
	g_exit = 2;
    free_call(argv, input);
    exit(0);
}

void restore_fds(int saved_stdin, int saved_stdout)
{
    // Restore stdin
    dup2(saved_stdin, STDIN_FILENO);
    // Restore stdout
    dup2(saved_stdout, STDOUT_FILENO);
    // Close the saved file descriptors
    close(saved_stdin);
    close(saved_stdout);
}

void handle_redirect_or_execute(t_cmd *cmd_list, char **envp)
{
    int fd = 0;
	int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);
	t_token *temp = cmd_list->redirections;
    // Iterate through redirections to set them up
	int flag = 0;
	char *file;
    while (cmd_list->redirections)
    {
        if (cmd_list->redirections->type == T_HEREDOC) // <<
        {	
        	heredoc(cmd_list->args, envp, cmd_list->redirections->value);
			flag = 1;
			free(cmd_list->redirections->value);
			cmd_list->redirections->value = ft_strdup("tempfile.txt");
			fd = open("tempfile.txt", O_RDONLY);
            dup2(fd, STDIN_FILENO);	
            close(fd);
        }
		cmd_list->redirections = cmd_list->redirections->next;
	}
			// restore_fds(saved_stdin, saved_stdout);
	cmd_list->redirections = temp;
	while (cmd_list->redirections)
	{
		file = cmd_list->redirections->value;
        if (cmd_list->redirections->type == T_APPEND) // >>
        {
            // printf("triggered T APPEND (>>)\n");
            // Setup output append redirection (stdout)
            fd = open(cmd_list->redirections->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (cmd_list->redirections->type == T_IN) // < THIS IS SOMEHOW SHIT
        {
			if (flag == 1)
				file = "tempfile.txt";
            // Setup input redirection (stdin)// triggers error == Warning: invalid file descriptor -1 in syscall close()
            fd = open(file, O_RDONLY);
			if (fd < 0)
			{
				perror("fd error");
				return;
			}
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        else if (cmd_list->redirections->type == T_OUT) // >
        {
			// Setup output redirection (stdout)
            fd = open(cmd_list->redirections->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        cmd_list->redirections = cmd_list->redirections->next;
	}
    // Now execute the command after all redirections have been set up
	// printf("EXECUTING\n");
    execute_path(cmd_list, envp);
	restore_fds(saved_stdin, saved_stdout);
	free_tokens(&temp);
	unlink("tempfile.txt");
}
