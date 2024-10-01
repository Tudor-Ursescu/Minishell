/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:49:05 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/01 12:20:53 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	return (0);
}

int add_redir(t_token **head, char *line, int i, int *cmd)
{
	t_token *new;
	
	*cmd = 0;
	if (line[i] == '<')
	{
		if (line[i + 1] == '<')
			new = create_arg(T_HEREDOC, "<<");
		else
			new = create_arg(T_IN, "<");
	}
	else
	{
		if (line[i + 1] == '>')
			new = create_arg(T_APPEND, ">>");
		else
			new = create_arg(T_OUT, ">");
	}
	append_arg(head, new);
	return (which_red(line, i));
}

int add_pipe(t_token **head, int i)
{
	t_token	*temp;
	
	temp = create_arg(T_PIPE, "|");
	append_arg(head, temp);
	i += 1;
	return (i);
}

int	add_quote_arg(t_token **list, char *line, int i, char quote)
{
	t_token	*new;
	int		start;
	char	*sub;

	start = i + 1; //Skip the opening quote;
	while (line[i] && line[i] != quote)
		i++;
	if (line[i] == quote)
	{
		sub = ft_substr(line, start, i - start);
		new = create_arg(T_WORD, sub);
		free(sub);
		append_arg(list, new);
		i++;//ending quote
	}
	return (i);
}

int	add_arg(t_token **list, char *line, int i, int *cmd)
{
	t_token	*new;
	int		start;
	char	*sub;
	start = i;
	while (line[i] && is_word_char(line[i]))
		i++;
	if (start != i)
	{
		sub = ft_substr(line, start, i - start);
		new = create_arg(T_WORD, sub);
		free(sub);
		append_arg(list, new);
		*cmd = 0;
	}
	return (i);
}