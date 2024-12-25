/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buck.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 21:09:38 by hirwatan          #+#    #+#             */
/*   Updated: 2024/12/25 21:32:42 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char *ft_readline(int fd) {
    int buffer_size = 1024; // 適切なバッファサイズを確保
    char *buffer = (char *)malloc(buffer_size);
    if (!buffer) return NULL;
    int i = 0;
    char c;
    while (read(fd, &c, 1) > 0 && c != '\n') {
        if (i >= buffer_size - 1) {
            buffer_size *= 2;
            buffer = realloc(buffer, buffer_size);
            if (!buffer) return NULL;
        }
        buffer[i++] = c;
    }
    if (i == 0 && c != '\n') { // ファイルの終端に達した場合
        free(buffer);
        return NULL;
    }
    buffer[i] = '\0'; // 文字列の終端を設定
    return buffer;
}

int	check_errors_findP(t_map *m)
{
	int	y;
	int	x;

	if (!check_rectangle(m) && !check_collection(m))
		return (0);
	y = 0;
	while (y < m->height)
	{
		x = 0;
		while (x < m->width)
		{
			if (m->map[y][x] == 'P')
			{
				m->start_x = x;
				m->start_y = y;
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	is_valid(t_map *m, int x, int y, int **visited)
{
	if (x >= 0 && x < m->width && y >= 0 && y < m->height)
	{
		if (m->map[y][x] != '1' && visited[y][x] == 0)
			return (1);
	}
	return (0);
}

int	backtrack(t_map *m, int x, int y, int *collected, int **visited)
{
	int	dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	int	i;
	int	nx;
	int	ny;

	if (m->map[y][x] == 'C')
		(*collected)++;
	if (m->map[y][x] == 'E' && (*collected) == m->totalC)
		return (1);
	visited[y][x] = 1;
	i = 0;
	while (i++ < 4)
	{
		nx = x + dirs[i][0];
		ny = y + dirs[i][1];
		if (is_valid(m, nx, ny, visited))
		{
			if (backtrack(m, nx, ny, collected, visited) == 1)
				return (1);
			if (m->map[ny][nx] == 'C')
				(*collected)--;
		}
	}
	return (visited[y][x] = 0, 0);
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

int **initialize_visited(t_map *m) {
    int **visited = (int **)malloc(sizeof(int *) * m->height);
    if (!visited) {
        write(1, "Error\n", 6);
        return NULL;
    }
    for (int i = 0; i < m->height; i++) {
        visited[i] = (int *)malloc(sizeof(int) * m->width);
        if (!visited[i]) {
            write(1, "Error\n", 6);
            for (int j = 0; j < i; j++) {
                free(visited[j]);
            }
            free(visited);
            return NULL;
        }
        memset(visited[i], 0, sizeof(int) * m->width);
    }
    return visited;
}

void cleanup(t_map *m, int **visited) {
    for (int i = 0; i < m->height; i++) {
        free(visited[i]);
        free(m->map[i]);
    }
    free(visited);
    free(m->map);
}

int main(void) {
    int fd = open_file("maps/date");
    if (fd < 0) return 1;

    t_map m;
    map_new(&m);
    save_mapsize(fd, &m);

    if (!allocate_memory(&m)) {
        close(fd);
        return 1;
    }

    if (!reopen_file("maps/date", &fd)) {
        free(m.map);
        return 1;
    }

    load_map(&m, fd);
    close(fd);

    int **visited = initialize_visited(&m);
    if (check_errors_findP(&m) == 0 || !visited) {
        put_error_map_delete(&m);
        return 1;
    }

    int collected = 0;
    int reachable = backtrack(&m, m.start_x, m.start_y, &collected, visited);
    if (reachable == 0) write(1, "Error\n", 6);

    cleanup(&m, visited);
    return 0;
}