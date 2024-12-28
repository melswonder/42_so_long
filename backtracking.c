/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 21:09:38 by hirwatan          #+#    #+#             */
/*   Updated: 2024/12/28 14:28:33 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	save_mapsize(int fd, t_map *m)
{
	char	*line;

	while ((line = ft_readline(fd)) != NULL)
	{
		if (m->height == 0)
			m->width = ft_strlen(line);
		m->height++;
		free(line);
	}
}

int	allocate_memory(t_map *m)
{
	m->map = (char **)malloc(sizeof(char *) * m->height);
	if (!m->map)
	{
		write(1, "Error\n", 6);
		return (0);
	}
	return (1);
}

void	load_map(t_map *m, int fd)
{
	char	*line;
	int		row;

	row = 0;
	while ((line = ft_readline(fd)) != NULL)
	{
		m->map[row] = line;
		row++;
	}
}

void	cleanup(t_map *m, int **visited)
{
	for (int i = 0; i < m->height; i++)
	{
		free(visited[i]);
		free(m->map[i]);
	}
	free(visited);
	free(m->map);
}

int check_valid_map(void)
{
	int		fd;
	t_map	m;
	int		**visited;
	int		collected;
	int		reachable;

	fd = open_file("maps/date");
	if (fd < 0)
		return (1);
	map_new(&m);
	save_mapsize(fd, &m);
	if (!allocate_memory(&m))
		return (close(fd), 1);
	if (!reopen_file("maps/date", &fd))
		return (free(m.map), 1);
	load_map(&m, fd);
	close(fd);
	visited = initialize_visited(&m);
	if (check_errors_findP(&m) == 0 || !visited)
		return (put_error_map_delete(&m), 1);
	collected = 0;
	reachable = backtrack(&m, m.start_x, m.start_y, &collected, visited);
	if (reachable == 0)
		write(1, "Error\n", 6);
	return (cleanup(&m, visited), 0);
}
