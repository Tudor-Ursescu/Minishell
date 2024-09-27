/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:30:21 by tursescu          #+#    #+#             */
/*   Updated: 2024/09/27 16:04:10 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int parse_args(t_token **list, char *line)
{
    int i;
    int cmd;
    int count;

    i = 0;
    cmd = 1;
    while (line[i])
    {
        i = skip_whitespace(line, i);
        if (line[i] == '>' || line[i] == '<')
            i = add_redir(list, line, i, &cmd);
        else if (line[i] == '|')
            i = add_pipe(list, i);
        else if (line[i] == '\'' || line[i] == '"')
            i = add_quote_arg(list, line, i , line[i]);
        else
            i = add_arg(list, line, i, &cmd);
    }
    return (0);
}