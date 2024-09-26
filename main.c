/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:59:47 by tursescu          #+#    #+#             */
/*   Updated: 2024/09/26 14:00:48 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <string.h>
// int main (void)
// {
//     t_args *arg_list;
//     char *line;

//     while (1)
//     {
// 		line = readline("minishell> ");
// 		printf("%s\n", line);
// 		if (line == NULL || strcmp(line, "exit") == 0)
// 		{
// 			free(line);
// 			break;
// 		}
// 		if(line[0] != '\0')
// 			add_history(line);
// 		arg_list = NULL;
// 		parse_args(&arg_list, line);
// 		if (arg_list == NULL)
// 			printf("Parsing failed!");
// 		else
// 			print_arg_list(arg_list);
// 		free_args(&arg_list);
// 		free(line);
//     }
// 	return (0);
// }