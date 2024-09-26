/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:30:21 by tursescu          #+#    #+#             */
/*   Updated: 2024/09/26 14:20:31 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int parse_args(t_args **list, char *line)
{
    int i;
    int cmd;
    int count;
    count = 0;
    i = 0;
    cmd = 1;
    while (line[i])
    {
        i = skip_whitespace(line, i);
        if (line[i] == '>' || line[i] == '<')
            {
                i = add_redir(list, line, i, &cmd);
                count++;
            }
        else if (line[i] == '|')
            {
            i = add_pipe(list, i);
            count++;
            }
        else if (line[i] == '\'' || line[i] == '"')
            {
                i = add_quote_arg(list, line, i , line[i]);
                count++;
            }
        else
        {
            i = add_arg(list, line, i, &cmd);
            count++;
        }
    }
    return (count);
}
