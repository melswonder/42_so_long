/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:21:09 by hirwatan          #+#    #+#             */
/*   Updated: 2024/12/22 01:58:21 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char **map;
    int width;
    int height;
    int collectibles;
    int start_x;
    int start_y;
} GameMap;


int	find_new_line(char *str)
{
	if (!str)
		return (0);
	while (*str != '\0')
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

char	*left_over(char *str)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	i = 0;
	j = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	new_str = (char *)malloc(ft_strlen(str + i) + 1);
	if (!new_str)
		return (NULL);
	i++;
	while (str[i] != '\0')
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*return_line(char *str)
{
	char	*dest;
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 2));
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		dest[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		dest[i++] = '\n';
	dest[i] = '\0';
	return (dest);
}

char	*read_and_append(int fd, char *buffer)
{
	char	*buf;
	char	*temp;
	int		byte_lead;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	byte_lead = 1;
	while (!find_new_line(buffer) && byte_lead > 0)
	{
		byte_lead = read(fd, buf, BUFFER_SIZE);
		if (byte_lead < 0)
		{
			free(buf);
			free(buffer);
			return (NULL);
		}
		buf[byte_lead] = '\0';
		temp = buffer;
		buffer = ft_strjoin(buffer, buf);
		free(temp);
		if (!buffer)
			break ;
	}
	return (free(buf), buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_and_append(fd, buffer);
	if (!buffer)
		return (NULL);
	if (!buffer[0])
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = return_line(buffer);
	buffer = left_over(buffer);
	return (line);
}
int is_valid_move(GameMap *game_map, int x, int y, int **visited) {
    if (x >= 0 && x < game_map->width && y >= 0 && y < game_map->height) {
        if (game_map->map[y][x] != '1' && !visited[y][x]) {
            return 1;
        }
    }
    return 0;
}

int backtrack(GameMap *game_map, int x, int y, int **visited, int collected) {
    if (game_map->map[y][x] == 'E' && collected == game_map->collectibles) {
        return 1;
    }

    visited[y][x] = 1;

    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int i = 0;
    while (i < 4) {
        int new_x = x + directions[i][0];
        int new_y = y + directions[i][1];

        if (is_valid_move(game_map, new_x, new_y, visited)) {
            if (game_map->map[new_y][new_x] == 'C') {
                collected++;
            }
            if (backtrack(game_map, new_x, new_y, visited, collected)) {
                return 1;
            }
            if (game_map->map[new_y][new_x] == 'C') {
                collected--;
            }
        }
        i++;
    }

    visited[y][x] = 0;
    return 0;
}

int check_map(GameMap *game_map) {
    // Check if the map is rectangular
    int i = 0;
    while (i < game_map->height) {
        if (strlen(game_map->map[i]) != game_map->width) {
            return 0;
        }
        i++;
    }

    // Check if the map is surrounded by walls
    i = 0;
    while (i < game_map->width) {
        if (game_map->map[0][i] != '1' || game_map->map[game_map->height - 1][i] != '1') {
            return 0;
        }
        i++;
    }
    i = 0;
    while (i < game_map->height) {
        if (game_map->map[i][0] != '1' || game_map->map[i][game_map->width - 1] != '1') {
            return 0;
        }
        i++;
    }

    int **visited = (int **)malloc(game_map->height * sizeof(int *));
    i = 0;
    while (i < game_map->height) {
        visited[i] = (int *)calloc(game_map->width, sizeof(int));
        i++;
    }

    int result = backtrack(game_map, game_map->start_x, game_map->start_y, visited, 0);

    i = 0;
    while (i < game_map->height) {
        free(visited[i]);
        i++;
    }
    free(visited);

    return result;
}

char *get_next_line(int fd) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    read = getline(&line, &len, fdopen(fd, "r"));
    if (read == -1) {
        free(line);
        return NULL;
    }
    if (line[read - 1] == '\n') {
        line[read - 1] = '\0';
    }
    return line;
}

int main() {
    int fd;
    char *line;
    fd = open("date", O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    GameMap game_map;
    game_map.collectibles = 0;
    game_map.height = 0;

    // First pass to determine map height and width
    while ((line = get_next_line(fd)) != NULL) {
        if (game_map.height == 0) {
            game_map.width = strlen(line);
        }
        game_map.height++;
        free(line);
    }

    // Allocate memory for the map
    game_map.map = (char **)malloc(game_map.height * sizeof(char *));
    lseek(fd, 0, SEEK_SET); // Reset file descriptor to the beginning

    // Second pass to read the map data
    int i = 0;
    while ((line = get_next_line(fd)) != NULL) {
        game_map.map[i] = line;
        int j = 0;
        while (j < game_map.width) {
            if (line[j] == 'P') {
                game_map.start_x = j;
                game_map.start_y = i;
            } else if (line[j] == 'C') {
                game_map.collectibles++;
            }
            j++;
        }
        i++;
    }
    close(fd);

    if (check_map(&game_map)) {
        printf("The map is valid and the player can reach the exit after collecting all items.\n");
    } else {
        printf("The map is invalid or the player cannot reach the exit after collecting all items.\n");
    }

    // Free the map data
    i = 0;
    while (i < game_map.height) {
        free(game_map.map[i]);
        i++;
    }
    free(game_map.map);

    return 0;
}