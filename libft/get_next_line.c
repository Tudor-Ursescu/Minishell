/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:32:27 by ckonneck          #+#    #+#             */
/*   Updated: 2024/07/09 13:53:48 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	ch[BUFFER_SIZE + 1];
	int			bytesread;
	int			i;
	int			j;
	char		*chartobesplit;

	bytesread = 0;
	i = 0;
	j = 0;
	chartobesplit = malloc(21001);
	if (!(chartobesplit) || ft_vandr(bytesread, fd, ch, &chartobesplit) == -1)
		return (NULL);
	while (ch[j] != '\n' && ch[j] != '\0')
	{
		chartobesplit[i++] = ch[j++];
		if (!ch[j])
		{
			bytesread = read(fd, ch, BUFFER_SIZE);
			if (bytesread <= 0)
				chartobesplit[i] = '\0';
			ch[bytesread] = '\0';
			j = 0;
		}
	}
	return (ft_newline(&i, &j, chartobesplit, ch));
}

// #include <stdio.h>
// #include <fcntl.h>
// #include <stdlib.h>
// #include <string.h>
// int	main(void)
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	char	*line;

// 	int count = 0;
// 	while (count < 10)
// 	{	
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line);
// 		count++;
// 	} 

// 	close(fd);

// 	return (0);
// }
