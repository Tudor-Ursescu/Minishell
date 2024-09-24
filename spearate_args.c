/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spearate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:49:05 by tursescu          #+#    #+#             */
/*   Updated: 2024/09/23 17:15:25 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	which_red(char *line, int i)
{
    if (line[i] == '>')
    {
		if (line[i + 1] == '>')
			return (i + 2);
		else
			return (i + 1);
    }
	else if (line[i] == '<')
	{
		if (line[i + 1] == '<')
			return (i + 2);
		else
			return (i + 1);
	}
}

int append_redir(t_args **head, char *line, int i, int *cmd)
{
	t_args *temp;
	
	*cmd = 0;
	if (line[i] == '<')
	{
		if (line[i + 1] == '<')
			temp = create_arg(T_HEREDOC, "<<");
		else
			temp = create_arg(T_RED_FROM, "<");
	}
	else
	{
		if (line[i + 1] == '>')
			temp = create_arg(T_REDIR_APPEND, ">>");
		else
			temp = create_arg(T_RED_TO, "<");
	}
	append_arg(head, temp);
	return (which_red(line, i));
}

int append_pipe(t_args **head, int *i)
{
	t_args	*temp;
	
	temp = create_arg(T_PIPE, "|");
	append_arg(head, temp);
	*i += 1;
	return (1);
}

int append_arg(t_args **list, char *line, int i)
{
	t_args	*temp;
	char	*arg;

	if (line )
}