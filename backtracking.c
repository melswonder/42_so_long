/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 21:09:38 by hirwatan          #+#    #+#             */
/*   Updated: 2024/12/30 20:31:33 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	save_mapsize(int fd, t_map *m)
{
	char	*line;

	line = ft_readline(fd);
	while (line != NULL)
	{
		if (m->height == 0)
			m->width = ft_strlen(line);
		m->height++;
		free(line);
		line = ft_readline(fd);
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
	line = ft_readline(fd);
	while (line != NULL)
	{
		if (row >= m->height)
		{
			free(line);
			break ;
		}
		m->map[row] = line;
		row++;
		line = ft_readline(fd);
	}
}

int	backtrack(t_map *m, int x, int y, int **visited)
{
	int	i;
	int	coords[2];

	if (m->map[y][x] == 'C')
		m->collected++;
	if (m->map[y][x] == 'E' && m->collected == m->total_c)
		return (1);
	visited[y][x] = 1;
	i = 0;
	while (i < 4)
	{
		check_direction(x, y, i, coords);
		if (is_valid(m, coords[0], coords[1], visited))
		{
			if (backtrack(m, coords[0], coords[1], visited) == 1)
				return (1);
			if (m->map[coords[1]][coords[0]] == 'C')
				m->collected--;
		}
		i++;
	}
	return (visited[y][x] = 0, 0);
}

int	check_valid_map(t_map *m)
{
	int	fd;
	int	**visited;
	int	reachable;

	fd = open_file("maps/date");
	if (fd < 0)
		return (0);
	map_new(m);
	save_mapsize(fd, m);
	if (!allocate_memory(m))
		return (close(fd), 0);
	if (!reopen_file("maps/date", &fd))
		return (free(m->map), 0);
	load_map(m, fd);
	close(fd);
	visited = initialize_visited(m);
	if (check_errors_find_p(m) == 0 || !visited)
		return (put_error_map_delete(m), 0);
	m->collected = 0;
	reachable = backtrack(m, m->start_x, m->start_y, visited);
	if (reachable == 0)
		return (write(1, "Error\n", 6), cleanup(m, visited), 0);
	return (cleanup(m, visited), 1);
}
