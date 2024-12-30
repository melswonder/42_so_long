/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_open_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 14:18:04 by hirwatan          #+#    #+#             */
/*   Updated: 2024/12/30 21:28:55 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	read_line_new(int *buf_size, char **buf, int *i)
{
	*buf_size = 128;
	*buf = malloc(*buf_size);
	if (!*buf)
		return ;
	*i = 0;
}

char	*ft_readline(int fd)
{
	int		buf_size;
	char	*buf;
	int		i;
	char	c;

	read_line_new(&buf_size, &buf, &i);
	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
			break ;
		buf[i++] = c;
		if (i == buf_size - 1)
		{
			buf_size *= 2;
			buf = realloc(buf, buf_size);
			if (!buf)
				return (NULL);
		}
	}
	if (i == 0 && c != '\n')
		return (free(buf), NULL);
	return (buf[i] = '\0', buf);
}

int	open_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(1, "Error\n", 6);
	}
	return (fd);
}

int	reopen_file(const char *filename, int *fd)
{
	close(*fd);
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
	{
		write(1, "Error\n", 6);
		return (0);
	}
	return (1);
}
