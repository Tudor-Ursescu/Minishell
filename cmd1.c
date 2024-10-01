/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:36:56 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/01 16:10:56 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
// the cmdlist should hold multiple nodes based on how many chunks are present in the terminal cmdline
// the chunks will be determined(separated) by pipes. In every cmd node we have a matrix that holds the 
// args and a struct that holds the redirections.

//function that goes trough the token list and counts the ones that are taken as args
size_t nb_of_args(t_token *tokens)
{
    size_t res;

    res = 0;
    while (tokens != NULL && !is_pipe(tokens))
    {
        if (!is_redirection(tokens))
            res++;
        tokens = tokens->next;
    }
    return (res);
}

// function that takes the tokens regarded as args, and adds them in the args matrix contained in cmd 
char    **get_args(t_token *tokens)
{
    char    **args;
    size_t  size;
    size_t  i;

    i = 0;
    size = nb_of_args(tokens);
    if (size == 0)
    {
        printf("Error: ");
        return (NULL);
    }
    args = malloc (sizeof(char *) * (size + 1));
    if (!args)
    {
        printf("Allocation error(args initialisation)\n");
        return (NULL);
    }
    while (i != size)
    {
        if (!is_redirection(tokens) && tokens->value != NULL)
            args[i++] = ft_strdup(tokens->value);
        tokens = tokens->next;
    }
    return (args);
}

//takes redir tokens dfrom the token list and adds them in the struct redirections contained in cmd
t_token *get_redirectons(t_token *tokens)
{
    t_token *redirections;
    
    redirections = NULL;
    while (tokens != NULL && !is_pipe(tokens))
    {
        if (is_redirection(tokens))
            append_token(&redirections, tokens);// to dup probably
        tokens = tokens->next;
    }
    return (redirections);
}
//this function finds the pipe and returns the tokens after the pipe
t_token *find_next_cmd(t_token *tokens)
{
    while(tokens != NULL && !is_pipe(tokens))
        tokens = tokens->next;
    if (is_pipe(tokens))
        tokens = tokens->next;
    return (tokens);
}

