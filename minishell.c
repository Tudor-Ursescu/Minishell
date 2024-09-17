/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:27:51 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/17 15:03:15 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	printf("\033[H\033[J"); // clears terminal

	char	**argv;
	int		argc;
	char	*input;

	while (1)
	{
		input = prompt();
		argv = ft_split(input, ' ');
		argc = 0;
		while (argv[argc])
			argc++;
		if (argc > 0)
		{
			if (ft_strncmp(argv[0], "echo", ft_strlen(argv[0])) == 0)
				echo(argv);
			else if (ft_strncmp(argv[0], "exit", ft_strlen(argv[0])) == 0)
			{
				free_call(argv, input);
				printf("GOODBYE NYA\n");
				break;
			}
			else if (ft_strncmp(argv[0], "punch", ft_strlen(argv[0])) == 0
				|| ft_strncmp(argv[0], "hit", ft_strlen(argv[0])) == 0)
				printf("ow that hurt you bitch. piece of shit\n");
			else if (ft_strncmp(argv[0], "uwu", ft_strlen(argv[0])) == 0)
			{
				system("xdg-open https://www.youtube.com/watch?v=U06jlgpMtQs");
				printf("UWU COMRADE\n");
			}
			else if (ft_strncmp(argv[0], "cd", ft_strlen(argv[0])) == 0)
				cd_function(argv);
			else if (ft_strncmp(argv[0], "pwd", ft_strlen(argv[0])) == 0)
				pwd_function();
			else if (ft_strncmp(argv[0], "ls", ft_strlen(argv[0])) == 0)
				ls_function();
			else
				printf("uwushell: command not found: %s\n", argv[0]);
		}
		free_call(argv, input);
	}
}

void	free_call(char **argv, char *input)
{
	int	i;
	free(input);
	i = 0;
	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);

}

// char *command;
// input = NULL;
// command = prompt(input);

// free(input);

// int main (void)
// {
// 	char *argv[100];
//     int argc;
// 	while (1)
// 	{
// 		char *input;
// 		input = prompt();

// 		argc = 0;
// 		char **tokens = ft_split(input, ' ');
//         while (tokens[argc] != NULL)
//         {
//             argv[argc] = tokens[argc];
//             argc++;
//         }
//         argv[argc] = NULL;
// 		if (argc > 0)
// 		{
// 			if(ft_strncmp(argv[0], "echo", ft_strlen(argv[0])) == 0)
// 				echo(argv);
// 			else if(ft_strncmp(argv[0], "exit", ft_strlen(argv[0])) == 0)
// 			{
// 				free(input);
//                 free_tokens(tokens);
// 				break ;
// 			}
// 			else if(ft_strncmp(argv[0], "punch", ft_strlen(argv[0])) == 0)
// 				printf("ow that hurt you bitch. piece of shit\n");
// 		}

// 		free(input);
//         free_tokens(tokens);
// 	}
// }
