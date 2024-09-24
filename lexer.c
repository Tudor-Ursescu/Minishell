/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:53:53 by tursescu          #+#    #+#             */
/*   Updated: 2024/09/23 15:17:57 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


// t_args	**lexer(const char *input)
// {
// 	t_args	**args;
// 	int		a_count;
// 	int		i;
// 	int		start;
// 	char	*word;

// 	a_count = 0;
// 	i = 0;
// 	args = (t_args **)malloc(sizeof(t_args *) * 200);
// 	if(!args)
// 		return (NULL);
// 	while (input[i] != '\0')
// 	{
// 		while (ft_isspace(input[i]))
// 			i++;
// 		if (input[i] == '\0')
// 			break ;
// 		if (input[i] == '|')
// 		{
// 			args[a_count++] = create_arg(T_PIPE, "|");
// 			i++;
// 			continue;
// 		}
// 		if (input[i] == '>')
// 		{
// 			args[a_count++] = create_arg(T_RED_TO, ">");
// 			i++;
// 			continue;
// 		}
// 		if (input[i] == '<')
// 		{
// 			args[a_count++] = create_arg(T_RED_FROM, "<");
// 			i++;
// 			continue;
// 		}
// 		if (input[i] == '>' && input[i + 1] == '>')
// 		{
// 			args[a_count++] = create_arg(T_REDIR_APPEND, ">>");
// 			i += 2;
// 			continue;
// 		}
// 		if (input[i] == '<' && input[i + 1] == '<')
// 		{
// 			args[a_count++] = create_arg(T_HEREDOC, "<<");
// 			i += 2;
// 			continue;
// 		}
// 		if (is_word_char(input[i]))
// 		{
// 			start = i;
// 			while (is_word_char(input[i]))
// 				i++;
// 			word = ft_strndup(input + start, i - start);
// 			args[a_count++] = create_arg(T_CMD, word);
// 			free(word);
// 			continue; 
// 		}
// 		else
// 			i++;
// 	}
// 	args[a_count++] = create_arg(T_END, "");
// 	args[a_count] = NULL;
// 	return (args); 
// }

// void print_args(t_args **args)
// {
// 	int i;
	
// 	i = 0;
// 	while (args[i] != NULL)
// 	{
// 		printf("Token Type: %d, Value: '%s'\n", args[i]->type, args[i]->value);
// 		i++;
// 	}
// }