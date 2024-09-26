/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:52:18 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/26 13:48:10 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	void	*dest_ptr;

	dest_ptr = dst;
	if ((!dst && !src) || dst == src)
		return (dst);
	if (dst >= src)
	{
		while (n--)
			((char *)dst)[n] = ((char *)src)[n];
	}
	else if (dst < src)
	{
		while (n--)
			*(char *)dst++ = *(char *)src++;
	}
	return (dest_ptr);
}

void	ft_bzero(void *s, size_t n)
{
	char	*ptr;

	ptr = (char *)s;
	while (n > 0)
	{
		*ptr = 0;
		ptr++;
		n--;
	}
}

int	ft_vandr(int bytesread, int fd, char *ch, char **chartobesplit)
{
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		ft_bzero((char *)ch, BUFFER_SIZE);
		free(*chartobesplit);
		*chartobesplit = NULL;
		return (-1);
	}
	if (ch[0] == '\0')
	{
		bytesread = read(fd, ch, BUFFER_SIZE);
		if (bytesread <= 0)
		{
			free(*chartobesplit);
			*chartobesplit = NULL;
			return (-1);
		}
		ch[bytesread] = '\0';
	}
	return (bytesread);
}

char	*ft_newline(int *i, int *j, char *chartobesplit, char *ch)
{
	if (ch[*j] == '\n')
	{
		chartobesplit[(*i)++] = ch[(*j)++];
		chartobesplit[*i] = '\0';
		ft_memmove(&ch[0], &ch[*j], ft_strlen(&ch[*j]) + 1);
		return (chartobesplit);
	}
	else if (ch[*j] == '\0')
	{
		chartobesplit[*i] = '\0';
		return (chartobesplit);
	}
	return (NULL);
}
