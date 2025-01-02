/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 21:09:38 by hirwatan          #+#    #+#             */
/*   Updated: 2025/01/02 18:14:05 by hirwatan         ###   ########.fr       */
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
	int i;
	
	i = 0;
	m->map = (char **)malloc(sizeof(char *) * m->height);
	if (!m->map)
		return (write(1, "Error\n", 6),0);
	while(i < m->height)
	{
		m->map[i] = NULL;
		i++;
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
void	free_visited(int **visited, int height)
{
    int	i;

    i = 0;
    while (i < height)
    {
        free(visited[i]);
        i++;
    }
    free(visited);
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
	if (!reachable)
		return (write(1, "Error\n", 6), cleanup(m, visited), 0);
	free_visited(visited,m->height);
	return (1);
}
