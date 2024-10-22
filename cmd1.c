/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:36:56 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/22 17:45:10 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	nb_of_args(t_token *tokens)
{
	size_t	res;
	int		was_red;

	was_red = 0;
	res = 0;
	while (tokens)
	{
		if (is_pipe(tokens))
			break ;
		if (is_redirection(tokens))
			was_red = 1;
		else if (!is_redirection(tokens) && !is_pipe(tokens) && !was_red)
			res++;
		if (was_red && !is_redirection(tokens))
			was_red = 0;
		tokens = tokens->next;
	}
	return (res);
}

char	**get_args(t_token *tokens)
{
	char	**args;
	size_t	size;
	size_t	i;

	i = 0;
	size = nb_of_args(tokens);
	args = malloc((size + 1) * sizeof(char *));
	if (!args)
	{
		printf("Allocation error(args initialisation)\n");
		return (NULL);
	}
	while (i < size && tokens != NULL && tokens->type != T_PIPE)
	{
		if (is_redirection(tokens))
			tokens = tokens->next->next;
		if (tokens && !is_redirection(tokens) && !is_pipe(tokens))
		{
			args[i] = ft_strdup(tokens->value);
			i++;
		}
		tokens = tokens->next;
	}
	args[i] = NULL;
	return (args);
}

t_token	*get_redirections(t_token *tokens)
{
	t_token	*redirections;
	t_token	*new_redir;

	new_redir = NULL;
	redirections = NULL;
	while (tokens != NULL)
	{
		if (is_pipe(tokens))
			break ;
		if (is_redirection(tokens) && tokens->next)
		{
			new_redir = create_token(tokens->type, tokens->next->value);
			append_token(&redirections, new_redir);
		}
		tokens = tokens->next;
	}
	return (redirections);
}

t_token	*find_next_cmd(t_token *tokens)
{
	while (tokens != NULL)
	{
		if (!is_pipe(tokens))
			tokens = tokens->next;
		else
			return (tokens->next);
	}
	return (NULL);
}
