/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_new_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:39:19 by hirwatan          #+#    #+#             */
/*   Updated: 2024/12/28 14:22:58 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_new(t_map *m)
{
	m->map = 0;
	m->height = 0;
	m->width = 0;
	m->totalC = 0;
	m->countP = 0;
	m->countE = 0;
	m->start_x = 0;
	m->start_y = 0;
}

void	put_error_map_delete(t_map *m)
{
	int	i;

	write(1, "Error\n", 6);
	if (m->map)
	{
		i = 0;
		while (i < m->height)
		{
			free(m->map[i]);
			i++;
		}
		free(m->map);
	}
}

void	gnl_new(t_read *sg)
{
	sg->line = NULL;
	sg->ret = 0;
	sg->len = 0;
	sg->new_line = NULL;
	sg->i = 0;
}

void	gnl_delete(t_read *sg)
{
	sg->line = NULL;
	sg->ret = 0;
	sg->len = 0;
	sg->new_line = NULL;
	sg->i = 0;
}

int	**initialize_visited(t_map *m)
{
	int	**visited;

	visited = (int **)malloc(sizeof(int *) * m->height);
	if (!visited)
		return (write(1, "Error\n", 6), NULL);
	for (int i = 0; i < m->height; i++)
	{
		visited[i] = (int *)malloc(sizeof(int) * m->width);
		if (!visited[i])
		{
			write(1, "Error\n", 6);
			for (int j = 0; j < i; j++)
			{
				free(visited[j]);
			}
			free(visited);
			return (NULL);
		}
		memset(visited[i], 0, sizeof(int) * m->width);
	}
	return (visited);
}
