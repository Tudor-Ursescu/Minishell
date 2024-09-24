/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:19:14 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/19 12:18:13 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

// #include <stddef.h>
// #include <fcntl.h>
// #include <stdio.h>
// #include <sys/stat.h>
// int main (void)
// {
// //int fd = open("output.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
// 	char *s = "hello";
// 	ft_putstr_fd(s, 1); // or uncomment for textfile
// // close(fd);
// }