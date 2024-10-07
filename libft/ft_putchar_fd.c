/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:46:18 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/19 11:36:57 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

// #include <stddef.h>
// #include <fcntl.h>
// #include <stdio.h>
// #include <sys/stat.h>
// int	main(void)
// {
// 	int fd = open("output.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
// 	ft_putchar_fd('H', 1);
// 	ft_putchar_fd('e', fd);
// 	ft_putchar_fd('l', fd);
// 	ft_putchar_fd('l', fd);
// 	ft_putchar_fd('o', fd);
// 	ft_putchar_fd(',', 1);
// 	ft_putchar_fd(' ', fd);
// 	ft_putchar_fd('"', fd);
// 	ft_putchar_fd('W', fd);
// 	ft_putchar_fd('o', fd);
// 	ft_putchar_fd('r', fd);
// 	ft_putchar_fd('l', fd);
// 	ft_putchar_fd('d', fd);
// 	ft_putchar_fd('!', fd);
// 	char *message = "Hello, World!";
// 	size_t length = ft_strlen(message);
// 	for (size_t i = 0; i < length; ++i)
// 		ft_putchar_fd(message[i], fd);
// 	close(fd);

// 	return 0;
// }