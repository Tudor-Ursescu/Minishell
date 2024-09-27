/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:00:39 by tursescu          #+#    #+#             */
/*   Updated: 2024/09/27 16:38:00 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
// the cmdlist should hold multiple nodes based on how many chunks are present in the terminal cmdline
// the chunks will be determined(separated) by pipes. In every cmd node we have a matrix that holds the 
// args and a struct that holds the redirections.
t_cmd	create_cmd_list()