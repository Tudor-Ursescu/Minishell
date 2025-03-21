/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:00:39 by tursescu          #+#    #+#             */
/*   Updated: 2025/03/21 10:19:26 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

t_cmd	*create_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
	{
		printf("Memory alloc failed for command\n");
		return (NULL);
	}
	new_cmd->redirections = NULL;
	new_cmd->args = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

int	process_current_cmd(t_cmd *cmd, t_token *curr_tokens, t_cmd *cmd_list)
{
	cmd->redirections = get_redirections(curr_tokens);
	cmd->args = get_args(curr_tokens);
	if (cmd->args == NULL)
	{
		printf("Command creation failed\n");
		free_cmds(cmd_list);
		free(cmd);
		return (1);
	}
	return (0);
}

void	link_command(t_cmd **cmd_list, t_cmd **last_cmd, t_cmd *new_cmd)
{
	if (*cmd_list == NULL)
	{
		*cmd_list = new_cmd;
		*last_cmd = new_cmd;
	}
	else
	{
		(*last_cmd)->next = new_cmd;
		*last_cmd = new_cmd;
	}
}

t_cmd	*create_cmd_list(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*last_cmd;
	t_cmd	*curr_cmd;
	t_token	*curr_tokens;

	cmd_list = NULL;
	last_cmd = NULL;
	curr_tokens = tokens;
	while (curr_tokens != NULL)
	{
		curr_cmd = create_cmd();
		if (!curr_cmd)
		{
			free_cmds(cmd_list);
			return (NULL);
		}
		if (process_current_cmd(curr_cmd, curr_tokens, cmd_list) == 1)
			return (NULL);
		link_command(&cmd_list, &last_cmd, curr_cmd);
		curr_tokens = find_next_cmd(curr_tokens);
	}
	return (cmd_list);
}
