/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:32:16 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/19 12:18:35 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		write(fd, "-2", 2);
		n = 147483648;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	if (n < 10)
	{
		c = n + 48;
		write(fd, &c, 1);
	}
}

// #include <stddef.h>
// #include <fcntl.h>
// #include <stdio.h>
// #include <sys/stat.h>
/*
int main (void)
{
//int fd = open("output.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	int c = -1;
	ft_putnbr_fd(c, 1); // or uncomment for textfile
// close(fd);
}
*/